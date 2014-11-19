using System;
using System.IO;

namespace WPC69_LevenshteinDistance
{
    class Program
    {
        private static StreamWriter sw;

        static void Main(string[] args)
        {
            // We'll write results out to a text file
            sw = new StreamWriter(
                Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "results.txt"));

            while (true)
            {
                // Get the user to provide two strings to compare
                Console.Write("Enter source string : ");
                string source = Console.ReadLine();

                Console.Write("Enter target string : ");
                string target = Console.ReadLine();

                // Eye candy
                string divider = string.Empty.PadRight(50, '-');
                WriteLine(divider);
                WriteLine();

                // Do the work and display the result
                Levenshtein calculator = new Levenshtein(source, target);

                string result = string.Format("Levenstein distance = {0}", calculator.CalculateDistance());
                WriteLine(result);
                
                PrettyPrintMatrix(calculator.GetMatrix(), source, target);
            }
        }

        private static void PrettyPrintMatrix(int[,] matrix, string source, string target)
        {
            int i,j;
            string divider;

            WriteLine();
            divider = "       |";
            Write(divider);
            divider += " ";

            for (i = 0; i < source.Length; i++)
            {
                Write(string.Format(" {0,2} |", source[i]));
                divider += "   | ";
            }
            WriteLine();
            WriteLine(divider);

            divider = string.Empty.PadRight(source.Length * 5 + 8, '-');            

            for (i = 0; i <= target.Length; i++)
            {
                if (i == 0)
                    Write("   ");
                else
                    Write(string.Format("{0,2} ", target[i - 1]));

                for (j = 0; j <= source.Length; j++)
                {
                    Write(string.Format(" {0,2} |", matrix[j, i]));
                }
                WriteLine();
                WriteLine(divider);
            }
            WriteLine();
        }

        private static void WriteLine(string text)
        {
            Console.WriteLine(text);
            sw.WriteLine(text);
            sw.Flush();
        }

        private static void WriteLine()
        {
            WriteLine(string.Empty);
        }

        private static void Write(string text)
        {
            Console.Write(text);
            sw.Write(text);
            sw.Flush();
        }
    }
}
