using System;
using System.Collections.Generic;
using System.Globalization;

namespace WPC58_SecondsSinceGregorianStart
{
    class Program
    {
        private static string format = "dd/MM/yyyy HH:mm:ss";
        private static CultureInfo uk = new CultureInfo("en-GB");
        private const string lineBreak = "-----------------------------------------------------------------";

        // The Gregorian calendar was first introduced on 15th October 1582.
        private static DateTime gregorianStart = new DateTime(1582, 10, 15, new GregorianCalendar());

        static void Main(string[] args)
        {
            // Show the number of seconds for some test dates using two approaches to 
            // calculate the seconds; one using the in-built .Net functions and the other
            // using our code.  Both results should be the same.
            DisplayResultsOfTestDates();

            // Allow the user to try out their own dates.
            // Loop until the user enters q to quit.
            while (true)
            {
                Console.WriteLine("Enter q to quit");
                Console.Write("Enter date and time in dd/mm/yyyy hh:mm:ss format : ");

                string inputDate = Console.ReadLine();
                if (inputDate.ToLower() == "q") break;

                // Parse the input date into a Gregorian calendar date.
                DateTime testDate = DateTime.ParseExact(inputDate, format, uk);

                // Calculate the result using the internal .Net functions and our code.
                double netWay = SecondsTheDotNetWay(testDate);
                double ourWay = SecondsOurWay(testDate);
                double difference = netWay - ourWay;        // this should always be 0 if we got it right.

                Console.WriteLine(
                    "{0}   Seconds [.Net] {1,11:0}   [Our] {2,11:0}   [Diff] {3}",
                    testDate,
                    netWay,
                    ourWay,
                    difference);

                Console.WriteLine(lineBreak);
            }
        }

        /// <summary>
        /// Run some test dates and calculate the seconds from the Gregorian start date.
        /// We calculate the seconds using both the .Net and our code approaches to check
        /// that our code is correct.
        /// </summary>
        private static void DisplayResultsOfTestDates()
        {
            // Run some test dates through.
            foreach (DateTime testDate in GetTestDates())
            {
                double netWay = SecondsTheDotNetWay(testDate);
                double ourWay = SecondsOurWay(testDate);
                double difference = netWay - ourWay;
                Console.WriteLine(
                    "{0}   Seconds [.Net] {1,11:0}   [Our] {2,11:0}   [Diff] {3}",
                    testDate,
                    netWay,
                    ourWay,
                    difference);
            }

            Console.WriteLine(lineBreak);
        }

        /// <summary>
        /// Calculate the number of seconds from the Gregorian start date to the input
        /// date using the standard functions built into .NET.
        /// </summary>
        /// <param name="inputDate">
        /// The end date and time of the period to calculate.
        /// </param>
        /// <returns>
        /// The number of seconds between the Gregorian start date and the input date and time.
        /// </returns>
        private static double SecondsTheDotNetWay(DateTime inputDate)
        {
            return (inputDate - gregorianStart).TotalSeconds;
        }

