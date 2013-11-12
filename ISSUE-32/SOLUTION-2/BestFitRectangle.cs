using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WPC32_PCB_panelization
{
    public class BestFitRectangle
    {
        private List<Pcb> _initialList;
        private char[,] _occupied;
        private char[,] _bestFit;

        /// <summary>
        /// Constructs the object that calculates the best-fit solution.
        /// </summary>
        /// <param name="listOfRectangles"></param>
        public BestFitRectangle(List<Pcb> listOfRectangles)
        {
            _initialList = listOfRectangles;
        }

        /// <summary>
        /// Finds the best-fit solution for the pcbs.
        /// </summary>
        /// <returns>The array that holds the best-fit solution.</returns>
        public char[,] Calculate()
        {
            // General counter for iterating through the list.
            int pcbIndex = 0;
            
            int bestFitArea = int.MaxValue;

            // Start off with a bounding box that's the same height as the tallest pcb.
            // The tallest pcb is always the first pcb in the list.
            int boundingBoxHeight = GetBoxInitialHeight(_initialList);

            // The most inefficient solution will be a bounding box that's as wide
            // as the sum of the widths of all pcbs in the initial list.
            int boundingBoxWidth = GetBoxMaximumWidth(_initialList);

            // What's the total area of the pcbs?
            int pcbArea = GetTotalAreaOfPcbs(_initialList);

            // What's the width of the widest pcb?
            int pcbLargestWidth = GetWidestPcb(_initialList);


            while (boundingBoxWidth > pcbLargestWidth)
            {
                // Let's look for a solution that fits within the bounding box.
                // We'll keep track of which cells within the bounding box are occupied.
                _occupied = new char[boundingBoxWidth, boundingBoxHeight];

                // Now go through each pcb and fit each at a position that's as high as possible
                // in the bounding box.
                bool allPcbsFitInBoundingArea = true;
                for (pcbIndex = 0; pcbIndex < _initialList.Count; pcbIndex++)
                {
                    Point topLeft = PositionPcbWithinBox(_initialList[pcbIndex], _occupied);

                    if (topLeft == null)
                    {
                        // We couldn't find a slot for the pcb within the dimensions of the 
                        // occupied array.  We can't fit this pcb in the bounding area
                        // so don't bother looking for the other pcbs.
                        allPcbsFitInBoundingArea = false;
                        break;
                    }
                    else
                    {
                        // Add the pcb to the occupied array.  This could do with refactoring.
                        _occupied = _initialList[pcbIndex].UpdateOccupiedArray(
                            _initialList[pcbIndex].Identifier, 
                            topLeft.X, 
                            topLeft.Y, 
                            _occupied);
                    }
                    //Common.DrawSolution(_occupied);
                }

                if (allPcbsFitInBoundingArea)
                {
                    // OK, we have a solution, but is it the best one?
                    // Reduce the right hand edge of the bounding box to fit the rectangles.
                    bool foundRightEdge = false;
                    int x, y;
                    for (x = _occupied.GetUpperBound(0); x > 0; x--)
                    {
                        for (y = 0; y <= _occupied.GetUpperBound(1); y++)
                        {
                            if (_occupied[x, y] != 0)
                            {
                                foundRightEdge = true;
                                break;
                            }
                        }
                        if (foundRightEdge) break;
                    }

                    // If this solution takes up less space than the best fit solution so far,
                    // make this solution the best fit one.
                    int boundingArea = (_occupied.GetUpperBound(1) + 1) * (x + 1);
                    if (boundingArea < bestFitArea)
                    {
                        _bestFit = CopyOccupiedToBestFit(_occupied, x + 1);
                    }
                    //Common.DrawSolution(_bestFit);
                }
                else
                {
                    // We couldn't fit all the pcbs in the bounding box so increase the height
                    // and try again.
                    boundingBoxHeight++;
                }

                // There could be other solutions that are better fits than what we've found
                // so far, so reduce the width of the bounding rectangle by one and try again.
                boundingBoxWidth--;

                // First check that the size of the bounding box is larger than the
                // total area of the pcbs we're trying to fit in it.  If it is smaller,
                // we don't have to check a solution because we won't be able to fit them
                // all in.  So increase the height by 1 and try again.
                while (pcbArea > boundingBoxHeight * boundingBoxWidth)
                {
                    boundingBoxHeight++;

                    // If the bounding box is now bigger than the best fit so far, it's 
                    // not going to give us a viable best fit.  If so, reduce the width of 
                    // the bounding box.
                    if (bestFitArea < boundingBoxHeight * boundingBoxWidth)
                    {
                        boundingBoxWidth--;
                    }
                }
            }

            return _bestFit;
        }

        /// <summary>
        /// Finds a position for the pcb in the occupied array.
        /// </summary>
        /// <param name="pcb">The pcb to find a position for.</param>
        /// <param name="occupied">The array that holds the position of all other pcbs
        /// fitted so far.</param>
        /// <returns>The point in the occupied array for the top-left corner of the pcb.
        /// If we couldn't find a position for the pcb, null is returned.</returns>
        private Point PositionPcbWithinBox(Pcb pcb, char[,] occupied)
        {
            // Initialise the return value.
            Point topLeft = null;
            int x = 0, y = 0;

            // Scan through the occupied array to find the best position for the pcb.
            while (x <= occupied.GetUpperBound(0))
            {
                while (y <= occupied.GetUpperBound(1))
                {
                    if (occupied[x, y] == 0)
                    {
                        // The cell is not occupied so we need to find out how many more
                        // empty cells there are vertically before we hit the bounding box's 
                        // bottom row.  If there aren't enough cells for the pcb's height, 
                        // it won't fit.
                        int emptyVerticalCells = 0;

                        // Remember the top left corner of the pcb in the array if we find
                        // that the pcb will fit here.
                        Point pcbOrigin = new Point(x, y);

                        while (y <= occupied.GetUpperBound(1) && occupied[x, y] == 0)
                        {
                            emptyVerticalCells++;
                            if (pcb.Height + pcb.BorderSpace == emptyVerticalCells)
                            {
                                // The pcb will fit vertically in this gap, but will it fit horizontally?
                                // We need to scan the cells in each of the rows the pcb will take up.
                                bool validArea = true;
                                for (int y1 = pcbOrigin.Y; y1 < pcbOrigin.Y + pcb.Height + pcb.BorderSpace; y1++)
                                {
                                    for (int x1 = pcbOrigin.X; x1 < pcbOrigin.X + pcb.Width + pcb.BorderSpace; x1++)
                                    {
                                        if (x1 > occupied.GetUpperBound(0))
                                        {
                                            validArea = false;
                                            break;
                                        }

                                        if (occupied[x1, y1] != 0)
                                        {
                                            validArea = false;
                                            break;
                                        }
                                    }
                                    if (!validArea) break;
                                }

                                if (validArea)
                                {
                                    // It can be used by the pcb so grab it.
                                    topLeft = pcbOrigin;
                                    break;
                                }
                            }
                            
                            y++;
                        }
                    }

                    if (topLeft != null) break;
                    y++;
                }

                if (topLeft != null) break;
                x++;
                y = 0;
            }

            return topLeft;
        }

        /// <summary>
        /// Gets the maximum width of the bounding box based on the widths of all the pcbs.
        /// </summary>
        /// <param name="pcbs">The list of pcbs</param>
        /// <returns>The sum of the widths of all pcbs plus the cutting border</returns>
        private int GetBoxMaximumWidth(List<Pcb> pcbs)
        {
            int maxWidth = 0;

            foreach (Pcb p in pcbs)
            {
                maxWidth += (p.Width + p.BorderSpace);
            }

            return maxWidth;
        }

        /// <summary>
        /// Gets the height of the tallest pcb in the list.
        /// </summary>
        /// <param name="pcbs">The list of pcbs.</param>
        /// <returns>The height of the tallest pcb plus the cutting border.</returns>
        private int GetBoxInitialHeight(List<Pcb> pcbs)
        {
            return _initialList[0].Height + _initialList[0].BorderSpace;
        }

        /// <summary>
        /// Gets the width of the widest pcb in the list.
        /// </summary>
        /// <param name="pcbs">The list of pcbs.</param>
        /// <returns>The width of the widest pcb plus the cutting border.</returns>
        private int GetWidestPcb(List<Pcb> pcbs)
        {
            int widestPcb = 0;

            foreach (Pcb p in pcbs)
            {
                if (p.Width + p.BorderSpace > widestPcb)
                {
                    widestPcb = p.Width + p.BorderSpace;
                }
            }
            return widestPcb;
        }

        /// <summary>
        /// Gets the total area taken by all pcbs in the list, including space 
        /// for the cutting border.
        /// </summary>
        /// <param name="pcbs">The list of pcbs.</param>
        /// <returns>The sum of the area of all pcbs in the list, including the cutting
        /// border for each.</returns>
        private int GetTotalAreaOfPcbs(List<Pcb> pcbs)
        {
            int totalArea = 0;

            foreach (Pcb p in pcbs)
            {
                totalArea += p.Area;
            }
            return totalArea;
        }

        /// <summary>
        /// Copy the current solution to a new best-fit array and return it.
        /// </summary>
        /// <param name="occupied">The current solution.</param>
        /// <param name="rightEdge">The x coordinate of the right-hand edge that encompasses
        /// all of the pcbs.  This may be a lot less than the right-hand edge of the occupied
        /// array.</param>
        /// <returns>The best-fit array.</returns>
        private char[,] CopyOccupiedToBestFit(char[,] occupied, int rightEdge)
        {
            char[,] bestFit = new char[rightEdge, occupied.GetUpperBound(1) + 1];

            for (int y = 0; y <= _occupied.GetUpperBound(1); y++)
            {
                for (int x = 0; x < rightEdge; x++)
                {
                    bestFit[x, y] = occupied[x, y];
                }
            }
            return bestFit;
        }
    }
}
