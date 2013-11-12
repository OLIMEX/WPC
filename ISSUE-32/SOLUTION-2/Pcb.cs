using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WPC32_PCB_panelization
{
    public class Pcb : IComparable<Pcb>
    {
        // Property backing variables.
        private int _width;
        private int _height;
        private char _identifier;
        private int _borderSpace;

        /// <summary>
        /// Width of the pcb.
        /// </summary>
        public int Width
        { 
            get { return _width; }
            set { _width = value; }
        }

        /// <summary>
        /// Height of the pcb.
        /// </summary>
        public int Height
        {
            get { return _height; }
            set { _height = value; }
        }

        /// <summary>
        /// Pcb identifier letter
        /// </summary>
        public char Identifier
        {
            get { return _identifier; }
            set { _identifier = value; }
        }

        /// <summary>
        /// The space between one pcb and another to allow for wastage in cutting.
        /// </summary>
        public int BorderSpace
        {
            get { return _borderSpace; }
            set { _borderSpace = value; }
        }

        /// <summary>
        /// The area of the pcb including border space to the right and below.
        /// </summary>
        public int Area
        {
            get { return (_width + _borderSpace) * (_height + _borderSpace); }
        }

        /// <summary>
        /// Constructs a pcb object.
        /// </summary>
        /// <param name="width"></param>
        /// <param name="height"></param>
        /// <param name="identifier"></param>
        public Pcb(int width, int height, char identifier, int borderSpace)
        {
            _width = width;
            _height = height;
            _identifier = identifier;
            _borderSpace = borderSpace;
        }

        /// <summary>
        /// Updates the array that holds the position of each pcb in a potential solution.
        /// </summary>
        /// <param name="pcbIdentifier">The character that identifies the pcb.</param>
        /// <param name="originX">The x coordinate of the topleft corner of the pcb in the array
        /// </param>
        /// <param name="originY">The y coordinate of the topleft corner of the pcb in the array.
        /// </param>
        /// <param name="occupied">The array of pcbs positioned so far.</param>
        /// <returns>The array of pcbs positioned so far, updated with this pcb.</returns>
        public char[,] UpdateOccupiedArray(char pcbIdentifier, int originX, int originY, char[,] occupied)
        {
            for (int x = originX; x < originX + _width + _borderSpace; x++)
            {
                for (int y = originY; y < originY + _height + _borderSpace; y++)
                {
                    if (y >= originY + _height)
                    {
                        occupied[x, y] = '-';
                    }
                    else if (x >= originX + _width)
                    {
                        occupied[x, y] = '|';
                    }
                    else
                    {
                        occupied[x, y] = pcbIdentifier;
                    }
                }
            }

            return occupied;
        }

        /// <summary>
        /// Used when sorting to get the pcb's in the height descending order.
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public int CompareTo(Pcb other)
        {
            if (this.Height != other.Height)
                return other.Height - this.Height;
            else
                return other.Width - this.Width;
        }
    }
}
