using System;
using System.IO;
using System.Text;

namespace Olimex_Programming_Challenge_21
{
    /// <summary>
    /// Problem:
    /// 
    /// Aoccdrnig to a rscheearch at Cmabrigde Uinervtisy, it deosn’t mttaer in waht oredr 
    /// the ltteers in a wrod are, the olny iprmoetnt tihng is taht the frist and lsat 
    /// ltteer be at the rghit pclae. The rset can be a toatl mses and you can sitll 
    /// raed it wouthit porbelm. Tihs is bcuseae the huamn mnid deos not raed ervey 
    /// lteter by istlef, but the wrod as a wlohe.
    ///
    /// You can see original text here: 
    /// http://www.mrc-cbu.cam.ac.uk/people/matt.davis/Cmabrigde/
    ///
    /// Write code which takes as input normal text and shuffles the letters inside the 
    /// words to make text like this one above.
    /// </summary>
    class Program
    {
        private const string InputFile = "AlicesAdventuresInWonderland.txt";
        private const string OutputFile = "output.txt";

        static void Main(string[] args)
        {
            // Get a random number generator for jumbling letters.
            Random rand = new Random();
            
            // Create an output file where the jumbled text will be written to.
            TextWriter output = CreateOutputFile();

            // Open up the input file and starts reading it, one character at a time.
            using (TextReader input = OpenInputFile())
            {
                // Read characters until there's no more to read (EOF).
                while (input.Peek() >= 0)
                {
                    // Check whether the character in the file is alpha or an apostrophe.
                    // Apostrophe's ensure words like "people's" are treated as one word.
                    char c = (char)input.Peek();
                    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '\'')
                    {
                        // Character is alpha or apostrophe.  Read the whole word to a string.
                        string word = ReadAlphaString(input);
                        if (word.Length > 3)
                        {
                            // Jumble the letters
                            string jumbled = JumbleWord(word, rand);
                            output.Write(jumbled);
                        }
                        else
                        {
                            // Word too short to jumble; just output it as is
                            output.Write(word);
                        }
                    }
                    else
                    {
                        // Character is not alpha so just read it and write it out 
                        // to the output file.
                        char cRead = (char)input.Read();
                        output.Write(cRead);
                    }
                }

                // All done so close the output file.
                output.Close();
            }
        }

        /// <summary>
        /// Jumbles a word using the supplied random number generator.
        /// </summary>
        /// <param name="word">The word to jumble</param>
        /// <param name="rand">The random number generator.  The caller provides
        /// this to avoid generating the same jumbled word whenever a repeated word
        /// is in the input text.</param>
        /// <returns>The jumbled word</returns>
        private static string JumbleWord(string word, Random rand)
        {
            char[] inputWord = word.ToCharArray();
            char[] jumbledWord = new char[inputWord.Length];

            // Copy the first and last characters in the word to the jumbled word array.
            jumbledWord[0] = inputWord[0];
            int lastIndex = inputWord.Length - 1;
            jumbledWord[lastIndex] = inputWord[lastIndex];

            // Go through each character in the input word, starting at the
            // second character and finishing at the last but one.
            for (int index = 1; index < lastIndex; index++)
            {
                // If this isn't the last character to be slotted into the jumbled
                // word, get a random number between 1 and the length of the input
                // word less 1.  This will give us the position of the character
                // in the jumbled word.
                if (index != lastIndex - 1)
                {
                    // Find a suitable slot for the character in the output
                    // jumbled word.
                    int slot;
                    while (true)
                    {
                        // If the position of the letter in the jumbled word is 
                        // the same as in the input word, discard this one and 
                        // get another random number.
                        while ((slot = rand.Next(1, lastIndex)) == index) { }

                        // If the slot in the jumbled word hasn't been filled
                        // yet, drop the character into it.  Otherwise, get
                        // another random slot until we find an empty slot.
                        if (jumbledWord[slot] == '\0')
                        {
                            jumbledWord[slot] = inputWord[index];
                            break;
                        }
                    }
                }
                else
                {
                    // For the last character to be slotted into the jumbled word,
                    // it can only go into one position so handle separately.
                    // This avoids a lot of looping if we handled this case in the 
                    // if block.
                    for (int jIndex = 1; jIndex < lastIndex; jIndex++)
                    {
                        if (jumbledWord[jIndex] == '\0')
                        {
                            jumbledWord[jIndex] = inputWord[index];
                            break;
                        }
                    }
                }
            }

            // All done with this word, so give it back to the caller.
            return new string(jumbledWord);
        }

        /// <summary>
        /// Read a word from the input file.  Apostrophes are considered to be part
        /// of a word.
        /// </summary>
        /// <param name="input">The input file.</param>
        /// <returns>The word.</returns>
        private static string ReadAlphaString(TextReader input)
        {
            StringBuilder sb = new StringBuilder(16);
            while (input.Peek() >= 0)
            {
                char peek = (char)input.Peek();
                if ((peek >= 'A' && peek <= 'Z') || (peek >= 'a' && peek <= 'z') || peek == '\'')
                {
                    sb.Append((char)input.Read());
                }
                else
                {
                    break;
                }
            }
            return sb.ToString();
        }

        /// <summary>
        /// Open the input text file.
        /// </summary>
        /// <returns>The input text stream.</returns>
        private static TextReader OpenInputFile()
        {
            string filepath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, InputFile);
            StreamReader input = new StreamReader(filepath);
            return input as TextReader;
        }

        /// <summary>
        /// Create an output text file.
        /// </summary>
        /// <returns>The text stream that characters can be written to.</returns>
        private static TextWriter CreateOutputFile()
        {
            string filepath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, OutputFile);
            StreamWriter output = new StreamWriter(filepath, false);
            return output as TextWriter;
        }
    }
}
