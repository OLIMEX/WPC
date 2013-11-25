using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace WPC34_POV_Led_Display
{
    public partial class Form1 : Form
    {
        const int AngularStep = 1;
        const int LedsPerStrip = 100;
        const int HVSize = 140;

        public Form1()
        {
            InitializeComponent();
            lblStatus.Text = string.Empty;
        }

        private void btnRun_Click(object sender, EventArgs e)
        {
            lblStatus.Text = string.Empty;

            // Read a simple black and white or grayscale BMP image.
            // For simplicity, it must be exactly 140 x 140 pixels in size.
            string bitmapImage = "m.bmp";
            string folder = AppDomain.CurrentDomain.BaseDirectory;
            string path = Path.Combine(folder, bitmapImage);

            // Load the bitmap image and find out its dimensions.
            Bitmap image = new Bitmap(path);
            if (image.Height != HVSize || image.Width != HVSize)
            {
                lblStatus.Text = string.Format("Image must be exactly {0} pixels wide and high", HVSize);
                return;
            }

            // Calculate the illuminate state of each led along the strip at each angular position
            // around the circular path.
            List<int[]> states = CalculateLedStates(image);

            // Show the resulting image that would be displayed
            DrawView(states);
        }

        private List<int[]> CalculateLedStates(Bitmap image)
        {
            Point centre = new Point(image.Width / 2, image.Height / 2);

            // A list to hold the states of each led along the light strip at each angular step
            List<int[]> states = new List<int[]>(360 / AngularStep);

            for (double degrees = 0; degrees < 360 / AngularStep; degrees++)
            {
                // Calculate the angle in radians
                double radians;         // = Math.PI * degrees / 180;

                if (degrees < 90)
                {
                    radians = Math.PI * degrees / 180;
                }
                else if (degrees < 180)
                {
                    radians = Math.PI * (180 - degrees) / 180;
                }
                else if (degrees < 270)
                {
                    radians = Math.PI * (degrees - 180) / 180;
                }
                else
                {
                    radians = Math.PI * (360 - degrees) / 180;
                }

                // Create a new strip of leds.
                int[] leds = new int[LedsPerStrip];

                // Progressively scan along the line from the centre of the image to find out
                // the co-ordinates of each led position along the line
                for (int distance = 0; distance < LedsPerStrip; distance++)
                {
                    int a = (int)(Math.Cos(radians) * distance);
                    int b = (int)(Math.Sin(radians) * distance);

                    Point ab = new Point();
                    if (degrees < 90)
                    {
                        ab.X = centre.X + a;
                        ab.Y = centre.Y + b;
                    }
                    else if (degrees < 180)
                    {
                        ab.X = centre.X - a;
                        ab.Y = centre.Y + b;
                    }
                    else if (degrees < 270)
                    {
                        ab.X = centre.X - a;
                        ab.Y = centre.Y - b;
                    }
                    else
                    {
                        ab.X = centre.X + a;
                        ab.Y = centre.Y - b;
                    }

                    // Look into the bitmap image at the coordinates to find out whether the 
                    // led should be illuminated or not.
                    if (ab.X >= image.Width || ab.Y >= image.Height || ab.X < 0 || ab.Y < 0)
                    {
                        // The point is outside the bounds of the image so the led will 
                        // not be illuminated.
                    }
                    else
                    {
                        // the point is inside the bounds of the image so the led will
                        // be illuminated.
                        Color pixel = image.GetPixel(ab.X, ab.Y);
                        float brightness = pixel.GetBrightness();
                        if (brightness > 0.25)
                        {
                            leds[distance] = 1;
                        }
                    }
                }

                // The led strip is now populated with a value that says how bright each led is to
                // be along the strip.  Add this to the states list.
                states.Add(leds);
            }

            return states;
        }

        private void DrawView(List<int[]> states)
        {
            // Create a new bitmap to hold the image the rotating led strip will show.
            Bitmap view = new Bitmap(HVSize, HVSize);
            pb1.Image = view;

            Point centre = new Point(view.Width / 2, view.Height / 2);

            //for (int degrees = 0; degrees < 360 / AngularStep; degrees++)
            for (int degrees = 0; degrees < 360; degrees++)
            {
                // Calculate the angle in radians
                double radians;     // = Math.PI * degrees / 180;
                if (degrees < 90)
                {
                    radians = Math.PI * degrees / 180;
                }
                else if (degrees < 180)
                {
                    radians = Math.PI * (180 - degrees) / 180;
                }
                else if (degrees < 270)
                {
                    radians = Math.PI * (degrees - 180) / 180;
                }
                else
                {
                    radians = Math.PI * (360 - degrees) / 180;
                }

                int[] leds = states[degrees];

                for (int distance = 0; distance < LedsPerStrip; distance++)
                {
                    int a = (int)(Math.Cos(radians) * distance);
                    int b = (int)(Math.Sin(radians) * distance);

                    Point ab = new Point();
                    if (degrees < 90)
                    {
                        ab.X = centre.X + a;
                        ab.Y = centre.Y + b;
                    }
                    else if (degrees < 180)
                    {
                        ab.X = centre.X - a;
                        ab.Y = centre.Y + b;
                    }
                    else if (degrees < 270)
                    {
                        ab.X = centre.X - a;
                        ab.Y = centre.Y - b;
                    }
                    else
                    {
                        ab.X = centre.X + a;
                        ab.Y = centre.Y - b;
                    }

                    if (ab.X >= view.Width || ab.Y >= view.Height || ab.X < 0 || ab.Y < 0)
                    {
                        // The point is outside the bounds of the image so the led will 
                        // not be illuminated.
                    }
                    else
                    {
                        // the point is inside the bounds of the image so the led will
                        // be illuminated.
                        if (leds[distance] > 0)
                        {
                            view.SetPixel(ab.X, ab.Y, Color.Blue);
                            pb1.Refresh();
                        }
                    }
                }
            }
        }
    }
}
