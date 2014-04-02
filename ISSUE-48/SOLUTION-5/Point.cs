using System;

namespace WPC48_Geometry
{
    public class Point
    {
        public double X { get; set; }
        public double Y { get; set; }

        public Point(double x, double y)
        {
            X = x;
            Y = y;
        }

        /// <summary>
        /// Define the subtraction operator so we can subtract one point from another.
        /// </summary>
        /// <param name="a"></param>
        /// <param name="b"></param>
        /// <returns></returns>
        public static Point operator -(Point a, Point b)
        {
            return new Point(a.X - b.X, a.Y - b.Y);
        }

        /// <summary>
        /// Rotate this point through the specified angle expressed in radians.
        /// </summary>
        /// <param name="radians"></param>
        public void Rotate(double radians)
        {
            // Tolerance when a point is close to zero that we will treat it as zero.
            const double RoundingTolerance = 0.0000000000001;

            double x = this.X * Math.Cos(radians) - this.Y * Math.Sin(radians);
            double y = this.X * Math.Sin(radians) + this.Y * Math.Cos(radians);

            if (x < 0 && x > -RoundingTolerance || x > 0 && x < RoundingTolerance) x = 0;
            if (y < 0 && y > -RoundingTolerance || y > 0 && y < RoundingTolerance) y = 0;
            
            this.X = x;
            this.Y = y;
        }

        /// <summary>
        /// A string representing the point in the form "(x, y)"
        /// </summary>
        /// <returns>A stringified representation of this point.</returns>
        public override string ToString()
        {
            return string.Format("({0}, {1})", X, Y);
        }
    }
}
