using System;
using System.IO;

namespace WPC32_PCB_panelization
{
    public class Common
    {
        /// <summary>
        /// Draws the solution from the cells in the occupied array.
        /// </summary>
        /// <param name="occupied"></param>
        public static void DrawSolution(char[,] occupied, int borderGap, StreamWriter sw)
        {
            int emptySpaceCount = 0;

            string title = string.Format("Best fit solution is {0} x {1}",
                occupied.GetUpperBound(0) - 1,
                occupied.GetUpperBound(1) - 1);
            Console.WriteLine(title);
            Console.WriteLine();

            sw.WriteLine(title);
            sw.WriteLine();

            // The right most column and lowest row are included in the occupied
            // array so we ignore these as they aren't necessary in practice.
            // You wouldn't cut and waste a border off these edges.
            for (int y = 0; y < occupied.GetUpperBound(1) - borderGap + 1; y++)
            {
                for (int x = 0; x < occupied.GetUpperBound(0) - borderGap + 1; x++)
                {
                    if (occupied[x, y] == 0)
                    {
                        emptySpaceCount++;
                        Console.Write('.');
                        sw.Write('.');
                    }
                    else
                    {
                        Console.Write(occupied[x, y]);
                        sw.Write(occupied[x, y]);
                    }
                }
                Console.WriteLine();
                sw.WriteLine();
            }
            Console.WriteLine();
            Console.WriteLine("Empty spaces = {0}", emptySpaceCount);
            Console.WriteLine();

            sw.WriteLine();
            sw.WriteLine("Empty spaces = {0}", emptySpaceCount);
            sw.WriteLine();
            sw.WriteLine("------------------------------------------------------------------------------------------------");
        }
    }
}
