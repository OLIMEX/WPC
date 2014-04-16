using System.Collections.Generic;

namespace WPC51_ContainerLoad
{
    /// <summary>
    /// Simple class holding details of a container, its size and where the boxes are
    /// after it's been filled.
    /// </summary>
    public class Container
    {
        /// <summary>
        /// The fixed width of the container (x axis)
        /// </summary>
        public int WidthX { get; set; }

        /// <summary>
        /// The fixed depth of the container (z axis)
        /// </summary>
        public int DepthZ { get; set; }

        /// <summary>
        /// The fixed height of the container (y axis)
        /// </summary>
        public int HeightY { get; set; }

        /// <summary>
        /// An array which indicates whether each "cell" in the container is
        /// occupied by a box or not.  An element will be '.' if it's empty,
        /// or the box's identifier character if it's occupied.
        /// </summary>
        public char[, ,] Occupied { get; set; }

        /// <summary>
        /// A list for boxes that couldn't be fitted to the container.
        /// </summary>
        public List<Box> BoxesNotFitted { get; set; }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="widthX">The width of the container (x axis)</param>
        /// <param name="heightY">The height of the container (y axis)</param>
        /// <param name="depthZ">The depth of the container (z axis)</param>
        public Container(int widthX, int heightY, int depthZ)
        {
            this.WidthX = widthX;
            this.HeightY = heightY;
            this.DepthZ = depthZ;
            InitializeOccupied();
            BoxesNotFitted = new List<Box>();
        }

        /// <summary>
        /// Initializes an empty container.
        /// </summary>
        private void InitializeOccupied()
        {
            Occupied = new char[WidthX, HeightY, DepthZ];

            for (int x = 0; x < WidthX; x++)
            {
                for (int y = 0; y < HeightY; y++)
                {
                    for (int z = 0; z < DepthZ; z++)
                    {
                        Occupied[x, y, z] = '.';
                    }
                }
            }
        }
    }
}
