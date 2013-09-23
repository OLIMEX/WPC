
namespace WPC25_EqualTravelPaths
{
    public class Point
    {
        private int _x;
        private int _y;

        /// <summary>
        /// The X co-ordinate of the Point
        /// </summary>
        public int X 
        { 
            get
            {
                return _x;
            }
            set
            {
                _x = value;
            }
        }

        /// <summary>
        /// The Y co-ordinate of the Point
        /// </summary>
        public int Y 
        {
            get
            {
                return _y;
            }
            set
            {
                _y = value;
            }
        }

        /// <summary>
        /// Constructs the Point object.
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        public Point(int x, int y)
        {
            _x = x;
            _y = y;
        }

        /// <summary>
        /// Checks if two Point objects have the same co-ordinates, and hence are equal.
        /// </summary>
        /// <param name="a"></param>
        /// <returns></returns>
        public bool Equals(Point a)
        {
            // If parameter is null, return false
            if ((object)a == null) return false;

            // Return true if the fields in the two Points match.
            return (_x == a.X) && (_y == a.Y);
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
