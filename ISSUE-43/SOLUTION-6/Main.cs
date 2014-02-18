/// <summary>
/// 
/// Olimex WPC # 43 - bank card validation
/// 
/// Using Mono version 2.10.8.1
/// 
/// </summary>
using System;
using System.Text;

namespace CardValidation
{

	/// <summary>
  	/// Checksum generation and verification class using the Luhn algorithm.
	/// For an explanation of the algorithm see: http://en.wikipedia.org/wiki/Luhn_algorithm
	/// The class provides two static methods: one to generate a checksum and one to validate the checksum   
  	/// </summary>
	class Luhn
	{
		/// <summary>
		/// A lookup table with the digits 0 through 9 doubled
		/// If the doubled value has more than 1 digit, then the individual digits are summed 
		/// </summary>
		private static readonly int[] lut = {0,2,4,6,8,1,3,5,7,9};

		/// <summary>
		/// Determine the Luhn checksum for a provided input
		/// </summary>
		/// <param name='input'>
		/// The input string to be checksummed.
		/// The provided input string has to be at least one character long or an exception is thrown.
		/// All characters must be digits in the range '0' to '9', i.e. have values between 48 and 57 (inclusive).
		/// </param>
		/// <returns>
		/// The calculated checksum.
		/// </returns>
		public static int Checksum(string input)
		{
			// Assume that strings shorter than 1 character are invalid
			if (input.Length < 1)
				throw new Exception("Input too short");
 
			int accumulator = 0;	// Collects sum of values for every digit 
			int char_value;			// A character in the input, cast to an integer

			// Iterate backwards over the string
			for (int index = input.Length - 1, cnt = 0; index >= 0; index--, cnt++) 
			{
				char_value = (int)input[index];
				// Verify that the provided character is a digit
				if ((char_value >= 48) && (char_value <= 57))
				{
					// For even positions, add the "doubled" value to the accumulator
					// Otherwise, just add the numerical value
					if (cnt % 2 == 0)
						accumulator += lut[char_value - 48];
					else
						accumulator += char_value - 48;
				}
				else
					throw new Exception("Invalid character in input");
			}

			// Return the calculated checksum
			return (accumulator * 9) % 10;
		}

		/// <summary>
		/// Determine the validity of a provided input.
		/// </summary>
		/// <param name='input'>
		/// A string of at least two characters long, with the last character assumed to be the checksum. 
		/// All characters, including the checksum must be digits in the range '0' to '9'
		/// That is, the must have values between 48 and 57 (inclusive). 
		/// </param>
		/// <returns>
		/// True if the checksum is valid, false otherwise.
		/// </returns>
		public static bool Validate (string input)
		{
			// Assume that strings shorter than 2 characters are invalid
			if (input.Length < 2)
				throw new Exception("Input too short");

			// Retrieve the checksum
			int provided_checksum;
			int check_char = (int)input[input.Length-1];

			if ((check_char >= 48) && (check_char <= 57)) 
				provided_checksum = (int)(check_char - 48);
			else
				throw new Exception("Invalid checksum character");

			int calculated_checksum = Checksum(input.Substring(0, input.Length - 1));

			if (calculated_checksum == provided_checksum)
				return true;
			else
				return false;
		}

	}

	/// <summary>
  	/// Checksum generation and verification class using the Luhn algorithm.
	/// A fast, compact version without verification of the provided input.
	/// </summary>
	class LuhnShort
	{
		private static readonly int[] lut = {0,2,4,6,8,1,3,5,7,9};

		public static int Checksum(string input)
		{ 
			int accumulator = 0;
			for (int index = input.Length - 1, cnt = 0; index >= 0; index--, cnt++) 
			{
				if (cnt % 2 == 0) 
					accumulator += lut[(int)input[index] - 48];
				else
					accumulator += (int)input[index] - 48;
			}
			return (accumulator * 9) % 10;
		}

		public static bool Validate(string input)
		{
			return (Checksum(input.Substring(0,input.Length-1)) == (int)input[input.Length-1] - 48) ? true : false;
		}

	}


	/// <summary>
  	/// Checksum generation and verification class using the Luhn algorithm.
	/// A slower version without lookup table.
	/// </summary>
	class LuhnLong
	{
		/// <summary>
		/// Calculate the checksum
		/// </summary>
		public static int Checksum(string input)
		{
			// Assume that strings shorter than 1 character are invalid
			if (input.Length < 1) {
				throw new Exception ("Input too short");
			}

			// Verify validity of provided input string
			foreach (char c in input) {
				if (!Char.IsNumber (c))
					throw new Exception ("Invalid character in input");
			}
 
			int accumulator = 0;	// Collects the sum of values 
			int cnt = 0;			// The odd/even counter

			// Iterate backwards over the string
			for (int index = input.Length - 1; index >= 0; index--) 
			{
				// The numerical value of the current digit
				int value = int.Parse(input[index].ToString());

				// For even positions, add the "doubled" value to the accumulator
				// Otherwise, just add the numerical value
				if (cnt % 2 == 0)
				{
					value *= 2;
					if (value >= 10)
					{
						string svalue = value.ToString();
						int mini_accu = 0;
						foreach (char c in svalue)
						{
							mini_accu += int.Parse(c.ToString());
						}
						accumulator += mini_accu;
					}
					else
						accumulator += value;
				}
				else
					accumulator += value;

				cnt++;
			}

			// Return the calculated checksum
			return (accumulator * 9) % 10;
		}


