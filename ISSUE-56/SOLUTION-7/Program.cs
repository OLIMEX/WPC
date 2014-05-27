using System;
using System.IO;
using System.Numerics;

namespace WPC56_Perfect_Numbers
{
    /// <summary>
    /// Calculates perfect numbers using the formula:
    /// 
    /// 2 ^ (n-1) * ( 2^n - 1 )
    /// 
    /// when ( 2^n - 1 ) is prime.
    /// 
    /// This reference was particularly useful:
    /// http://mathforum.org/dr.math/faq/faq.perfect.html#whatis
    /// 
    /// Also the BigInteger structure in C# 4.0 was required as perfect numbers
    /// get quite large very quickly!
    /// </summary>
    class Program
    {
        static void Main(string[] args)
        {
            CalculateUsingBigInteger();
            Console.Read();
        }

        // Calculate perfect numbers using this formula where 2^n - 1 is a Mersenne prime.
        // 2 ^ (n-1) * ( 2^n - 1 )
        private static void CalculateUsingBigInteger()
        {
            BigInteger possiblePrime = 1;
            int power = 1;

            // 1000 is a bit ambitious but ensures we run for a long time.
            // In practice, power got as far as 89 after a day's work.
            while (power < 1000)
            {
                power++;
                Console.WriteLine("Testing p = {0}", power);

                possiblePrime = BigInteger.Pow(2, power) - 1;

                // If it's prime, we can calculate the perfect number.
                if (IsPrime(possiblePrime))
                {
                    BigInteger perfectNumber = BigInteger.Pow(2, power - 1) * possiblePrime;
                    Console.WriteLine("Perfect Number = {0}", perfectNumber);
                }
            }

            return;
        }

        /// <summary>
        /// Work out if the supplied positive integer is prime.
        /// </summary>
        /// <param name="possiblePrime">The number to check.</param>
        /// <returns>true if it's prime</returns>
        private static bool IsPrime(BigInteger possiblePrime)
        {
            BigInteger limit = Sqrt(possiblePrime + 1);
            for (BigInteger i = 3; i <= limit; i += 2)
            {
                if (possiblePrime % i == 0) return false;
            }

            return true;
        }

        /// <summary>
        /// Calculate the square root of a positive integer.
        /// </summary>
        /// <param name="n">the number to root</param>
        /// <returns>the square root of the supplied number</returns>
        private static BigInteger Sqrt(BigInteger n)
        {
            if (n == 0) return 0;
            if (n > 0)
            {
                int bitLength = Convert.ToInt32(Math.Ceiling(BigInteger.Log(n, 2)));
                BigInteger root = BigInteger.One << (bitLength / 2);

                while (!IsSqrt(n, root))
                {
                    root += n / root;
                    root /= 2;
                }

                return root;
            }

            throw new ArithmeticException("NaN");
        }

        /// <summary>
        /// Checks if a number is a possible square root
        /// </summary>
        /// <param name="number"></param>
        /// <param name="root"></param>
        /// <returns></returns>
        private static bool IsSqrt(BigInteger number, BigInteger root)
        {
            BigInteger lowerBound = root * root;
            BigInteger upperBound = (root + 1) * (root + 1);

            return (number >= lowerBound && number < upperBound);
        }
    }
}
