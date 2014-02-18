using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WPC43_Bank_Card_Validation
{
    /// <summary>
    /// Checks the mod-10 value of the card number based on Luhn's algorithm.
    /// </summary>
    public static class Luhn
    {
        private static readonly int[] mod10DoubledValues = { 0, 2, 4, 6, 8, 1, 3, 5, 7, 9 };

        public static bool Modulus10Check(string cardNumber)
        {
            int sum = 0;

            // We don't double the rightmost digit.
            bool doubleIt = false;

            // Start with the rightmost digit and work through each going to the left.
            for (int i = cardNumber.Length - 1; i >= 0; i--)
            {
                int digit = (int)cardNumber[i] - (int)'0';
                if (doubleIt)
                {
                    sum += mod10DoubledValues[digit];
                }
                else
                {
                    sum += digit;
                }

                // Flip the flag.
                doubleIt = !doubleIt;
            }

            // Return true if the sum is exactly divisible by 10.
            return ((sum % 10) == 0);
        }
    }
}
