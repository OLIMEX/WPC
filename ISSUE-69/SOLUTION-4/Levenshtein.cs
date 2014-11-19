using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WPC69_LevenshteinDistance
{
    public class Levenshtein
    {
        private string source;
        private string target;
        private int[,] matrix;

        public Levenshtein(string source, string target)
        {
            this.source = source;
            this.target = target;
        }

        public int CalculateDistance()
        {
            int s, t;

            // New matrix to hold our calculation results.
            matrix = new int[source.Length + 1, target.Length + 1];

            // Seed the matrix for the first character in the source word.
            for (s = 1; s <= source.Length; s++)
            {
                matrix[s, 0] = s;
            }

            // Seed the matrix for the first character in the target word.
            for (t = 1; t <= target.Length; t++)
            {
                matrix[0, t] = t;
            }

            for (t = 1; t <= target.Length; t++)
            {
                for (s = 1; s <= source.Length; s++)
                {
                    if (source[s - 1] == target[t - 1])
                    {
                        matrix[s, t] = matrix[s - 1, t - 1];
                    }
                    else
                    {
                        matrix[s, t] = 
                            Math.Min(Math.Min(matrix[s - 1, t] + 1, 
                                              matrix[s, t - 1] + 1), 
                                              matrix[s - 1, t - 1] + 1);
                    }
                }
            }

            // Return the calculated Levenshtein distance
            return matrix[source.Length, target.Length];
        }

        public int[,] GetMatrix()
        {
            return matrix;
        }
    }
}
