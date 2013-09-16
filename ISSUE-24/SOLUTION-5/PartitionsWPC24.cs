/* Author: loloto
 * Works fast with numbers up to 33-34!
 * 
 * Task:
 * Write code which calculate the number of ways you can express positive natural number N as sum of positive natural numbers:
 * 
 * Example:
 * for N=1 we have 1 way
 * for N=3 we have 3 ways
 * 1+1+1
 * 1+2
 * 3
 * etc.
 * */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

class PartitionsWPC24
{
    static void Main(string[] args)
    {
        //for (int i = 0; i < 33; i++)
        //{
        //    Console.WriteLine(PartitionFunctionP(i));
        //}
        Console.Write("Enter positive integer number n (up to 33 please): ");
        int n;
        int.TryParse(Console.ReadLine(), out n);
        Console.WriteLine("The number of different partitions of the number {0}:", n);
        Console.WriteLine(PartitionFunctionP(n));
    }

    static long PartitionFunctionP(int n)
    {
        if (n > 0) // recurusion
        {
            long numberOfPartitions = 0;
            int consCounter = 0;
            int k;
            long pentN;

            do
            {
                consCounter++;
                k = GetNumberKFromConsecutive(consCounter);
                pentN = PentagonalNumber(k);
                numberOfPartitions += (long)Math.Pow(-1, k - 1) * PartitionFunctionP((int)(n - pentN));
            } while (n - pentN > 0);

            return numberOfPartitions;
        }
        else // bu definition
        {
            if (n == 0)
            {
                return 1;
            }

            if (n < 0)
            {
                return 0;
            }
        }

        // stupid VS
        return -1;
    }

    static long PentagonalNumber(int k)
    {
        return k*(3*k - 1) / 2;
    }

    /// <summary>
    /// Generating the correct coefficient of the sequence 1, -1, 2, -2 ... from given position (1-based).
    /// </summary>
    /// <param name="n"></param>
    /// <returns></returns>
    static int GetNumberKFromConsecutive(int n)
    {
        int k;
        if (n % 2 == 0)
        {
            k = - (n / 2);
        }
        else
        {
            k = (n / 2) + 1;
        }
        return k;
    }
}