        /// <summary>
        /// Calculate the number of seconds from the Gregorian start date to the input
        /// date using our long-winded code.  I'm sure this could be simplified a lot!
        /// </summary>
        private static double SecondsOurWay(DateTime inputDate)
        {
            double seconds = 0;
            DateTime from = gregorianStart;

            if (from.Year == inputDate.Year)
            {
                // Period is in the same year
                if (from.Month == inputDate.Month)
                {
                    // Period is in the same month and year
                    if (from.Day == inputDate.Day)
                    {
                        // Period is on the same day
                        // Only need to look at the time.
                        seconds += (inputDate - from).TotalSeconds;
                    }
                    else
                    {
                        // Period is in the same month and year but not the same day
                        // And add the seconds for the intervening days
                        seconds += (inputDate.Day - from.Day) * 24 * 60 * 60;

                        // Add the seconds for the time on the input date.
                        seconds += inputDate.Hour * 60 * 60;
                        seconds += inputDate.Minute * 60;
                        seconds += inputDate.Second;
                    }
                }
                else
                {
                    // Period is in the same year but not the same month.
                    // Start with the seconds for the days in the Gregorian start month.
                    seconds += (DaysInMonth(from.Month) - from.Day + 1) * 24 * 60 * 60;

                    // Add the days in the intervening months
                    for (int i = from.Month + 1; i < inputDate.Month; i++)
                    {
                        seconds += DaysInMonth(i) * 24 * 60 * 60;
                    }

                    // Now add the days in the input date month, excluding the
                    // end date.
                    seconds += (inputDate.Day - 1) * 24 * 60 * 60;
                    
                    // Finally add the seconds for the time on the input date.
                    seconds += inputDate.Hour * 60 * 60;
                    seconds += inputDate.Minute * 60;
                    seconds += inputDate.Second;
                }
            }
            else
            {
                // Period is in a different year to the Gregorian start date.
                // Start with the seconds for the days in the Gregorian start month.
                seconds += (DaysInMonth(from.Month) - from.Day + 1) * 24 * 60 * 60;

                // Add the days in the whole months from the start date in the start year.
                for (int i = from.Month + 1; i <= 12; i++)
                {
                    seconds += DaysInMonth(i) * 24 * 60 * 60;
                }

                // Add the days in the whole years in the period.
                for (int year = from.Year + 1; year < inputDate.Year; year++)
                {
                    seconds += 365 * 24 * 60 * 60;

                    // If the year is a leap year, account for 29th Feb.
                    if (IsLeapYear(year))
                    {
                        seconds += 24 * 60 * 60;
                    }
                }

                // Now add the days in the whole months in the input date's year.
                for (int month = 1; month < inputDate.Month; month++)
                {
                    seconds += DaysInMonth(month) * 24 * 60 * 60;
                }

                // If the input date is in March - December, check whether we need
                // to account for 29th Feb if this is a leap year.
                if (inputDate.Month > 2)
                {
                    if (IsLeapYear(inputDate.Year))
                    {
                        seconds += 24 * 60 * 60;
                    }
                }
                
                // Now add the days in the input date month, excluding the
                // end date.
                seconds += (inputDate.Day - 1) * 24 * 60 * 60;

                // Finally add the seconds for the time on the input date.
                seconds += inputDate.Hour * 60 * 60;
                seconds += inputDate.Minute * 60;
                seconds += inputDate.Second;
           }

           return seconds;
        }

        /// <summary>
        /// Gets the number of days in a month, ignoring leap years.
        /// </summary>
        /// <param name="month">Month number, 1-12</param>
        /// <returns>The number of days in the month</returns>
        private static int DaysInMonth(int month)
        {
            int[] daysInMonth = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
            if (month < 1 || month > 12) throw new ArgumentException("Invalid month");
            return daysInMonth[month - 1];
        }

        /// <summary>
        /// Checks whether the supplied year is a leap year.
        /// </summary>
        /// <param name="year">The year of interest</param>
        /// <returns>true if the year is a leap year</returns>
        private static bool IsLeapYear(int year)
        {
            return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
        }

        /// <summary>
        /// Gets a list of test dates to check our algorithms against.
        /// </summary>
        /// <returns>The list of test dates.</returns>
        private static List<DateTime> GetTestDates()
        {
            List<DateTime> testDates = new List<DateTime>();
            testDates.Add(DateTime.ParseExact("15/10/1582 00:00:00", format, uk));
            testDates.Add(DateTime.ParseExact("15/10/1582 00:00:10", format, uk));
            testDates.Add(DateTime.ParseExact("15/10/1582 01:02:03", format, uk));
            testDates.Add(DateTime.ParseExact("16/10/1582 01:02:03", format, uk));
            testDates.Add(DateTime.ParseExact("15/10/1583 01:02:03", format, uk));
            testDates.Add(DateTime.ParseExact("29/02/1600 12:34:56", format, uk));
            testDates.Add(DateTime.ParseExact("28/02/1900 12:34:56", format, uk));
            testDates.Add(DateTime.ParseExact("01/03/1900 12:34:56", format, uk));
            testDates.Add(DateTime.ParseExact("28/02/2000 12:34:56", format, uk));
            testDates.Add(DateTime.ParseExact("29/02/2000 12:34:56", format, uk));
            testDates.Add(DateTime.ParseExact("01/03/2000 12:34:56", format, uk));
            testDates.Add(DateTime.ParseExact("29/02/2000 12:34:56", format, uk));
            testDates.Add(DateTime.ParseExact("29/02/2400 12:34:56", format, uk));
            
            return testDates;
        }
    }
}
