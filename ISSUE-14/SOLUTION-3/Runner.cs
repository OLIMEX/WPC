using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Diagnostics;
using System.Numerics;

namespace Olimex_Programming_Challenge_14
{
    [TestClass]
    public class Runner
    {
        [TestMethod]
        public void CalculateWithBigInteger()
        {
            // How many decimal places do we want to calculate pi to?
            // The higher the number, the longer it will take.  This is an exponential increase!
            // 11 took me over 2 hours on an i5 PC.
            const int requiredDecimalPlaces = 9;

            // The result after each iteration is checked against the result from the previous one.
            // If the difference between them is <= this tolerance, it will be deemed to be an
            // acceptable result.
            const int tolerance = 2;

            // Once we get the result, this will tell us how many iterations we had to go through
            // to get the result.
            BigInteger iterations = 0;

            // Calculate pi.  We'll also measure how long this took us.
            Stopwatch timer = Stopwatch.StartNew();
            string result = Pi.CalculateWithBigInt(requiredDecimalPlaces, tolerance, out iterations);
            timer.Stop();

            // Output the result.
            Debug.Print("After {0} iterations which took {1}ms, pi = {2}", 
                iterations, 
                timer.ElapsedMilliseconds, 
                result);
        }
    }
}
