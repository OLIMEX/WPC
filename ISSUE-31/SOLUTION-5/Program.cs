using System;
using System.Drawing;
using System.IO;
using System.Text;

namespace WPC_31___Run_Length_Encoder_Decoder
{
    /// <summary>
    /// Reads a simple bitmap image, the Olimex logo, parses it into rows of B and W characters, 
    /// to represent the raw pixel illumination, then encodes it into Run Length Encoded form, 
    /// then decodes it back into its original form.
    /// 
    /// Both encoded and decoded forms are written out to text files for analysis.
    /// </summary>
    /// 
    /// <originalProblem>
    /// RLE/D is the simplest way to compress data http://en.wikipedia.org/wiki/Run-length_encoding
    /// Implement RLE/D in shortest/simplest way possible using your favourite language.
    /// </originalProblem>
    class Program
    {
        /// <summary>
        /// This is the array that will hold a string for each line in the image.
        /// The string will contain the unencoded (raw) data, a sequence of B or W
        /// to indicate whether a pixel in the image is illuminated or not.
        /// </summary>
        static string[] lines;

        static void Main(string[] args)
        {
            // Read a simple black and white or grayscale BMP image
            string bitmapImage = "logo.bmp";
            string folder = AppDomain.CurrentDomain.BaseDirectory;
            string path = Path.Combine(folder, bitmapImage);

            // Load the bitmap image and find out its dimensions.
            Bitmap image = new Bitmap(path);
            int height = image.Height;
            int width = image.Width;

            // We'll need one string for each row of pixels in the image.
            lines = new string[height];

            // Scan through the image row by row, reading each pixel and writing out
            // a B or W into the line string depending on whether it's Black or White.
            for (int y = 0; y < height; y++)
            {
                StringBuilder line = new StringBuilder(width);

                for (int x = 0; x < width; x++)
                {
                    Color pixel = image.GetPixel(x, y);
                    if (pixel.R < 128)
                        // Pixel is black
                        line.Append('B');
                    else
                        // pixel is white
                        line.Append('W');
                }

                // Encode the raw line and add it to the string array.
                lines[y] = EncodeLine(line);
            }

            // Write the run length encoded lines out to a text file.
            string encodedOutputFile = Path.Combine(folder, "encoded output.txt");
            using (StreamWriter encodedOutput = new StreamWriter(encodedOutputFile))
            {
                for (int i = 0; i < lines.Length; i++)
                {
                    Console.WriteLine(lines[i]);
                    encodedOutput.WriteLine(lines[i]);
                }
                encodedOutput.Close();
            }

            // Decode the output back to its original raw form and write to a text file.
            string decodedOutputFile = Path.Combine(folder, "decoded output.txt");
            using (StreamWriter decodedOutput = new StreamWriter(decodedOutputFile))
            {
                for (int i = 0; i < lines.Length; i++)
                {
                    decodedOutput.WriteLine(DecodedLine(lines[i]));
                }
                decodedOutput.Close();
            }

            // Leave the console open so the user can see the results.
            Console.WriteLine();
            Console.WriteLine("Press a key to quit...");
            Console.Read();
        }

        /// <summary>
        /// Decode a run length encoded string back into its original form.
        /// </summary>
        /// <param name="line">The RLE string, e.g. 4W3B2W10B</param>
        /// <returns>The original string with an @ for a black pixel and space for a white one,
        /// e.g. "    @@@  @@@@@@@@@@"</returns>
        private static string DecodedLine(string line)
        {
            int repeatCounter = 0;
            string repeatNumber = string.Empty;
            StringBuilder decoded = new StringBuilder();
            char aChar = '.';

            for (int i = 0; i < line.Length; i++)
            {
                aChar = line[i];
                if (char.IsDigit(aChar))
                {
                    repeatNumber += aChar;
                }
                else
                {
                    int.TryParse(repeatNumber, out repeatCounter);
                    repeatNumber = string.Empty;
                    for (int z = 0; z < repeatCounter; z++)
                    {
                        // Substitute B with an @ character and W with a space
                        // to make the image clearer to see as text.
                        decoded.Append(aChar == 'B' ? '@': ' ');
                    }
                }
            }

            return decoded.ToString();
        }

        /// <summary>
        /// Encode a string of B and W characters, that represent Black and White pixels in an image
        /// line, into its run length encoded form.
        /// </summary>
        /// <param name="line">The string of B and W characters, 
        /// e.g. WWWWBBBWWBBBBBBBBBB</param>
        /// <returns>The RLE string, e.g. 4W3B2W10B</returns>
        private static string EncodeLine(StringBuilder line)
        {
            int repeatCounter = 0;
            char currentPixel = line[0];
            StringBuilder encoded = new StringBuilder();

            for (int i = 0; i < line.Length; i++)
            {
                if (currentPixel == line[i])
                {
                    repeatCounter++;
                }
                else
                {
                    encoded.AppendFormat("{0}{1}", repeatCounter, currentPixel);
                    currentPixel = line[i];
                    repeatCounter = 1;
                }
            }

            // Don't forget the last bit on the line.
            encoded.AppendFormat("{0}{1}", repeatCounter, currentPixel);

            return encoded.ToString();
        }
    }
}
