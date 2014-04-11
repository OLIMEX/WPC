using System;
using System.Collections.Generic;
using System.Drawing;

namespace WPC50_Circle_Find
{
    public static class Calculator
    {
        /// <summary>
        /// Main function that finds the centre of the circle in the supplied image.
        /// </summary>
        /// <param name="image">The bitmap containing the coloured circle.</param>
        /// <param name="centreX">The x co-ordinate of the centre of the coloured circle.</param>
        /// <param name="centreY">The y co-ordinate of the centre of the coloured circle.</param>
        public static void FindCentre(Bitmap image, out double centreX, out double centreY)
        {
            List<Point> points = new List<Point>();

            // Scan the image to find some points on the circumference of the circle.
            // First, scan vertical lines
            Point point;
            if (FindCircumferencePoint(image, 75, 99, 0, -1, out point)) points.Add(point);
            if (FindCircumferencePoint(image, 50,  0, 0, +1, out point)) points.Add(point);
            if (FindCircumferencePoint(image, 25, 99, 0, -1, out point)) points.Add(point);

            // Next scan horizontal lines
            if (FindCircumferencePoint(image,  0, 75, +1, 0, out point)) points.Add(point);
            if (FindCircumferencePoint(image, 99, 50, -1, 0, out point)) points.Add(point);
            if (FindCircumferencePoint(image,  0, 25, +1, 0, out point)) points.Add(point);

            // OK, we should have at least 4 points.  
            if (points.Count < 3) throw new Exception("Can't find centre.  Not enough points found.");
            
            CalculateCentre(points, out centreX, out centreY);
        }

        /// <summary>
        /// Using the first 3 points in the supplied list, calculate the co-ordinates of the centre of
        /// a circle that passes through these points. The algorithm finds the centre by calculating the
        /// co-odinates of the point where the perpendiculars from the lines between points AB and BC 
        /// intersect.
        /// </summary>
        /// <param name="points">The list of points around the circumference of the coloured circle in
        /// the image.</param>
        /// <param name="centreX">The calculated x co-ordinate of the centre of the circle.</param>
        /// <param name="centreY">The calculated y co-ordinate of the centre of the circle.</param>
        private static void CalculateCentre(List<Point> points, out double centreX, out double centreY)
        {
            Point A = points[0];
            Point B = points[1];
            Point C = points[3];

            //                              By - Ay
            // Calculate slope of AB.  mr = -------
            //                              Bx - Ax
            double mr = (double)(B.Y - A.Y) / (double)(B.X - A.X);

            //                              Cy - By
            // Calculate slope of BC.  mt = -------
            //                              Cx - Bx
            double mt = (double)(C.Y - B.Y) / (double)(C.X - B.X);

            //               mr * mt (Cy - Ay) + mr (Bx + Cx) - mt (Ax + Bx)
            // Solve for x = -----------------------------------------------
            //                           2 * (mr - mt)
            centreX = (mr * mt * (double)(C.Y - A.Y) + mr * (double)(B.X + C.X) - mt * (double)(A.X + B.X)) / (2 * (double)(mr - mt));

            //                  1    (     Ax + Bx )   Ay + By
            // Solve for y = - --- * ( x - ------- ) + -------
            //                  mr   (        2    )      2
            centreY = (double)(-1 / mr) * (centreX - ((A.X + B.X) / 2)) + (double)(A.Y + B.Y) / 2;
        }

        /// <summary>
        /// Scans the pixels along a vertical or horizontal line through the image to find a pixel that is
        /// coloured.  This will be on the circumference of the circle.
        /// </summary>
        /// <param name="image">The bitmap image containing the coloured circle.</param>
        /// <param name="xStart">The x position at the start of the line to scan.</param>
        /// <param name="yStart">The y position at the start of the line to scan.</param>
        /// <param name="xStep">The number of pixels we'll setp along the line in the x direction.</param>
        /// <param name="yStep">The number of pixels we'll step along the line in the y direction.</param>
        /// <param name="onCircumference">The co-ordinates of the point found on the circumference,
        /// if such a point exists.</param>
        /// <returns>True - a point was found; false if the scanned line doesn't touch the circle.</returns>
        /// <remarks>
        /// This method of finding a point on the circle's circumference isn't great because the image
        /// is only 100 x 100 pixels in size, so there will be a lot of 'pixellation' around the circumference.
        /// But hey, that's set by the challenge.  Having an image that is 1000 x 1000 pixels in size would
        /// yield a more accurate result.
        /// </remarks>
        private static bool FindCircumferencePoint(Bitmap image, int xStart, int yStart, int xStep, int yStep, out Point onCircumference)
        {
            int x = xStart;
            int y = yStart;
            onCircumference = new Point(0, 0);

            for (int i=0; i<image.Height; i++)
            {
                // Find out what colour the pixel is.
                Color pixel = image.GetPixel(x, y);
                if (pixel.R < 200)
                {
                    // We've hit the circumference so return that point
                    onCircumference = new Point(x, y);
                    break;
                }

                y += yStep;
                x += xStep;
            }

            // Tell the caller whether we found a point on the circumference or not.
            return onCircumference.X + onCircumference.Y != 0;
        }
    }
}
