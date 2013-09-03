using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace WPC22_Plagiarism_Detector
{
    /// <summary>
    /// Make code which compare two texts and output the % of similarities between the two texts 
    /// i.e. if they have same words even if the words are in different order.
    /// </summary>
    /// <author>Nigel Mollett</author>
    /// <date>30/08/2013</date>
    class Program
    {
        // These are the two files we'll check for level of plagiarism.
        const string Filename1 = "PlagiarismText.txt";
        const string Filename2 = "AlicesAdventuresInWonderland.txt";

        static void Main(string[] args)
        {
            // Access the files for reading.
            TextReader reader1 = OpenInputFile(Filename1);
            TextReader reader2 = OpenInputFile(Filename2);

            // We'll parse the words in each file and put unique words into 2 lists.
            List<string> list1 = ParseWords(reader1);
            List<string> list2 = ParseWords(reader2);

            // Show how many unique words are in the input files.
            Console.WriteLine("File 1 {0} contains {1} unique words.", Filename1, list1.Count);
            Console.WriteLine("File 2 {0} contains {1} unique words.", Filename2, list2.Count);

            double matchedWords = 0;
            double plagiarism1 = 0;
            double plagiarism2 = 0;

            // For speed, we'll find out how many words in the smaller list are in the larger one.
            List<string> largerList = (list1.Count >= list2.Count) ? list1 : list2;
            List<string> smallerList = (list1.Count < list2.Count) ? list1 : list2;
            foreach (string word in smallerList)
            {
                if (largerList.Contains(word)) matchedWords++;
            }
            Console.WriteLine();
            Console.WriteLine("Number of unique words appearing in both files : {0}", matchedWords);
            Console.WriteLine();

            // Calculate the amount of plagiarism in each of the files.
            plagiarism1 = matchedWords / list1.Count;
            plagiarism2 = matchedWords / list2.Count;

            Console.WriteLine("Plagiarism level 1 (words in file1 found in file2) : {0}", plagiarism1.ToString("P2"));
            Console.WriteLine("Plagiarism level 2 (words in file2 found in file1) : {0}", plagiarism2.ToString("P2"));
            Console.WriteLine();

            Console.WriteLine("Press a key to quit...");
            Console.Read();
        }

        /// <summary>
        /// Read the words from the text reader (file) and compile a list of unique words in the file.
        /// </summary>
        /// <param name="reader">The input text file to parse</param>
        /// <returns>The list of unique words in the input text file</returns>
        private static List<string> ParseWords(TextReader reader)
        {
            List<string> uniqueWords = new List<string>();

            while (reader.Peek() >= 0)
            {
                char c = (char)reader.Peek();
                if (char.IsLetter(c))
                {
                    // It's the start of a word so read it and add it to the list if
                    // it doesn't already exist in there.
                    string word = ReadAlphaString(reader);

                    if (!uniqueWords.Contains(word))
                    {
                        uniqueWords.Add(word);
                    }
                }
                else
                {
                    // Just read the non-letter character and ignore it.
                    reader.Read();
                }
            }
            return uniqueWords;
        }

        /// <summary>
        /// Read a word from the input file.
        /// </summary>
        /// <param name="input">The input file.</param>
        /// <returns>The word.</returns>
        private static string ReadAlphaString(TextReader input)
        {
            StringBuilder sb = new StringBuilder(16);
            while (input.Peek() >= 0)
            {
                char peek = (char)input.Peek();
                if (char.IsLetter(peek))
                {
                    sb.Append((char)input.Read());
                }
                else
                {
                    break;
                }
            }
            return sb.ToString().ToLower();
        }

        /// <summary>
        /// Open the input text file.
        /// </summary>
        /// <returns>The input text stream.</returns>
        private static TextReader OpenInputFile(string filename)
        {
            string filepath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, filename);
            StreamReader input = new StreamReader(filepath);
            return input as TextReader;
        }
    }
}
