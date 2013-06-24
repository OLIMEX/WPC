using System.Numerics;

namespace Olimex_Programming_Challenge_14
{
    public static class Pi
    {
        /// <summary>
        /// Does exactly what it says on the tin.
        /// </summary>
        /// <param name="requiredDecimalPlaces">How many decimal places do we want to calculate pi to?</param>
        /// <param name="tolerance">Decides when we've got an accrate enough valud for pi.</param>
        /// <param name="iterations">Output value which tells the caller how many iterations we took.</param>
        /// <returns>The value of pi as a string</returns>
        public static string CalculateWithBigInt(
            int requiredDecimalPlaces, 
            int tolerance, 
            out BigInteger iterations)
        {
            // Used to scale the fractions up into big integer values rather than floats or doubles.
            BigInteger scaler = BigInteger.Pow(10, requiredDecimalPlaces);

            bool addition = true;
            BigInteger quarterPi = 0;
            BigInteger lastValue = 0;
            BigInteger divisor = 1;
            iterations = 0;

            // Continue for as many iterations as needed until we get an acceptable value for pi.
            while (true)
            {
                iterations++;

                if (addition)
                {
                    quarterPi += BigInteger.Divide(scaler, divisor);
                }
                else
                {
                    quarterPi -= BigInteger.Divide(scaler, divisor);
                }

                // Test if we've done sufficient iterations by seeing if
                // the current calculation is close enough to the result from
                // the previous iteration.
                if (BigInteger.Abs(BigInteger.Subtract(quarterPi, lastValue)) <= tolerance)
                {
                    break;
                }

                // Setup for next iteration.
                lastValue = quarterPi;
                addition = !addition;
                divisor = BigInteger.Add(divisor, 2);
            }

            // Perform the final calculation.
            BigInteger pi = BigInteger.Multiply(quarterPi, 4);

            // Stringify the BigInteger and insert the decimal point at the right position.
            string sPi = pi.ToString();
            int significantDigits = sPi.Length - requiredDecimalPlaces;
            sPi = string.Format("{0}.{1}", sPi.Substring(0, significantDigits), sPi.Substring(significantDigits));
            return sPi;
        }
    }
}
