using System;

namespace WPC51_ContainerLoad
{
    /// <summary>
    /// Simple class for holding details of a box, its size and identifier.
    /// </summary>
    public class Box : IComparable<Box>
    {
        /// <summary>
        /// Width of the box (x axis)
        /// </summary>
        public int WidthX { get; set; }

        /// <summary>
        /// Height of the box (y axis)
        /// </summary>
        public int HeightY { get; set; }

        /// <summary>
        /// Depth of the box (z axis)
        /// </summary>
        public int DepthZ { get; set; }

        /// <summary>
        /// Box identifier number
        /// </summary>
        public char Identifier { get; set; }

        /// <summary>
        /// The surface area of the side on the XZ plane.
        /// </summary>
        public int SurfaceAreaXZ
        {
            get { return WidthX * DepthZ; }
        }

        /// <summary>
        /// The surface area of the side on the XY plane.
        /// </summary>
        public int SurfaceAreaXY
        {
            get { return WidthX * HeightY; }
        }

        /// <summary>
        /// The surface area of the side on the YZ plane.
        /// </summary>
        public int SurfaceAreaYZ
        {
            get { return HeightY * DepthZ; }
        }

        /// <summary>
        /// Constructs a box object.
        /// </summary>
        /// <param name="width">Box width (x axis)</param>
        /// <param name="height">Box height (y axis)</param>
        /// <param name="depth">Box depth (z axis)</param>
        /// <param name="identifier">Identifier of this box</param>
        public Box(int width, int height, int depth, char identifier)
        {
            WidthX = width;
            HeightY = height;
            DepthZ = depth;
            Identifier = identifier;
        }

        /// <summary>
        /// Used when sorting to get the boxes into surface area XZ
        /// descending order.
        /// </summary>
        /// <param name="other">The box to compare this box against.</param>
        /// <returns>
        /// 0 when both boxes are the same<para/>
        /// +ve when the surface area of the other box is larger than this box<para/>
        /// -ve when the surface area of the other box is smaller than this box.<para/>
        /// The surface area of the box in the XZ plane is compared first.
        /// If they're the same, we prefer the one with the smallest height.
        /// </returns>
        public int CompareTo(Box other)
        {
            if (other.SurfaceAreaXZ != this.SurfaceAreaXZ)
            {
                return other.SurfaceAreaXZ - this.SurfaceAreaXZ;
            }
            else
            {
                return this.HeightY - other.HeightY;
            }
        }
    }
}
