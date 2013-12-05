
namespace WPC35_Maze
{
    public class Point
    {
        public int X { get; set; }
        public int Y { get; set; }

        public Point(int x, int y)
        {
            X = x;
            Y = y;
        }

        /// <summary>
        /// Define the conditional equals check operator so we can compare two Point objects for equality.
        /// </summary>
        /// <param name="a"></param>
        /// <param name="b"></param>
        /// <returns></returns>
        public static bool operator ==(Point a, Point b)
        {
            if (object.ReferenceEquals(a, b)) return true;

            if ((object)a == null || (object)b == null) return false;

            return a.X == b.X && a.Y == b.Y;
        }

        /// <summary>
        /// Define the converse of the equals check.
        /// </summary>
        /// <param name="a"></param>
        /// <param name="b"></param>
        /// <returns></returns>
        public static bool operator !=(Point a, Point b)
        {
            return !(a == b);
        }
    }
}
