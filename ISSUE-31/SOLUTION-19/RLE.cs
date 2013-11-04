using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;

namespace RLE
{
    static class Program
    {
        static void Main(string[] args)
        {
            var expanded = @"WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWBWWWWWWWWWWWWWW";
            var compressed = @"12W1B12W3B24W1B14W";

            var enumed = new string(expanded.RLEEncodeStream().RLEDecodeStream().ToArray());

            var decoded = RLEDecode(compressed);
            var encoded = RLEEncode(expanded);

            var worked = (expanded == decoded) && (compressed == encoded) && enumed == expanded;

            Console.Out.WriteLine(encoded);
        }

        static IEnumerable<char> RLEDecodeStream(this IEnumerable<char> source)
        {
            int length = 0;
            foreach (var c in source)
            {
                var cc = Char.GetUnicodeCategory(c);
                switch (cc)
                {
                    case UnicodeCategory.DecimalDigitNumber:
                        length = (10 * length) + (c - '0');
                        break;
                    default:
                        for (int i = 0; i < length; ++i)
                            yield return c;
                        length = 0;
                        break;
                }
            }
        }

        static IEnumerable<char> RLEEncodeStream(this IEnumerable<char> source)
        {
            int length = 0;
            char prev = '\0';
            foreach (var c in source)
            {
                if (c == prev)
                {
                    ++length;
                }
                else
                {
                    if (length > 0)
                    {
                        foreach (var x in length.ToString())
                            yield return x;
                        yield return prev;
                    }
                    prev = c;
                    length = 1;
                }
            }

            if (length > 0)
            {
                foreach (var x in length.ToString())
                    yield return x;
                yield return prev;
            }
        }

        private static string RLEDecode(string encoded)
        {
            var buffer = new StringBuilder();

            int length = 0;
            foreach (var c in encoded)
            {
                var cc = Char.GetUnicodeCategory(c);
                switch (cc)
                {
                    case UnicodeCategory.DecimalDigitNumber:
                        length = (10 * length) + (c - '0');
                        break;
                    default:
                        buffer.Append(c, length);
                        length = 0;
                        break;
                }
            }

            return buffer.ToString();
        }

        private static string RLEEncode(string decoded)
        {
            var buffer = new StringBuilder();

            int length = 0;
            char prev = '\0';
            foreach (var c in decoded)
            {
                if (c == prev)
                {
                    ++length;
                }
                else
                {
                    if (length > 0)
                        buffer.Append(length).Append(prev);
                    prev = c;
                    length = 1;
                }
            }

            if (length > 0)
            {
                buffer.Append(length).Append(prev);
            }

            return buffer.ToString();
        }
    }
}