		/// <summary>
		/// Validates the checksum.
		/// </summary>
		public static bool Validate(string input)
		{
			if (input.Length < 2) {
				throw new Exception ("Input too short");
			}

			// Retrieve the checksum
			int provided_checksum = int.Parse(input[input.Length-1].ToString());
			// Calculate the checksum
			int calculated_checksum = Checksum(input.Substring(0, input.Length - 1));

			if (calculated_checksum == provided_checksum)
				return true;
			else
				return false;
		}
	}

	/// <summary>
  	/// Checksum generation and verification class using the Luhn algorithm.
	/// A variation removing non-numeric characters from the provided input.
  	/// </summary>
	class LuhnClean
	{
		/// <summary>
		/// Determine the Luhn checksum for a provided input
		/// </summary>
		/// <param name='input'>
		/// The input string to be checksummed.
		/// All non-number characters are removed.
		/// </param>
		/// <returns>
		/// The calculated checksum.
		/// </returns>
		public static int Checksum(string input)
		{
			StringBuilder cleaned = new StringBuilder();

			foreach (char c in input)
				if (Char.IsNumber(c)) cleaned.Append(c);

			return Luhn.Checksum(cleaned.ToString());
		}


		/// <summary>
		/// Determine the validity of a provided input.
		/// </summary>
		/// <param name='input'>
		/// A string of at least two characters long, with the last character assumed to be the checksum. 
		/// All non-number characters are removed.
		/// </param>
		/// <returns>
		/// True if the checksum is valid, false otherwise.
		/// </returns>
		public static bool Validate(string input)
		{
			StringBuilder cleaned = new StringBuilder();

			foreach (char c in input)
				if (Char.IsNumber(c)) cleaned.Append(c);

			return Luhn.Validate(cleaned.ToString());
		} 
	}

	class MainClass
	{
		private static string[] calc_tests = {
			"432156789012123",
			"94458023592485",
			"8194172489628",
			"103451208612",
			"20409850397",
			"7992739871"
		};

		private static string[] check_tests_valid = {
			"4321567890121231",
			"944580235924859",
			"81941724896284",
			"1034512086123",
			"204098503970",
			"79927398713"
		};

		private static string[] check_tests_clean = {
			"4321 5678 9012 1231",
			"9445 8023 5924 85 9",
			"8194.1724.8962.84",
			"1034-5120-8612-3",
			"AB-2040_9850_3970",
			"7992 7398 713"
		};

		private static string[] check_tests_invalid = {
			"4321567890121230",
			"944580235924851",
			"81941724896288",
			"1034512086129",
			"204098503979",
			"79927398712"
		};


		public static void Main (string[] args)
		{
			// Tests
			foreach (string test in calc_tests) 			
				Console.WriteLine ("Checksum for {0} is {1}", test, Luhn.Checksum (test));

			foreach (string test in check_tests_valid) 
				Console.WriteLine ("{0} is {1}", test, Luhn.Validate (test) ? "valid" : "invalid (ERROR!)");

			foreach (string test in check_tests_clean) 
				Console.WriteLine ("{0} is {1}", test, LuhnClean.Validate (test) ? "valid" : "invalid (ERROR!)");

			foreach (string test in check_tests_invalid) 
				Console.WriteLine ("{0} is {1}", test, Luhn.Validate (test) ? "valid (ERROR!)" : "invalid");

			foreach (string test in check_tests_valid) 
				Console.WriteLine ("{0} is {1}", test, LuhnShort.Validate (test) ? "valid" : "invalid (ERROR!)");

			foreach (string test in check_tests_valid) 
				Console.WriteLine ("{0} is {1}", test, LuhnLong.Validate (test) ? "valid" : "invalid (ERROR!)");

			foreach (string test in check_tests_invalid) 
				Console.WriteLine ("{0} is {1}", test, LuhnShort.Validate (test) ? "valid (ERROR!)" : "invalid");

			foreach (string test in check_tests_invalid) 
				Console.WriteLine ("{0} is {1}", test, LuhnLong.Validate (test) ? "valid (ERROR!)" : "invalid");

			// Speed comparison
			string input = "432156789012123";
			System.DateTime start;
			System.DateTime stop;
			System.TimeSpan delta;

			start = System.DateTime.Now;
			for (int loop = 1; loop <= 100000; loop++) {
				Luhn.Validate (input);
			}
			stop = System.DateTime.Now;
			delta = stop - start;
			Console.WriteLine ("Validate (normal): {0} ms", delta.TotalMilliseconds);

			start = System.DateTime.Now;
			for (int loop = 1; loop <= 100000; loop++) {
				LuhnShort.Validate (input);
			}
			stop = System.DateTime.Now;
			delta = stop - start;
			Console.WriteLine ("Validate (fast): {0} ms", delta.TotalMilliseconds);

			start = System.DateTime.Now;
			for (int loop = 1; loop <= 100000; loop++) {
				LuhnLong.Validate (input);
			}
			stop = System.DateTime.Now;
			delta = stop - start;
			Console.WriteLine ("Validate (slow): {0} ms", delta.TotalMilliseconds);

			Console.ReadLine ();
		}
	}
}
