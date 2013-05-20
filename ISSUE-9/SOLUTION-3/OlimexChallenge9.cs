using System;
using System.Collections.Generic;

namespace Olimex_Programming_Challenge_9
{
    public class OlimexChallenge9
    {
        private List<Point> pointsList;

        /// <summary>
        /// Construct an object with the list of points to check.
        /// </summary>
        /// <param name="points">The list of points to check.</param>
        public OlimexChallenge9(List<Point> points)
        {
            if (points.Count < 3 || points.Count > 100)
            {
                throw new ArgumentException("Number of points outside expected range of 3 <= points <= 100.");
            }
            pointsList = points;
        }

        /// <summary>
        /// Get the circle that passes through the first 3 points in the list.
        /// </summary>
        /// <returns>An object containing the definition of a circle, e.g. the radius and
        /// centre co-ordinates.</returns>
        public CircleDefinition FindCircleDefinitionFrom3Points()
        {
            // Get the first 3 points in the list to check.  There will always be a circle
            // that passes through these 3 points provided they aren't on the same straight
            // line (co-linear).
            Point A = pointsList[0];
            Point B = pointsList[1];
            Point C = pointsList[2];

            // Calculate the gradient of line BA
            double xChordBA = B.X - A.X;
            double yChordBA = B.Y - A.Y;
            double gradientBA = yChordBA / xChordBA;

            // Calculate the gradient of line CA
            double xChordCA = C.X - A.X;
            double yChordCA = C.Y - A.Y;
            double gradientCA = yChordCA / xChordCA;

            double centreX = 0;
            if (gradientBA == 0)
            {
                // When line BA is a flat horizontal line, the X coordinate of the
                // centre of the circle will be halfway between points B and A.
                if (A.X >= B.X)
                    centreX = A.X - (A.X - B.X) / 2;
                else
                    centreX = B.X - (B.X - A.X) / 2;
            }
            else if (double.IsInfinity(gradientBA))
            {
                // When BA is a vertical line, the X coordinate of the centre of 
                // the circle is the same as for points B and A.
                centreX = B.X;
            }
            else
            {
                // Calculate the X coordinate of the centre of the circle.
                 centreX = ( gradientBA * gradientCA * (A.Y - C.Y)
                           + gradientCA * (A.X + B.X)
                           - gradientBA * (B.X + C.X) )
                           / ((gradientCA - gradientBA) * 2);
            }

            // If the gradient of chord BA is zero, we have to calculate the Y coordinate
            // of the centre from chord CA instead.
            double centreY = 0;
            if (gradientCA == 0)
            {
                // When CA is a vertical line, the Y coordinate of the centre of 
                // the circle is the same as for points C and A.
                centreY = C.Y;
            }
            else if (double.IsInfinity(gradientCA))
            {
                // When line CA is a flat horizontal line, the Y coordinate of the
                // centre of the circle will be halfway between points C and A.
                if (A.Y >= C.Y)
                    centreY = A.Y - (A.Y - C.Y) / 2;
                else
                    centreY = C.Y - (C.Y - A.Y) / 2;
            }
            else
            {
                if (gradientBA != 0)
                {
                    centreY = -1 * (centreX - (A.X + B.X) / 2)
                              / gradientBA + (A.Y + B.Y) / 2;
                    //Console.WriteLine("Normal path");
                }
                else
                {
                    centreY = -1 * (centreX - (B.X + C.X) / 2)
                              / gradientCA + (B.Y + C.Y) / 2;
                    //Console.WriteLine("alternate path");
                }
            }

            Point centre = new Point(centreX, centreY);

            // Find the radius from one of the known points on the cirle and the centre.
            double xDistance = centre.X - A.X;
            double yDistance = centre.Y - A.Y;
            double radius = Math.Sqrt(xDistance * xDistance + yDistance * yDistance);

            // Put the lot into an object for the caller
            return new CircleDefinition(radius, centre);
        }
    }

    /// <summary>
    /// Holds the attributes that define a circle (the centre point and radius).
    /// </summary>
    public class CircleDefinition
    {
        public double Radius { get; set; }
        public Point Centre { get; set; }

        public CircleDefinition(double radius, Point centre)
        {
            Radius = radius;
            Centre = centre;
        }
    }

    /// <summary>
    /// Holds the cartesian x,y co-ordinates for a point.
    /// </summary>
    public class Point
    {
        public double X { get; set; }
        public double Y { get; set; }

        public Point(double x, double y)
        {
            X = x;
            Y = y;
        }
    }
}
