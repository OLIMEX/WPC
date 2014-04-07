using System;

namespace WPC49_EasterDateCalculator
{
    public static class Calculate
    {
        /// <summary>
        /// Create a string containing the year and Easter Sunday dates for the 
        /// Western Church and Orthodox Eastern Church for a number of years.
        /// </summary>
        /// <param name="year">The year to start from.</param>
        /// <param name="numberOfYears">The number of Easter Sunday dates to calculate.
        /// </param>
        /// <returns></returns>
        public static string EasterDates(int year, int numberOfYears)
        {
            string text = "Year   Western Church   Eastern Church" + Environment.NewLine;
            text += "----   --------------   --------------" + Environment.NewLine;

            for (int i = 0; i < numberOfYears; i++)
            {
                text += year.ToString().PadRight(7);
                text += CalculateWesternChurchEasterSunday(year).PadRight(17);
                text += CalculateEasternChurchEasterSunday(year);
                text += Environment.NewLine;
                year++;
            }
            return text;
        }

        /// <summary>
        /// Variation of Gauss' algorithm to calculate the Eastern Orthodox church date
        /// for Easter Sunday.
        /// </summary>
        /// <param name="year"></param>
        /// <returns></returns>
        private static string CalculateEasternChurchEasterSunday(int year)
        {
            int a = year % 4;
            int b = year % 7;
            int c = year % 19;
            int d = (19 * c + 15) % 30;
            int e = (2 * a + 4 * b - d + 34) % 7;
            int month = (int)Math.Floor((double)((d + e + 114) / 31));
            int day = ((d + e + 114) % 31) + 1;

            DateTime date = new DateTime(year, month, day).AddDays(13);
            return string.Format("{0:d MMMM}", date); ;
        }

        /// <summary>
        /// Buthcher's algorithm to calculate the Western church date for Easter Sunday.
        /// </summary>
        /// <param name="year"></param>
        /// <returns></returns>
        private static string CalculateWesternChurchEasterSunday(int year)
        {
            int a = year % 19;
            int b = year / 100;
            int c = year % 100;
            int d = b / 4;
            int e = b % 4;
            int f = (b + 8) / 25;
            int g = (b - f + 1) / 3;
            int h = (19 * a + b - d - g + 15) % 30;
            int i = c / 4;
            int k = c % 4;
            int l = (32 + 2*e + 2*i - h - k) % 7;
            int m = (a + 11*h + 22*l) / 451;
            int p = (h + l - 7*m + 114) % 31;
            int month = (h + l - 7 * m + 114) / 31;

            DateTime date = new DateTime(year, month, p+1);
            return string.Format("{0:d MMMM}", date); ;
        }
    }
}
