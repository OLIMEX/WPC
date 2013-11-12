using System;
using System.Collections.Generic;
using System.IO;

namespace WPC32_PCB_panelization
{
    class Program
    {
        /// <summary>
        /// The size of gap between pcbs (to allow for cutting)
        /// </summary>
        const int BorderSpace = 2;

        static void Main(string[] args)
        {
            // We'll write results out to a text file
            StreamWriter sw = new StreamWriter(
                Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "results.txt"));

            // Small test
            List<Pcb> list = SetupTest1();
            DoWork(list, sw);

            // Medium test
            list = SetupTest2();
            DoWork(list, sw);

            // Large test
            list = SetupTest3();
            DoWork(list, sw);

            sw.Close();
            Console.Write("Press any key to quit...");
            Console.Read();
        }

        private static void DoWork(List<Pcb> list, StreamWriter sw)
        {
            // Calculate best-fit rectangle
            BestFitRectangle calculator = new BestFitRectangle(list);
            char[,] bestFit = calculator.Calculate();

            // Display the best fit solution.
            Common.DrawSolution(bestFit, BorderSpace, sw);
        }

        /// <summary>
        /// Small test
        /// </summary>
        /// <returns></returns>
        private static List<Pcb> SetupTest1()
        {
            List<Pcb> list = new List<Pcb>();
            list.Add(new Pcb(2, 4, 'A', BorderSpace));
            list.Add(new Pcb(3, 3, 'B', BorderSpace));
            list.Add(new Pcb(1, 1, 'C', BorderSpace));
            list.Add(new Pcb(5, 5, 'D', BorderSpace));
            list.Add(new Pcb(3, 6, 'E', BorderSpace));
            list.Add(new Pcb(2, 2, 'F', BorderSpace));
            list.Add(new Pcb(6, 1, 'G', BorderSpace));

            // Sort them into height descending order.
            list.Sort();
            return list;
        }

        /// <summary>
        /// Medium test
        /// </summary>
        /// <returns></returns>
        private static List<Pcb> SetupTest2()
        {
            List<Pcb> list = new List<Pcb>();
            list.Add(new Pcb(20, 31, 'A', BorderSpace));
            list.Add(new Pcb(15, 18, 'B', BorderSpace));
            list.Add(new Pcb(1, 2, 'C', BorderSpace));
            list.Add(new Pcb(2, 1, 'D', BorderSpace));
            list.Add(new Pcb(2, 1, 'E', BorderSpace));
            list.Add(new Pcb(19, 17, 'F', BorderSpace));
            list.Add(new Pcb(8, 25, 'G', BorderSpace));
            list.Add(new Pcb(32, 25, 'H', BorderSpace));
            list.Add(new Pcb(17, 17, 'I', BorderSpace));
            list.Add(new Pcb(10, 10, 'J', BorderSpace));
            list.Add(new Pcb(26, 13, 'K', BorderSpace));
            list.Add(new Pcb(13, 26, 'L', BorderSpace));

            // Sort them into height descending order.
            list.Sort();
            return list;
        }

        /// <summary>
        /// Large test
        /// </summary>
        /// <returns></returns>
        private static List<Pcb> SetupTest3()
        {
            List<Pcb> list = new List<Pcb>();
            list.Add(new Pcb(1, 1, 'A', BorderSpace));
            list.Add(new Pcb(2, 2, 'B', BorderSpace));
            list.Add(new Pcb(3, 4, 'C', BorderSpace));
            list.Add(new Pcb(4, 5, 'D', BorderSpace));
            list.Add(new Pcb(5, 6, 'E', BorderSpace));
            list.Add(new Pcb(6, 6, 'F', BorderSpace));
            list.Add(new Pcb(7, 7, 'G', BorderSpace));
            list.Add(new Pcb(8, 8, 'H', BorderSpace));
            list.Add(new Pcb(9, 9, 'I', BorderSpace));
            list.Add(new Pcb(10, 10, 'J', BorderSpace));
            list.Add(new Pcb(11, 11, 'K', BorderSpace));
            list.Add(new Pcb(12, 12, 'L', BorderSpace));
            list.Add(new Pcb(13, 13, 'M', BorderSpace));
            list.Add(new Pcb(14, 14, 'N', BorderSpace));
            list.Add(new Pcb(15, 15, 'O', BorderSpace));
            list.Add(new Pcb(16, 16, 'P', BorderSpace));
            list.Add(new Pcb(17, 17, 'Q', BorderSpace));
            list.Add(new Pcb(18, 18, 'R', BorderSpace));
            list.Add(new Pcb(19, 19, 'S', BorderSpace));
            list.Add(new Pcb(20, 20, 'T', BorderSpace));

            // Sort them into height descending order.
            list.Sort();
            return list;
        }

    }
}
