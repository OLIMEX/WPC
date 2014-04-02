using System;

namespace WPC48_Geometry
{
    class Program
    {
        static void Main(string[] args)
        {
            string test;

            test = "Test 1 - should be anti-clockwise";
            Calculate(test, new Point(2, 5), new Point(7, 1), new Point(13, 4));

            test = "Test 2 - should be clockwise";
            Calculate(test, new Point(2, 5), new Point(7, 10), new Point(13, 4));

            test = "Test 3 - should be all on the same line";
            Calculate(test, new Point(2, 2), new Point(7, 7), new Point(13, 13));

            test = "Test 4 - some wacky points";
            Calculate(test, new Point(123.111, 789.256), new Point(-156.24, -0), new Point(542.1, -8996.4));

            test = "Test 5 - A, B and C are all the same points";
            Calculate(test, new Point(7, 5), new Point(7, 5), new Point(7, 5));

            Console.WriteLine("Press a key to exit");
            Console.Read();
        }

        static void Calculate(string description, Point a, Point b, Point c)
        {
            Console.WriteLine(description);
            Console.WriteLine("A={0}   B={1}   C={2}", a.ToString(), b.ToString(), c.ToString());

            // First translate the points to put point A at the origin of the plane.
            b = b - a;
            c = c - a;
            a = new Point(0, 0);

            // Measure the angle between line AB and the x-axis.
            // This is the angle that we will rotate the plane containing points B and C
            // through to align point B on the x-axis.
            double radians = Math.Atan2(b.Y, b.X);

            // Rotate the plane in the opposite direction to the angle.
            b.Rotate(-radians);
            c.Rotate(-radians);

            // See if Cy is on the x-axis, i.e. is on the same line as A and B.
            if (c.Y == 0)
            {
                Console.WriteLine("Path A->B->C - all three points are on the same line");
            }
            else
            {
                // If Cy is below the x-axis, we're going in a clockwise direction.
                bool isClockwise = c.Y < 0;
                Console.WriteLine("Path A->B->C goes in {0} direction", isClockwise ? "a clockwise" : "an anti-clockwise");
            }

            Console.WriteLine("----------------------------------------------------------------------");
        }
    }
}
