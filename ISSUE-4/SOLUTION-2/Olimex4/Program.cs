using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace Olimex4
{
	class Program
	{
		static void Main ( string[] args )
		{
			var text = File.ReadAllText( "Alice.txt" );
			var words = text.Split( GetDelimiters(), StringSplitOptions.RemoveEmptyEntries );

			int countMax = 0;
			string wordMax = string.Empty;
			foreach ( var word in words )
			{
				var count = CountIfHPM( word );
				if ( count > countMax )
				{
					countMax = count;
					wordMax = word;
				}
			}

			Console.WriteLine( "Longest isogram word is '{0}'", wordMax );
		}

		static char[] GetDelimiters ()
		{
			var delims = new List<char>();
			for ( int i = 1; i < 128; i++ )
			{
				if ( !char.IsLetter( (char)i ) )
				{
					delims.Add( (char)i );
				}
			}
			return delims.ToArray();
		}

		static int CountIfHPM( string word )
		{
			var hash = new HashSet<char>();
			foreach ( var ch in word )
			{
				if ( !hash.Add( ch ) )
					return 0;
			}
			return hash.Count;
		}
	}
}
