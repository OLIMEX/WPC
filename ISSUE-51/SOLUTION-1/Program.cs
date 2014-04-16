using System;
using System.Collections.Generic;
using System.IO;

namespace WPC51_ContainerLoad
{
    class Program
    {
        const int ContainerWidthX = 20;
        const int ContainerDepthZ = 8;
        const int ContainerHeightY = 8;

        /// <summary>
        /// The program's entry point
        /// </summary>
        /// <param name="args">Ignored</param>
        static void Main(string[] args)
        {
            // We'll write results out to a text file
            StreamWriter sw = new StreamWriter(
                Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "results.txt"));

            // Run some simulated loads
            LoadContainer(SetupTest1(), sw);
            LoadContainer(SetupTest2(), sw);
            LoadContainer(SetupTest3(), sw);

            sw.Close();
            Console.WriteLine("Press a key to quit...");
            Console.Read();
        }

        /// <summary>
        /// Load a new empty container with the supplied list of boxes.
        /// </summary>
        /// <param name="boxes">The boxes to be loaded into the container</param>
        /// <param name="sw">The output log file</param>
        private static void LoadContainer(List<Box> boxes, StreamWriter sw)
        {
            // Setup an empty container with the desired size.
            Container container = new Container(ContainerWidthX, ContainerHeightY, ContainerDepthZ);

            LargestAreaFirstFit laff = new LargestAreaFirstFit(boxes, container);
            container = laff.Calculate();

            // Show where the boxes are now located in the container
            ShowContainer(container, sw);
        }

        /// <summary>
        /// Display and write out to a text file how the boxes have been loaded into
        /// the container.
        /// </summary>
        /// <param name="container">The loaded container</param>
        /// <param name="sw">The output log file</param>
        private static void ShowContainer(Container container, StreamWriter sw)
        {
            // Show how the boxes have fitted into the container.
            int occupiedCellCount = 0;
            int totalCellCount = container.WidthX * container.HeightY * container.DepthZ;

            for (int y = 0; y < container.HeightY; y++)
            {
                Console.WriteLine("Plane Y={0}", y);
                sw.WriteLine("Plane Y={0}", y);

                for (int z = 0; z < container.DepthZ; z++)
                {
                    for (int x = 0; x < container.WidthX; x++)
                    {
                        if (container.Occupied[x, y, z] == '.')
                        {
                            Console.Write(". ");
                            sw.Write(". ");
                        }
                        else
                        {
                            occupiedCellCount++;
                            Console.Write("{0} ", container.Occupied[x, y, z]);
                            sw.Write("{0} ", container.Occupied[x, y, z]);
                        }
                    }

                    Console.WriteLine();
                    sw.WriteLine();
                }

                Console.WriteLine();
                sw.WriteLine();
            }

            // Show whether any boxes couldn't be fitted into the container.
            if (container.BoxesNotFitted.Count > 0)
            {
                string notFitted = string.Empty;
                for (int i = 0; i < container.BoxesNotFitted.Count; i++)
                {
                    if (i == 0)
                    {
                        notFitted += container.BoxesNotFitted[i].Identifier.ToString();
                    }
                    else
                    {
                        notFitted += string.Format(", {0}", container.BoxesNotFitted[i].Identifier);
                    }
                }
                Console.WriteLine("Boxes that couldn't be fitted are : {0}", notFitted);
                Console.WriteLine();
                sw.WriteLine("Boxes that couldn't be fitted are : {0}", notFitted);
                sw.WriteLine();
            }

            // Show how much of the container is filled / empty
            double fillRate = occupiedCellCount * 100 / totalCellCount;
            Console.WriteLine("Percentage full = {0:0.0}%", fillRate);
            sw.WriteLine("Percentage full = {0:0.0}%", fillRate);

            Console.WriteLine();
            sw.WriteLine();

            // Leave a blank line between tests.
            Console.WriteLine(string.Empty.PadRight(80, '='));
            sw.WriteLine(string.Empty.PadRight(80, '='));
        }

