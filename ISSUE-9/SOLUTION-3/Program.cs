using System;
using System.Collections.Generic;

namespace Olimex_Programming_Challenge_9
{
    /// <summary>
    /// Problem:
    /// Let have N (3..100) points with X,Y coordinates.
    /// Make code which checks if there is circle which to pass through all of them.
    /// </summary>
    public class Program
    {
        const double tolerance = 0.0000001;

        /// <summary>
        /// A set of points where the centre of the circle is at the origin
        /// of the cartesian grid.
        /// </summary>
        /// <returns></returns>
        private static List<Point> InitializePoints()
        {
            List<Point> points = new List<Point>();
            points.Add(new Point(7.07106781, 7.07106781));
            points.Add(new Point(-7.07106781, 7.07106781));
            points.Add(new Point(7.07106781, -7.07106781));
            points.Add(new Point(-7.07106781, -7.07106781));
            points.Add(new Point(7.07106781, -7.071068));

            return points;
        }

        /// <summary>
        /// Optional set of points where the centre of the circle is not 
        /// at the origin of the cartesian grid.
        /// </summary>
        /// <returns></returns>
        private static List<Point> InitializePoints2()
        {
            List<Point> points = new List<Point>();
            points.Add(new Point(11, 1));
            points.Add(new Point(1, 11));
            points.Add(new Point(1, -9));
            points.Add(new Point(-9, 1));
            points.Add(new Point(11, 1));
            points.Add(new Point(11, 1.01));
            points.Add(new Point(7.07106781, 7.07106781));

            return points;
        }

        public static void Main(string[] args)
        {
            // Get the list of points we'll run our test against.
            List<Point> points = InitializePoints();

            // Find the circle that passes through the first 3 points in the list.
            OlimexChallenge9 challenge = new OlimexChallenge9(points);
            CircleDefinition centre = challenge.FindCircleDefinitionFrom3Points();

            // Output commentary.
            Console.WriteLine("Number of points to check : {0}", points.Count);
            Console.WriteLine();
            Console.WriteLine("Point 1  : ({0}, {1})", points[0].X, points[0].Y);
            Console.WriteLine("Point 2  : ({0}, {1})", points[1].X, points[1].Y);
            Console.WriteLine("Point 3  : ({0}, {1})", points[2].X, points[2].Y);
            Console.WriteLine();
            Console.WriteLine("These 3 points define a circle with:");
            Console.WriteLine("Centre   : ({0}, {1})", centre.Centre.X, centre.Centre.Y);
            Console.WriteLine("Radius   :  {0}", centre.Radius);
            Console.WriteLine();

            // Assume all the points are on the circle until we prove otherwise.
            bool allPointsOnCircumference = true;

            // Check the distance of each point from the circle's centre against 
            // the radius to see if it sits on the circumference.
            if (points.Count > 3)
            {
                for (int pointIndex = 3; pointIndex < points.Count; pointIndex++)
                {
                    double xDistance = points[pointIndex].X - centre.Centre.X;
                    double yDistance = points[pointIndex].Y - centre.Centre.Y;
                    double distanceFromCentre =
                        Math.Sqrt(Math.Pow(xDistance, 2) + Math.Pow(yDistance, 2));

                    // Check whether we're within the tolerance limit.
                    if (Math.Abs(distanceFromCentre - centre.Radius) > tolerance)
                    {
                        // Off the circle.
                        Console.WriteLine("Point {0} : Not on circle  : ({1}, {2})", 
                            pointIndex + 1,
                            points[pointIndex].X, 
                            points[pointIndex].Y);
                        allPointsOnCircumference = false;
                    }
                    else
                    {
                        // On the circle.
                        Console.WriteLine("Point {0} : On the circle  : ({1}, {2})", 
                            pointIndex + 1,
                            points[pointIndex].X, 
                            points[pointIndex].Y);
                    }
                }
            }
            else
            {
                // Only 3 points so they must all be on the circle.
                Console.WriteLine("All points are on the circle's circumference.");
            }

            // Show the final result.
            Console.WriteLine();
            Console.WriteLine("*******************************************");
            if (allPointsOnCircumference)
                Console.WriteLine("    SUCCESS  !!!");
            else
                Console.WriteLine("    FAILED   !!!");
            Console.WriteLine("*******************************************");

            Console.WriteLine();
            Console.WriteLine("Press a key to exit...");
            Console.ReadLine();
        }
    }
}
