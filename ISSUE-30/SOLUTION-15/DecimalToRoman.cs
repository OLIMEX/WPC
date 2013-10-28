/*
 * Weekend Programming Challenge – Week #30 Roman numbers
 * 
 * Author: loloto
 * 
 * Converting decimal numbers [1; 4000] to Roman numbers
 * (more than 4k have different graphical notations, it's not to implement algoritmically though)
 * 
 * */

using System;

namespace DecimalToRomanWPC30
{
    class DecimalToRoman
    {
        static void Main(string[] args)
        {
            int decNum;

            do
            {
                Console.WriteLine("Enter decimal number in the range [1; 4000]: ");
                int.TryParse(Console.ReadLine(), out decNum);
            } while (decNum < 1 || decNum > 4000);

            String romanNumber = GetRomanNumber(decNum);

            Console.WriteLine("Roman number: {0}", romanNumber);
        }

        static string GetRomanNumber(int decimalNumber)
        {
            if (decimalNumber < 1 || decimalNumber > 4000)
            {
                throw new ArgumentOutOfRangeException("decimalNumber", "Specified deciaml number is out of the range [1, 4000]!");
            }

            string romanNumber = String.Empty;

            for (int i = 0; i < DecimalArr.Length; i++)
            {
                if (decimalNumber == 0)
                {
                    break;
                }

                while (decimalNumber >= DecimalArr[i])
                {
                    decimalNumber -= DecimalArr[i];
                    romanNumber += RomanArr[i];
                }
            }

            return romanNumber;
        }

        static readonly int[] DecimalArr = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
        static readonly string[] RomanArr = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };
    }
}
