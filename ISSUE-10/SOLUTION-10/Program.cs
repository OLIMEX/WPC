using System;
using System.Collections.Generic;

namespace Olimex_Programming_Challenge_10
{
    /// <summary>
    /// Olimex Programming Challenge 10 - May 2013
    /// 
    /// Problem:
    /// Let 0 &lt; (a/b) &lt; 1 where a and b are positive integers.
    /// 
    /// Make program which enters the numbers a and b then represent a/b with a
    /// sum of numbers 1/n + 1/n2 + 1/n3 ... and prints the n numbers.
    /// 
    /// For instance:
    /// input:  a = 6
    ///         b = 7
    /// output: 2, 3, 42
    ///         i.e. 6/7 = 1/2 + 1/3 + 1/42
    ///         
    /// input:  a = 3
    ///         b = 4
    /// output: 2, 4
    ///         as 3/4 = 1/2 + 1/4
    /// </summary>
    /// 
    /// <solution>
    /// Use long values throughout; no floating points as this will be slow and comparing will be inaccurate.
    /// 
    /// 1.  Refactor the input fraction a/b into a*a/a*b.  This allows us to use longs throughout as the 
    ///     smallest fraction (1/n) in the output will be 1/a*b.
    /// 
    /// 2.  The starting residual is a*a.  This will be reduced gradually in the loop below as we find 
    ///     suitable fractions.
    /// 
    /// 3.  Start with a divisor of 2 (i.e. 1/2) and calculate a*b/2.
    /// 
    /// 4.  If there's a remainder, then 1/divisor is not a valid fraction for the output. 
    ///     Bump the divisor and check that.
    ///    
    /// 5.  If there's no remainder, it's a valid fraction for the output.
    ///     Add the divisor to the output.
    ///     But it's eminently possible for there to be several of these divisors to add to the 
    ///     results so calculate how many and add them too.
    /// 
    /// 6.  Reduce the residual (a*a) by the divisor * the number added to the output.
    /// 
    /// 7.  Check the remainder and residual.
    ///     If they're not both 0, bump the divisor and loop round again.
    ///     If they are both 0, we're done.  Return the list of valid divisors.
    /// </solution>
    class Program
    {
        static void Main(string[] args)
        {
            while (true)
            {
                // Get the inputs from the user.
                Console.WriteLine("Calculate sum of fractions (Hit Return without entering to quit)");
                Console.WriteLine("e.g. for a=6 and b=7, output n will be 2, 3, 42");
                Console.WriteLine("i.e. 6/7 = 1/2 + 1/3 + 1/42");
                Console.WriteLine();

                Console.Write("Enter fraction numerator     a : ");
                string num = Console.ReadLine();
                if (string.IsNullOrWhiteSpace(num)) break;

                Console.Write("Enter fraction denominator   b : ");
                string denom = Console.ReadLine();
                if (string.IsNullOrWhiteSpace(denom)) break;
                Console.WriteLine();

                // Inputs are strings so we need to convert them into longs.
                long inNumerator;
                long inDenominator;

                if (long.TryParse(num, out inNumerator) && long.TryParse(denom, out inDenominator))
                {
                    if (inDenominator == 0)
                        Console.WriteLine("ERROR : Invalid denominator.");
                    else if (inNumerator >= inDenominator)
                        Console.WriteLine("ERROR : Fraction must be in the range 0 < fraction < 1.");
                    else
                    {
                        // These are used to test that the sum of the fractions found equals
                        // the input fraction.
                        double sumFractions = 0;
                        double inFraction = (double)inNumerator / (double)inDenominator;

                        // All set up so go get 'em Floyd!
                        Denominators denoms = new Denominators(inNumerator, inDenominator);
                        List<long> denominators = denoms.CalculateDenominators();

                        // Display them nicely formatted on one line.
                        Console.Write("Fractional denominators are  n : ");
                        for (int i = 0; i < denominators.Count; i++)
                        {
                            if (i + 1 != denominators.Count)
                                // All but the last value in the list.
                                Console.Write(denominators[i] + ", ");
                            else
                                // Last value in the list.
                                Console.WriteLine(denominators[i]);

                            // Add the fraction to the total so we can compare the final result against
                            // the input fraction.
                            sumFractions += 1 / (double)denominators[i];
                        }

                        // Display whether we've calculated the right fractions.
                        // The 2 values displayed should be the same.
                        Console.WriteLine();
                        Console.WriteLine("Input decimal value : {0}", inFraction);
                        Console.WriteLine("Sum of fractions    : {0}", sumFractions);
                    }
                }
                else
                {
                    Console.WriteLine("ERROR : Invalid values.");
                }
                Console.WriteLine();
                Console.WriteLine("----------------------------------------------------------------");
                Console.WriteLine();
            }
        }
    }
}
