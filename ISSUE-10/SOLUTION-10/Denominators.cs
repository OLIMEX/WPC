using System.Collections.Generic;

namespace Olimex_Programming_Challenge_10
{
    public class Denominators
    {
        private long numerator;
        private long denominator;

        public Denominators(long numerator, long denominator)
        {
            this.numerator = numerator;
            this.denominator = denominator;
        }

        /// <summary>
        /// Using the fraction supplied in the constructor, calculate the 1/n fractions that collectively
        /// sum to the same value as the supplied fraction.
        /// </summary>
        /// <returns>The list of fractional denominators that when summed equate to the supplied fraction.
        /// This is the list of n values, not the 1/n floating point values.
        /// </returns>
        public List<long> CalculateDenominators()
        {
            // Create a list to hold the fractional denominators (n values) we find.
            List<long> denoms = new List<long>();

            // Revalue the fraction as the maximum fractional value could be 1 / (denominator * numerator).
            // This allows us to work totally with longs.
            denominator = denominator * numerator;
            numerator = numerator * numerator;

            // Initialize the residual.
            long residual = numerator;

            // The big loop where we test each divisor to detect a valid fraction for the sum.
            // We start with the biggest fraction first, i.e. 1/2.
            for (long divisor = 2; divisor <= denominator; divisor++)
            {
                long testDivide = denominator / divisor;
                long remainder = denominator % divisor;

                if (remainder == 0 && residual - testDivide >= 0)
                {
                    // How many 1/divisor fractions do we need to report?
                    // It's perfectly possible that we need more than one 1/divisor in 
                    // the results so calculate how many and add them.
                    long noOfDivisors = residual / testDivide;
                    for (int j = 0; j < noOfDivisors; j++)
                    {
                        denoms.Add(divisor);
                    }

                    // Reduce the residual that's left.
                    residual -= testDivide * noOfDivisors;
                }

                // When there's no remainder and no residual left, we're done.
                if (remainder == 0 && residual == 0)
                {
                    break;
                }
            }

            return denoms;
        }
    }
}
