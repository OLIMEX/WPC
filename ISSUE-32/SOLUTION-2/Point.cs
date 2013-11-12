
namespace WPC32_PCB_panelization
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
    }
}