        /// <summary>
        /// Test with boxes of various sizes.
        /// </summary>
        /// <returns>The list of boxes</returns>
        private static List<Box> SetupTest1()
        {
            List<Box> list = new List<Box>();
            list.Add(new Box(12, 4, 5, 'a'));
            list.Add(new Box(4, 8, 2, 'b'));
            list.Add(new Box(10, 3, 2, 'c'));
            list.Add(new Box(10, 5, 3, 'd'));
            list.Add(new Box(4, 3, 3, 'e'));
            list.Add(new Box(2, 8, 1, 'f'));
            list.Add(new Box(10, 5, 2, 'g'));
            list.Add(new Box(5, 3, 5, 'h'));
            list.Add(new Box(20, 1, 5, 'i'));
            list.Add(new Box(16, 2, 6, 'j'));
            list.Add(new Box(5, 1, 5, 'k'));
            list.Add(new Box(3, 7, 3, 'l'));
            list.Add(new Box(3, 3, 3, 'm'));

            // Sort them into descending order according to the surface area
            // of their XZ side and height.
            list.Sort();
            return list;
        }

        /// <summary>
        /// Test using lots of boxes of the same size
        /// </summary>
        /// <returns>The list of boxes</returns>
        private static List<Box> SetupTest2()
        {
            List<Box> list = new List<Box>();
            list.Add(new Box(3, 3, 3, 'a'));
            list.Add(new Box(3, 3, 3, 'b'));
            list.Add(new Box(3, 3, 3, 'c'));
            list.Add(new Box(3, 3, 3, 'd'));
            list.Add(new Box(3, 3, 3, 'e'));
            list.Add(new Box(3, 3, 3, 'f'));
            list.Add(new Box(3, 3, 3, 'g'));
            list.Add(new Box(3, 3, 3, 'h'));
            list.Add(new Box(3, 3, 3, 'i'));
            list.Add(new Box(3, 3, 3, 'j'));
            list.Add(new Box(3, 3, 3, 'k'));
            list.Add(new Box(3, 3, 3, 'l'));
            list.Add(new Box(3, 3, 3, 'm'));
            list.Add(new Box(3, 3, 3, 'n'));
            list.Add(new Box(3, 3, 3, 'o'));
            list.Add(new Box(3, 3, 3, 'p'));
            list.Add(new Box(3, 3, 3, 'q'));
            list.Add(new Box(3, 3, 3, 'r'));
            list.Add(new Box(3, 3, 3, 's'));
            list.Add(new Box(3, 3, 3, 't'));
            list.Add(new Box(3, 3, 3, 'u'));
            list.Add(new Box(3, 3, 3, 'v'));
            list.Add(new Box(3, 3, 3, 'w'));
            list.Add(new Box(3, 3, 3, 'x'));
            list.Add(new Box(3, 3, 3, 'y'));
            list.Add(new Box(3, 3, 3, 'z'));

            // Sort them into descending order according to the surface area
            // of their XZ side and height.
            list.Sort();
            return list;
        }

        /// <summary>
        /// Test using lots of boxes (full to the gunnals)
        /// </summary>
        /// <returns>The list of boxes</returns>
        private static List<Box> SetupTest3()
        {
            List<Box> list = new List<Box>();
            list.Add(new Box(4, 4, 4, 'a'));
            list.Add(new Box(4, 4, 4, 'b'));
            list.Add(new Box(4, 4, 4, 'c'));
            list.Add(new Box(4, 4, 4, 'd'));
            list.Add(new Box(4, 4, 4, 'e'));
            list.Add(new Box(4, 4, 4, 'f'));
            list.Add(new Box(4, 4, 4, 'g'));
            list.Add(new Box(4, 4, 4, 'h'));
            list.Add(new Box(4, 4, 4, 'i'));
            list.Add(new Box(4, 4, 4, 'j'));
            list.Add(new Box(4, 4, 4, 'k'));
            list.Add(new Box(4, 4, 4, 'l'));
            list.Add(new Box(4, 4, 4, 'm'));
            list.Add(new Box(4, 4, 4, 'n'));
            list.Add(new Box(4, 4, 4, 'o'));
            list.Add(new Box(4, 4, 4, 'p'));
            list.Add(new Box(4, 4, 4, 'q'));
            list.Add(new Box(4, 4, 4, 'r'));
            list.Add(new Box(4, 4, 4, 's'));
            list.Add(new Box(4, 4, 4, 't'));
            list.Add(new Box(4, 4, 4, 'u'));

            // Sort them into descending order according to the surface area
            // of their XZ side and height.
            list.Sort();
            return list;
        }
    }
}
