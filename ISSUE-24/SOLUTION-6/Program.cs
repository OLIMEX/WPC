using System;

namespace WPC23_Combinatorics
{
    /// <summary>
    /// Problem:
    /// Write code which calculate the number of ways you can express positive natural 
    /// number N as sum of positive natural numbers.
    /// 
    /// Example:
    /// for N=1 we have 1 way
    /// 
    /// for N=3 we have 3 ways
    /// 1+1+1
    /// 1+2
    /// 3
    /// 
    /// *******************************************************************************************
    /// Solution
    /// 
    /// Let's solve this by looking at a tree example for getting all the sum sequences for N = 4.
    /// 
    ///             a = 1                    a = 2               a = 3          a = 4
    ///                 |                        |                   |              |
    ///            ------------               -------             -------
    ///            |          |               |     |             |
    ///        b = 1          2               1     2             1
    ///            |          |               |
    ///         -------    -------         -------
    ///         |     |    |               |
    ///         1     2    1               1
    ///         |
    ///      -------
    ///      |
    ///      1
    /// 
    /// As this is a tree structure, we'll use recursion to solve this challenge.
    /// 
    /// So for 4, this tree should give:
    /// 
    /// 1+1+1+1
    /// 1+1+2
    /// 1+2+1
    /// 2+1+1
    /// 2+2
    /// 3+1
    /// 4
    /// 
    /// Note that 1+1+2 and 1+2+1 and 2+1+1 are effectively all the same so we'll try to eliminate
    /// these duplicates in our solution.  Ideally we should get these:
    /// 
    /// 1+1+1+1
    /// 1+1+2
    /// 2+2
    /// 3+1
    /// 4
    /// 
    /// </summary>
    class Program
    {
        /// <summary>
        /// This will keep track of how many solutions we find.
        /// </summary>
        static int totalWays = 0;

        /// <summary>
        /// Main entry point for the console application.
        /// </summary>
        /// <param name="args"></param>
        static void Main(string[] args)
        {
            bool quit = false;

            // Stay in here until the user tells us to exit.
            while (!quit)
            {
                Console.Write("Enter a positive integer N (or hit Enter to quit) : ");
                string input = Console.ReadLine();

                // Check that we have some input otherwsie inform the user.
                if (input != "")
                {
                    int n;
                    if (int.TryParse(input, out n))
                    {
                        if (n > 0)
                        {
                            // Calculate the sequences of summed numbers and update the total on the way.
                            totalWays = 0;
                            ShowCombinations(n);

                            Console.WriteLine();
                            Console.WriteLine("A total of {0} ways to express N as a sum of positive natural numbers.", totalWays);
                            Console.WriteLine("**************************************************************************");
                        }
                        else
                        {
                            Console.WriteLine("Only positive integers > 0 are allowed; try again");
                        }
                    }
                    else
                    {
                        Console.WriteLine("Invalid number; try again");
                    }
                }
                else
                {
                    quit = true;
                }
                Console.WriteLine();
            }
        }

        /// <summary>
        /// Recurse through the tree for N and output any valid sequences of summed numbers.
        /// </summary>
        /// <param name="n"></param>
        private static void ShowCombinations(int n)
        {
            string combination = string.Empty;

            // Start at the trunk and recurse down through the roots for each number in 
            // the range 1..N-1
            // N will be handled separately afterwards.
            for (int a = 1; a < n; a++)
            {
                int currentSum = a;
                int b = 1;
                combination = a.ToString();

                // Go through each of the numbers in 1..N-1 on the first level down from the trunk.
                while (b < n)
                {
                    Recurse(currentSum, n, a, b, combination);
                    b++;
                }
            }

            // Don't forget the specific case of N on its own.
            totalWays++;
            Console.WriteLine("{0}", n);
        }

        /// <summary>
        /// The guts that works out whether we have a valid sequence and writes it out.  This function
        /// calls itself, hence the name.
        /// </summary>
        /// <param name="currentSum">The current sum of all integers down the root from the trunk.</param>
        /// <param name="n">N, the input number to the program.</param>
        /// <param name="a">The trunk number.</param>
        /// <param name="b">A number on the current level we're looking at.</param>
        /// <param name="combination">The string containing the numbers to the current level from the trunk.
        /// If we find a valid sequence of numbers that add up to N, we'll output it to the console from 
        /// here.</param>
        private static void Recurse(int currentSum, int n, int a, int b, string combination)
        {
            // Keep recursing down the roots while the sum of numbers along the way are less than N.
            while (currentSum < n)
            {
                // Update the sum of numbers down the root.
                currentSum += b;
                combination += "+" + b.ToString();

                // If it's valid, dump it to the console.
                // b >= a skips duplicates that have been found by a previous iteration.
                //if (currentSum == n)      // Use this if you don't want to suppress some duplicates
                if (currentSum == n && b >= a)
                {
                    totalWays++;
                    Console.WriteLine(combination);
                }

                // Not found one yet, so drop to the next level.
                Recurse(currentSum, n, a, b, combination);
                
                // Move horizontally along the level and try the next number on it.
                b++;

                // Make sure we don't go beyond the max expected value along this level.
                if (b >= n) break;
            }
        }
    }
}
