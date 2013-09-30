using System;
using System.Collections.Generic;
using System.IO;

namespace WPC26_Square
{
    /// <summary>
    /// Checks a set of 4 points to determine whether they define the corners of a square.
    /// We check whether it's a square by checking the distance between each pair of points.
    /// 
    /// For a square, 
    /// -  the length of each side must be the same and 
    /// -  the diagonal distances must be the same too.
    /// 
    /// This means we should only see 2 unique lengths.  Anything else isn't a square.
    /// 
    /// We also check for duplicate points too and reject the set outright if any are found.
    /// </summary>
    public class Program
    {
        /// <summary>
        /// The list of points to test.  N rows of 4 (x,y) coordinates.
        /// Add more if you need to, there's no need to update any counters in the code.
        /// </summary>
        private static int[] testpoints = new int[] 
        { 
            // These should be squares
            0,0,  1,1,  0,1,   1,0,
            0,0,  2,1,  3,-1,  1,-2,
            0,0,  1,1,  0,1,   1,0,
            -1,1, 1,1,  1,-1, -1,-1,
            -1000,1000,  1000,1000,  1000,-1000, -1000,-1000,
            0,15, -10,0, 15,5, 5,-10,

            // These should not be squares
            -1000,1000,  1000,1000,  1000,-1000, -1000,-1001,
            0,0,  0,2,  3,2,   3,0,
            0,0,  3,4,  8,4,   5,0,

            // Test for duplicate points so not a square
            0,0,  0,0,  1,1,   0,0,
            0,0,  0,0,  1,0,   0,1,
            10,10, 10,10, 10,10, 10,10
        };
        private static StreamWriter sw;


        static void Main(string[] args)
        {
            int noOfTests = testpoints.Length / 8;
            int pointIndex = 0;

            // Open a log file so we can write out the paths we find.
            string logFile = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "WPC26-Results.txt");
            sw = new StreamWriter(logFile);

            // Run round this loop until we've checked each set of 4 points in the test data.
            while (noOfTests-- > 0)
            {
                Write("Testing points : ");

                // Gather the coordinates for a set of 4 points from the test data and write
                // each out to the console to show them.
                List<Point> points = new List<Point>();
                int pointCounter = 0;
                while (pointCounter < 4)
                {
                    points.Add(new Point(testpoints[pointIndex++], testpoints[pointIndex++]));
                    pointCounter++;

                    Write(string.Format("{0},{1}  ", testpoints[pointIndex-2], testpoints[pointIndex-1]));
                }
                WriteLine();
                
                // Now work out whether the points comprise a square.
                Point a, b;
                List<int> uniqueLengths = new List<int>();
                bool duplicateFound = false;

                for (int i = 0; i < points.Count; i++)
                {
                    a = points[i];
                    for (int j = i + 1; j < points.Count; j++)
                    {
                        b = points[j];

                        // Check for a duplicate point
                        if (a.X == b.X && a.Y == b.Y)
                        {
                            duplicateFound = true;
                            break;
                        }

                        // Calculate the square of the distance between the 2 points
                        int x = Math.Abs(a.X - b.X);
                        int y = Math.Abs(a.Y - b.Y);
                        int z = x*x + y*y;

                        // Keep track of how many unique distances we have between any 2 points.
                        if (!uniqueLengths.Contains(z))
                        {
                            uniqueLengths.Add(z);
                        }
                    }

                    if (duplicateFound) break;
                }

                // Report our findings about this set of 4 points.
                if (duplicateFound)
                {
                    WriteLine(" NO    not a square because at least one of the coordinates is a duplicate");
                }
                else if (uniqueLengths.Count == 2)
                {
                    WriteLine("YES    a square");
                }
                else
                {
                    WriteLine(" NO    not a square");
                }

                WriteLine("--------------------------------------------------------------------------");
            }
            sw.Close();

            // Leave the console open so the user can view the results.
            Console.WriteLine("Press a key to exit...");
            Console.Read();
        }

        private static void Write(string message)
        {
            Console.Write(message);
            sw.Write(message);
        }

        private static void WriteLine(string message)
        {
            Console.WriteLine(message);
            sw.WriteLine(message);
        }

        private static void WriteLine()
        {
            Console.WriteLine();
            sw.WriteLine();
        }
    }

    /// <summary>
    /// An object to hold our point x,y coordinates.
    /// </summary>
    public class Point
    {
        public int X { get; set; }
        public int Y { get; set; }

        public Point(int x, int y)
        {
            X = x;
            Y = y;
        }
    }
}
