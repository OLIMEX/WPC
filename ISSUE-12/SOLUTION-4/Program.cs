using System;
using System.Text;
using System.IO;
using System.Text.RegularExpressions;

namespace AppRunner
{
    class Program
    {
        // The text to be searched for instances of the input word or its close matches is held in
        // this file.
        private const string filename = "AlicesAdventuresInWonderland.txt";

        static void Main(string[] args)
        {
            // Allow the user to search for different input words without having to restart the
            // console application.
            while (true)
            {
                // Get the input string from the user.
                Console.Write("Enter a word to search for : ");
                string searchWord = Console.ReadLine();
                if (searchWord.Length == 0) break;

                // Read the Alice in Wonderland text from a local file.  We could have read this text
                // from the web by using the WebClient object but it's static text so I've chosen
                // to download it into a local file and read that instead.
                string fullPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, filename);
                string passageText = File.ReadAllText(fullPath);

                // Search the text using a regular expression, ignoring letter case.
                string regex = BuildRegularExpression(searchWord);
                MatchCollection matches =
                    Regex.Matches(passageText, regex, RegexOptions.IgnoreCase);


                // List each match along with the snippet of text that contains the match.
                Console.WriteLine("-------------------------------------------------------");
                foreach (Match match in matches)
                {
                    Console.WriteLine(string.Format("{0}  : {1}",
                        match.Value.PadRight(searchWord.Length + 2),
                        GetSnippet(passageText, match.Index, searchWord.Length)));
                }

                // Report how many matches we found.
                Console.WriteLine("Found {0} matche(s)", matches.Count);

                Console.WriteLine("-------------------------------------------------------");
            }
        }

        /// <summary>
        /// Retrieve the snippet of text from the input passage of text.
        /// </summary>
        /// <param name="passage">The text being searched for the input word and its valid combinations.
        /// </param>
        /// <param name="index">The index into the passage of text where the match was found.</param>
        /// <param name="inputLength">The length of the input word being searched for.</param>
        /// <returns>The text surrounding the input word or close match to it.</returns>
        private static string GetSnippet(string passage, int index, int inputLength)
        {
            int pre = index - 15;
            if (pre < 0) pre = 0;
            int post = index + inputLength + 15;
            if (post > passage.Length) post = passage.Length;
            string snippet = string.Format("...{0}...", passage.Substring(pre, post - pre));

            // Replace cr and lf characters with a space to keep the snippet of text on one line.
            snippet = snippet.Replace('\n', ' ');
            snippet = snippet.Replace('\r', ' ');

            return snippet;
        }

        /// <summary>
        /// Builds a regular expression that we can use against the input text to find matches or close matches.
        /// </summary>
        /// <param name="inputWord">The word to be searched for in the passage of text.</param>
        /// <returns></returns>
        /// <example>
        /// If the input word is "the" (without the double quotes), the regular expression returned will be:
        /// 
        ///     \bthe\b|\b\whe\b|\bt\we\b|\bth\w\b|\wthe\b|\bthe\w\b
        /// 
        /// </example>
        static string BuildRegularExpression(string inputWord)
        {
            StringBuilder expression = new StringBuilder(64);

            // Start with exact match to input word.
            expression.Append(string.Format("\\b{0}\\b", inputWord));

            // Add on cases where one character in the input word could be any character.
            // We don't need to do this for single lettered words, e.g. a and I
            if (inputWord.Length > 1)
            {
                for (int i = 0; i < inputWord.Length; i++)
                {
                    if (i == 0)
                    {
                        // First character in the input word could be any character.
                        // e.g. \b\whe\b
                        expression.Append(string.Format("|\\b\\w{0}\\b", inputWord.Substring(1)));
                    }
                    else if (i != inputWord.Length - 1)
                    {
                        // Not the first or last character in the input word.
                        // e.g. \bt\we\b
                        expression.Append(string.Format("|\\b{0}\\w{1}\\b", inputWord.Substring(0, i), inputWord.Substring(i + 1)));
                    }
                    else
                    {
                        // Last character in the input word could be any character.
                        // e.g. \bth\w\b
                        expression.Append(string.Format("|\\b{0}\\w\\b", inputWord.Substring(0, inputWord.Length - 1)));
                    }
                }
            }

            // Input word prefixed by any alphabetical character.
            expression.Append(string.Format("|\\b\\w{0}\\b", inputWord));

            // Input word suffixed by any alphabetical character.
            expression.Append(string.Format("|\\b{0}\\w\\b", inputWord));

            return expression.ToString();
        }
    }
}
