using System;
using System.Globalization;

namespace WPCWeek47
{
    class Program
    {

        static DateTime ParseDate(string date)
        {
            CultureInfo provider = CultureInfo.InvariantCulture;
            DateTime firstDate = DateTime.ParseExact(date, "d/MM/yyyy", provider);
            return firstDate;
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Date format: d/MM/yyyy");
            Console.WriteLine("Example: 2/05/2014");
            DateTime d1, d2;

            //Get the first date
            Console.Write("Please enter the first date: ");
            string firstD = Console.ReadLine();
            try
            {
                d1 = ParseDate(firstD);
            }
            catch (FormatException)
            {
                Console.WriteLine("Invalid format!");
                return;
            }
            
            //Get the second date
            Console.Write("Please enter the second date: ");
            string secondD = Console.ReadLine();
            try
            {
                d2 = ParseDate(secondD);
            }
            catch (FormatException)
            {
                Console.WriteLine("Invalid format!");
                return;
            }
            DateTime fromDate, toDate;

            //Find the smaller date
            if (d1 > d2)
            {
                fromDate = d2;
                toDate = d1;
            }
            else
            {
                fromDate = d1;
                toDate = d2;
            }

            int days, months, years;
            int[] daysInMonth = new int[12]{31, -1, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

            //Calculate days in month
            int increment = 0;
            if (fromDate.Day > toDate.Day)
            {
                increment = daysInMonth[fromDate.Month - 1];
            }

            if (increment == -1)
            {
                if (DateTime.IsLeapYear(fromDate.Year))
                {
                    increment = 29;
                }
                else
                {
                    increment = 28;
                }
            }

            //Calculate days
            if (increment != 0)
            {
                days = (toDate.Day + increment) - fromDate.Day; //Calculate the difference between the days
                increment = 1;
            }
            else
            {
                days = toDate.Day - fromDate.Day;
            }

            //Calculate months
            if (fromDate.Month + increment > toDate.Month)
            {
                months = (toDate.Month + 12) - (fromDate.Month + increment);
                increment = 1;
            }
            else
            {
                months = toDate.Month - (fromDate.Month + increment);
                increment = 0;
            }

            //Calculate years
            years = toDate.Year - (fromDate.Year + increment);

            Console.WriteLine("{0} year(s), {1} month(s), {2} day(s)", years, months, days);


        }
    }
}