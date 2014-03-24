using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace DateDiff
{
	public partial class MainForm : Form
	{
		public MainForm()
		{
			InitializeComponent();
			UpdateDisplay();
		}
		
		private void UpdateDisplay ()
		{
			DateTime first = dateTimePicker1.Value.Date;
			DateTime second = dateTimePicker2.Value.Date;

			// Insure that the second date is after the first one
			int daydiff = (second - first).Days;
			// Swap if needed
			if (daydiff < 0) {
				DateTime temp = first;
				first = second;
				second = temp;
			}

#if DEBUG
			DateTime verifyEnd = second;
#endif

			// Calculate the difference in years and remove it
			// Since the second date is always bigger than the first one,
			// This difference is always >= 0
			int years = second.Year - first.Year;
			second.AddYears (-years);

			// The years of both dates are now equal
			// Next, calculate the difference in months and remove it
			int months = second.Month - first.Month;
			second.AddMonths (-months);

			// If the second month is smaller than the first month
			// then decrease the difference in years and add twelve months
			// Since the second date is always bigger than the first one,
			// the second month can only be smaller if the difference in years is > 0
			// This means that the number of years will remain positive, even after
			// subtracting one.
			if (months < 0) {
				years--;
				months += 12;
			}

			// Both dates now have the same year and date
			// Next, calculate the difference in days
			int days = second.Day - first.Day;

			// If the second day is smaller that the first one, then
			// decrease the difference in months (and if needed in years)
			if (days < 0) {
				months--;
				if (months < 0) {
					years--;
					months += 12;
				}
				days = (second - second.AddMonths(-1)).Days + days;
			}				

#if DEBUG
			DateTime verifyStart = new DateTime(first.Ticks);
			verifyStart.AddYears(years);
			verifyStart.AddMonths(months);
			verifyStart.AddDays(days);
			System.Diagnostics.Debug.Assert (verifyStart.CompareTo (verifyEnd) == 0);
#endif	 
			// Display the results
			if (daydiff == 0)
				resultLabel.Text = "Both days are equal";
			else 
			{
				resultLabel.Text = String.Format ("Second date is{0}{1}{2} {3} the first one",
				                                 (years != 0) ? String.Format (" {0} year{1}", years, (years == 1) ? "" : "s") : "",
				                                 (months != 0) ? String.Format (" {0} month{1}", months, (months == 1) ? "" : "s") : "",
				                                 (days != 0) ? String.Format (" {0} day{1}", days, (days == 1) ? "" : "s") : "",
				                                 (daydiff > 0) ? "after" : "before");
			}

		}
	}
}
