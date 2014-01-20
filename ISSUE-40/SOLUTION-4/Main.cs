#define TEST

/*
 *  Olimex WPC # 40
 *  Split a positive integer in multiplications by 3 and truncated divisions by 2
 * 
 */

using System;
using System.Text;

namespace splitter
{
	class MainClass
	{
#if TEST
		private static int tests = 0;
		private static int ok = 0;
		private static int nok = 0;
#endif
		private static void split (int n)
		{
			int value = 1;
			int multiplications = 0;
			int divisions = 0;

			// As long as our calculated value does not
			// match the input value
			while (value != n) {
				// First of all, multiply it by 3
				value *= 3;
				multiplications++;
				// Stop if this multiplication yields the expected result
				if (value == n) break;
				else
				{
					int newvalue = value;
					divisions = 0;
					// Otherwise, repeatedly divide by 2
					// until the expected result is found or our
					// temporary result gets too small
					while (newvalue > n)
					{
						newvalue = newvalue / 2;
						divisions++;			
						if (newvalue == n) 
						{ 
							value = newvalue;
							break;
						}
					}
				}
			}

			// Build string representation of result
			StringBuilder line = new StringBuilder("1");
			for (int muls = 1; muls <= multiplications; muls++)
				line.Append("*3");
			for (int divs = 1; divs <= divisions; divs++)
				line.Append("/2");

#if TEST
			// Verify
			int verification = 1;
			for (int muls = 1; muls <= multiplications; muls++)
				verification *= 3;
			for (int divs = 1; divs <= divisions; divs++)
				verification /= 2;

			if (verification == n)
			{
				ok++;
				Console.WriteLine("OK! {0} = {1} = {2}", n, line, verification);
			}
			else
			{
				nok++;
				Console.WriteLine("ERROR! {0} != {1} != {2}", n , line, verification);
			}
#else
			// Print result
			Console.WriteLine("{0} = {1}", n, line);
#endif
		}

		public static void Main (string[] args)
		{
#if TEST
			for (int n = 1; n < 100; n++)
			{
				tests++;
				split(n);
			}
			Console.WriteLine("{0} tests, {1} OK, {2} errors", tests, ok, nok);
#else
			int parsed = 0;
			do
			{
				Console.Write("Enter a number (0 to exit): ");
				string input = Console.ReadLine();
				if (int.TryParse(input, out parsed))
				{
					if (parsed != 0) 
						split(parsed);
				}
				else
					Console.WriteLine("Not a number");
			} while (parsed != 0);
#endif
		}
	}
}
