using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;

namespace median
{
	/// <summary>
	/// Read the data file and store the data of the first channel
	/// in a List for further processing
	/// </summary>
	public class DataClass
	{
		public static List<ushort> OriginalValues {get; private set; }
		public static List<ushort> FilteredValues {get; private set; }
		
		static DataClass()
		{
			OriginalValues = new List<ushort>();
			FilteredValues = new List<ushort>();
			Read();
		}
	
		/// <summary>
		/// Take the (first) four hexadecimal characters from the
		/// buffer and convert them to an unsigned short		
		/// </summary>
		private static void ParseData(char[] buf)
		{
			string hex = new string(buf, 0, 4);
			ushort value = ushort.Parse(hex, NumberStyles.HexNumber);
			if (value <= 1023)
				OriginalValues.Add(value);
			else
				OriginalValues.Add(1023);
		}
		
		/// <summary>
		/// Read the data file, skipping over data we're not interested in
		/// but parsing and storing the contents of the first data channel
		/// </summary>
		public static void Read()
		{
			OriginalValues.Clear();
			
			using (StreamReader r = new StreamReader("ECGSAMPLE.txt"))
			{
				int bytesRead = 0;
				char[] buffer = new char[24];
				
				while (!r.EndOfStream)
				{
					bytesRead = r.ReadBlock(buffer, 0, 8);
					if (bytesRead != 8) 
						break;
					
					bytesRead = r.ReadBlock(buffer, 0, 24);
					if (bytesRead != 24) 
						break;
					else
						ParseData(buffer);
					
					bytesRead = r.ReadBlock(buffer, 0, 2);
					if (bytesRead != 2) 
						break;
				}
			}			
			
			return;
		}
		
		public static void Filter(int windowSize)
		{			
			List<ushort> window;			
			int halfWindow = windowSize / 2;
			int lowerBorder = windowSize;
			int upperBorder = OriginalValues.Count - windowSize;
			int position = 0;
		
			FilteredValues.Clear();			
			for (int x = 0 ; x < OriginalValues.Count; x++)
			{
				if (x < lowerBorder)
					position = halfWindow;
				else if(x > upperBorder)
					position = upperBorder - halfWindow;
				else
					position = x - halfWindow;						
				
				window = OriginalValues.GetRange(position, windowSize);				
				window.Sort();				
				FilteredValues.Add(window[halfWindow]);
			}
					
		}
	}
}
