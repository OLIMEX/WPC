using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace WPC53_Random_Number_Generator
{
    class Program
    {
        static void Main(string[] args)
        {
            const int minValue = 70;
            const int maxValue = 99;

            // We'll write results out to a text file
            StreamWriter sw = new StreamWriter(
                Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "results.txt"));

            sw.WriteLine("Sample Random Numbers from {0} to {1}", minValue, maxValue);
            sw.WriteLine("-------------------------------------");

            for (int i = 1; i <= 400; i++)
            {
                uint random = Random.Next(minValue, maxValue);
                sw.Write("{0,2} ", random);
                if (i % 20 == 0) sw.WriteLine();
            }
            sw.WriteLine();
            
            CheckDistribution(minValue, maxValue, sw);

            sw.Close();
        }

        static void CheckDistribution(int minValue, int maxValue, StreamWriter sw)
        {
            sw.WriteLine("\nDistribution");
            sw.WriteLine("-------------------------------------");

            int[] counts = new int[maxValue - minValue + 1];
            int sampleSize = 100000000;
            do
            {
                int randomIndex = (int)Random.Next((uint)minValue, (uint)(maxValue));
                counts[randomIndex - minValue]++;
            }
            while (sampleSize-- > 0);

            for (int i = 0; i < counts.Length; i++)
            {
                sw.WriteLine("Value {0,2} Count {1}", minValue + i, counts[i]);
            }
        }
    }
}
