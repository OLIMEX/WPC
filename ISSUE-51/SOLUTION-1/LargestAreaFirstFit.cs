using System.Collections.Generic;

namespace WPC51_ContainerLoad
{
    public class LargestAreaFirstFit
    {
        private List<Box> boxes;
        private Container container;

        /// <summary>
        /// Constructs an instance of the object with the list of boxes
        /// and the container they should fit into.
        /// </summary>
        /// <param name="boxes">The boxes to fit into the container</param>
        /// <param name="container">The container</param>
        public LargestAreaFirstFit(List<Box> boxes, Container container)
        {
            this.boxes = boxes;
            this.container = container;
        }

        /// <summary>
        /// Try to fit each box into the container.
        /// </summary>
        /// <returns></returns>
        public Container Calculate()
        {
            // Try to fit the boxes in order
            for (int boxIndex = 0; boxIndex < boxes.Count; boxIndex++)
            {
                Box box = boxes[boxIndex];
                bool boxFits = TryToFitBoxInsideContainer(box, container);
            }

            return container;
        }

        /// <summary>
        /// Try to fit the box inside the container.
        /// </summary>
        /// <param name="box">The box to fit into the container</param>
        /// <param name="container">The container</param>
        /// <returns>true if it has been fitted; false if no space for the box</returns>
        private bool TryToFitBoxInsideContainer(Box box, Container container)
        {
            int originX, originY, originZ;
            bool boxFitted = false;

            // Scan the floor of the container first.
            for (originY = 0; originY < container.HeightY; originY++)
            {
                for (originZ = 0; originZ < container.DepthZ; originZ++)
                {
                    for (originX = 0; originX < container.WidthX; originX++)
                    {
                        if (container.Occupied[originX, originY, originZ] == '.')
                        {
                            // This point (cell) in the container is empty so
                            // see if the whole box would fit within the bounds of
                            // the container at this position.
                            if (originX + box.WidthX > container.WidthX ||
                                originZ + box.DepthZ > container.DepthZ ||
                                originY + box.HeightY > container.HeightY)
                            {
                                break;
                            }

                            // OK, so the box doesn't extend beyond the bounds of the
                            // container but are any of the cells it would occupy 
                            // already taken by another box?  If there are, this box
                            // won't fit here.
                            int yScan = 0, xScan = 0, zScan = 0;
                            bool fits = true;       // assume it fits unless we find otherwise
                            for (yScan = originY; yScan < originY + box.HeightY; yScan++)
                            {
                                for (zScan = originZ; zScan < originZ + box.DepthZ; zScan++)
                                {
                                    for (xScan = originX; xScan < originX + box.WidthX; xScan++)
                                    {
                                        if (container.Occupied[xScan, yScan, zScan] != '.')
                                        {
                                            fits = false;
                                            break;
                                        }
                                    }

                                    if (!fits) break;
                                }

                                if (!fits) break;
                            }

                            // If the box fits here, add it to the container.
                            if (fits)
                            {
                                for (yScan = originY; yScan < originY + box.HeightY; yScan++)
                                {
                                    for (zScan = originZ; zScan < originZ + box.DepthZ; zScan++)
                                    {
                                        for (xScan = originX; xScan < originX + box.WidthX; xScan++)
                                        {
                                            container.Occupied[xScan, yScan, zScan] = box.Identifier;
                                        }
                                    }
                                }

                                boxFitted = true;
                            }

                            if (boxFitted) break;
                        }
                    }

                    if (boxFitted) break;
                }

                if (boxFitted) break;
            }

            // If the box couldn't be fitted, add it to a list so we can show the caller
            // which boxes have been left out.
            if (!boxFitted)
            {
                container.BoxesNotFitted.Add(box);
            }

            // The caller might want to know if the box fitted into the container or not.
            return boxFitted;
        }
    }
}
