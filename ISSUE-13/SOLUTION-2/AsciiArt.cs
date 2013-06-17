using System;
using System.IO;
using System.Drawing;
using System.Drawing.Imaging;
using System.Collections.Generic;
using System.Diagnostics;

namespace Olimex_Programming_Challenge_13
{
    /// <summary>
    /// Converts a picture into ASCII art.
    /// </summary>
    /// <remarks>
    /// This is very easy challenge although seems hard at first sight.
    /// <para/>
    /// Just convert the picture from color to gray scale, then select font which you will
    /// use to print ASCII art and analyze it which letters you could use for gray scale print 
    /// – every letter have some coefficient of filling from 0 for the space to 255 for 
    /// solid bar, use letters which are spread well in the font size space. Then slice 
    /// your image at rectangles with the font size, calculate the median grey scale for 
    /// each rectangle and print the corresponding ASCII character with same grey scale 
    /// value.
    /// </remarks>
    class AsciiArt
    {
        // The set of characters we'll use for drawing the ascii art.
        private const string letters = "!£$%^&*()-+=,./?<>:;'#@~[]{}|0123456789 abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        
        // These hold the user inputs.
        private static string filename;
        private static float gammaCorrection;
        private static int pixelBlockSize;

        static void Main(string[] args)
        {
            // Loop round so we can try different input parameters.
            while (true)
            {
                try
                {
                    // Get the user's inputs; filename, pixels per character, gamma correction.
                    GetInputs();

                    // Read the picture file
                    string fullPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, filename);
                    Image sourceImage = Bitmap.FromFile(fullPath);

                    // Convert to a greyscale non-indexed BMP image and save for visual check.
                    Image nonIndexBMP = ConvertSourceImageToGreyscale(sourceImage);
                    nonIndexBMP.Save("greyscale.bmp");

                    // Build a dictionary that tells us how dark each character is in the available letters.
                    Dictionary<char, int> densities = GetCharacterDensities();

                    // When we scan through the bitmap image, we look at a block of pixels that's 
                    // pixelBlockSize x pixelBlockSize in size.  This allows us to read larger images and
                    // scale the ascii art down in size.  If we didn't do this, the ascii art would have 
                    // the same width and height as the pixel width and height of the image, which makes 
                    // the ascii art massive!  We can still generate massive text files if we want by
                    // specifying a pixel block size of 1 when prompted for user input.
                    int xMax = nonIndexBMP.Width / pixelBlockSize;
                    int yMax = nonIndexBMP.Height / pixelBlockSize;
                    Bitmap bmGrey = nonIndexBMP as Bitmap;

                    // This will hold the ascii art characters.
                    char[,] ascii = new char[xMax, yMax];

                    int xBitmap = 0;
                    int yBitmap = 0;
                    int xAscii = 0;
                    int yAscii = 0;

                    // Scan through the bitmap.
                    while (yBitmap < nonIndexBMP.Height)
                    {
                        while (xBitmap < nonIndexBMP.Width)
                        {
                            // Scan the pixel block to find its average grey level.
                            int averageGrey = 0;

                            // Ensure we don't look beyond the bounds of the image.
                            if (xBitmap + pixelBlockSize < nonIndexBMP.Width && 
                                yBitmap + pixelBlockSize < nonIndexBMP.Height)
                            {
                                // Calculate the average grey level of the pixel block.
                                for (int xBlock = 0; xBlock < pixelBlockSize; xBlock++)
                                {
                                    for (int yBlock = 0; yBlock < pixelBlockSize; yBlock++)
                                    {
                                        averageGrey += 255 - bmGrey.GetPixel(xBitmap + xBlock, yBitmap + yBlock).R;
                                    }
                                }
                                averageGrey = averageGrey / (pixelBlockSize * pixelBlockSize);

                                // Find the ascii character that's nearest in brightness to the block.
                                char c = ' ';
                                int difference = int.MaxValue;
                                foreach (KeyValuePair<char, int> kv in densities)
                                {
                                    if (Math.Abs(kv.Value - averageGrey) < difference)
                                    {
                                        difference = Math.Abs(kv.Value - averageGrey);
                                        c = kv.Key;
                                    }
                                }
                                ascii[xAscii, yAscii] = c;
                            }

                            // Bump x along to the next block of pixels.
                            xBitmap += pixelBlockSize;
                            xAscii++;
                        }

                        // Bump y down to the next block of pixels.
                        yBitmap += pixelBlockSize;
                        yAscii++;

                        // We're starting on a new row of pixels in the image so reset our 
                        // x coordinate counters.
                        xBitmap = 0;
                        xAscii = 0;
                    }

                    // Almost done.  Write out the ascii art to a text file.
                    StreamWriter sw = new StreamWriter("asciiart.txt");
                    for (int y = 0; y < yMax; y++)
                    {
                        for (int x = 0; x < xMax; x++)
                        {
                            sw.Write(ascii[x, y]);
                        }
                        sw.WriteLine();
                    }
                    sw.Flush();
                    sw.Close();

                    // And finally show the ascii art to the user.  Tada!
                    Process pr = new Process();
                    pr.StartInfo.FileName = "notepad.exe";
                    pr.StartInfo.Arguments = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "asciiart.txt");
                    pr.StartInfo.CreateNoWindow = false;
                    pr.Start();
                    pr.WaitForExit();
                }
                catch (Exception ex)
                {
                    Console.WriteLine();
                    Console.WriteLine("*****************    Error   *********************");
                    Console.WriteLine(ex);
                }
                Console.WriteLine();
            }
        }

        private static Dictionary<char, int> GetCharacterDensities()
        {
            // Create a graphics object for the characters.
            int aWidth = 50;        // These are suitable for Courier New at 52ems.
            int aHeight = 76;
            Bitmap bm = new Bitmap(aWidth, aHeight);
            Graphics gr = Graphics.FromImage(bm);
            gr.Clear(Color.White);
            gr.TextRenderingHint = System.Drawing.Text.TextRenderingHint.SingleBitPerPixel;

            // Find out how big each monospaced character is.  We'll use Courier New but we
            // could use any mono-spaced font.
            Font font = new Font("Courier New", 52);
            SolidBrush brush = new SolidBrush(Color.Black);

            // Build a list of how black each character is in the letters we have available.
            Dictionary<char, int> densities = new Dictionary<char, int>(letters.Length);
            foreach (char c in letters)
            {
                // Start with a blank graphics canvas and draw the single character onto it.
                gr.Clear(Color.White);
                gr.DrawString(c.ToString(), font, brush, -6, -8);

                // Then look at each pixel to calculate how dark it is.
                int blackPixels = 0;
                for (int x = 0; x < aWidth; x++)
                {
                    for (int y = 0; y < aHeight; y++)
                    {
                        // The image is black & white so each of the RGB components have the same value.
                        // We only look at the red component but we could look at the G or B one.
                        Color colour = bm.GetPixel(x, y);

                        // Simple posterize check.
                        if (colour.R < 100)
                        {
                            blackPixels++;
                        }
                    }
                }

                densities.Add(c, blackPixels);
            }

            return densities;
        }

        private static void GetInputs()
        {
            // Get the filename to process.
            const string defaultFilename = "geek.bmp";
            Console.Write("Filename e.g. logo.bmp (default = {0}) : ", defaultFilename);
            filename = Console.ReadLine();
            if (filename.Trim().Length == 0) filename = defaultFilename;

            // Get the number of pixels that collectively will form the block for one ascii character.
            Console.Write("Pixel block size e.g. 3      (default 1)    : ");
            string blockSize = Console.ReadLine();
            if (!int.TryParse(blockSize, out pixelBlockSize)) pixelBlockSize = 1;

            // Get the gamma correction to compensate for different brightness of source images.
            Console.Write("Gamma correction  e.g. 3.5   (default 5.7)  : ");
            string sGamma = Console.ReadLine();
            if (!float.TryParse(sGamma, out gammaCorrection)) gammaCorrection = 5.7F;
        }

        private static Image ConvertSourceImageToGreyscale(Image source)
        {
            // Assume that the colour BMP is indexed to a palette.
            // Convert to a non-indexed BMP so we can load it into a graphics object.
            Image nonIndexBMP = new Bitmap(source.Width, source.Height, PixelFormat.Format24bppRgb);
            Graphics gr = Graphics.FromImage(nonIndexBMP);
            gr.DrawImage(source, 0, 0);
            gr.Dispose();

            // Setup a colour matrix for greyscale.
            float greytone = 1 / gammaCorrection;
            float[][] midtone = new float[5][];
            for (int i = 0; i < 5; i++)
            {
                midtone[i] = new float[5] { greytone, greytone, greytone, 1, 1 };
            }
            ImageAttributes attrs = new ImageAttributes();
            attrs.SetColorMatrix(new ColorMatrix(midtone));

            // Convert the colour non-indexed BMP to greyscale BMP.
            Graphics greyImage = Graphics.FromImage(nonIndexBMP);
            greyImage.DrawImage(source,
                                new Rectangle(0, 0, source.Width, source.Height),
                                0,
                                0,
                                source.Width,
                                source.Height,
                                GraphicsUnit.Pixel,
                                attrs);
            greyImage.Dispose();

            return nonIndexBMP;
        }
    }
}
