using System;
using System.Drawing;

namespace WPC50_Circle_Find
{
    /// <summary>
    /// Challenge:
    /// In window with size 100 x 100 pixels is drawn solid filled circle with 50 pixels 
    /// diameter at random coordinates X,Y but the circle is completely inside the window. 
    /// Make code which finds the circle XY coordinates.
    /// </summary>
    /// <remarks>
    /// This is a bit like WPC9 (May 2013) which determined if a circle could be drawn 
    /// through 3 arbitrary points.
    /// </remarks>
    class Program
    {
        static void Main(string[] args)
        {
            // Report the centre of a circle in one image
            Bitmap bitmap = Resource1.blue_circle_o1;
            FindCentre(bitmap, "Blue Circle 1");

            // Report the centre of the circle in another image.
            bitmap = Resource1.blue_circle_o2;
            FindCentre(bitmap, "Blue Circle 2");

            // Report the centre of the circle in another image.
            bitmap = Resource1.blue_circle_o3;
            FindCentre(bitmap, "Blue Circle 3");

            Console.WriteLine("Press a key to quit...");
            Console.Read();
        }

        static void FindCentre(Bitmap image, string imageName)
        {
            Console.WriteLine("Finding centre of {0}", imageName);
            
            // Find the centre of the circle.
            try
            {
                double centreX, centreY;
                Calculator.FindCentre(image, out centreX, out centreY);
                Console.WriteLine("Centre is at : ({0:0.00}, {1:0.00})", centreX, centreY);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }

            Console.WriteLine();
            Console.WriteLine(string.Empty.PadRight(30, '*'));
        }
    }
}
