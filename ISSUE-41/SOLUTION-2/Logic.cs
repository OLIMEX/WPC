using System;
using System.IO;

namespace WPC41_Speed_Typing_Test
{
    public class Logic
    {
        /// <summary>
        /// The name of the file containing the passage of text.
        /// </summary>
        private const string textFile = "AlicesAdventuresInWonderland.txt";

        /// <summary>
        /// Reads a passage of text from a text file.  This is the large piece of text 
        /// that we want to measure how long it takes to type.
        /// </summary>
        /// <returns></returns>
        public string LoadText()
        {
            // Get the path to the text file.
            string path = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, textFile);
            StreamReader sr = new StreamReader(path);
            string textPassage = sr.ReadToEnd();
            return textPassage;
        }

        /// <summary>
        /// Extract a suitable excerpt of text from the passage to be used to test 
        /// the user's typing speed.
        /// </summary>
        /// <param name="numberOfWords">The number of words required in the excerpt</param>
        /// <param name="textPassage">The passage of text to take the excerpt from</param>
        /// <returns>The excerpt of text</returns>
        public string GetTestText(decimal numberOfWords, string textPassage)
        {
            bool restart = true;
            int wordCount = 0;
            int startPosn = 0;
            int posn = 0;

            while (restart)
            {
                restart = false;
                wordCount = 0;

                // Get a random number from 0 to the length of the textPassage to identify
                // a character in the text passage to start from.
                Random rand = new Random();
                posn = rand.Next(textPassage.Length - 1);

                // Starting at this character position work skip characters until we get to
                // the first space.
                while (textPassage[posn] != ' ' && textPassage[posn] != '\n') posn++;

                // Skip further whitespace to get to the beginning of the next word.
                while (textPassage[posn] < 'A') posn++;

                // Now start reading the required number of words into a string.
                startPosn = posn;

                while (wordCount < numberOfWords)
                {
                    while (textPassage[posn] != ' ')
                    {
                        // Bump the character index counter/pointer.
                        posn++;

                        // If we hit the end of a paragraph, ignore this character position
                        // and look for a different test string.
                        if (textPassage[posn] == '\n' || textPassage[posn] == '\r')
                        {
                            restart = true;
                            break;
                        }
                    }
                    posn++;
                    wordCount++;

                    if (restart) break;
                }
                
                // When we've got the required number of words, quit the main loop.
                if (wordCount >= numberOfWords) break;
            }

            // Pass the excerpt of text back to the caller.
            return textPassage.Substring(startPosn, posn - startPosn); ;
        }

        /// <summary>
        /// Measures how accurate (roughly) the user typed the excerpt of text.
        /// </summary>
        /// <param name="excerpt">The excerpt of text to check the user's typing against</param>
        /// <param name="textTyped">The text typed by the user which we'll check against the
        /// excerpt</param>
        /// <param name="backspaceKeyCount">The number of times the backspace key had
        /// to be used when typing the excerpt of text</param>
        /// <returns>The accuracy of the typing as a percentage</returns>
        public decimal MeasureAccuracy(string excerpt, string textTyped, int backspaceKeyCount)
        {
            string[] excerptWords = excerpt.Split(' ');
            string[] typedWords = textTyped.Split(' ');

            // Find out the size of the largest of the 2 arrays.
            int maxArraySize;
            if (excerptWords.Length >= typedWords.Length)
                maxArraySize = excerptWords.Length;
            else
                maxArraySize = typedWords.Length;

            // Compare each word
            bool done = false;
            int excerptIndex = 0, typedIndex = 0;

            // Initialize the bad counter with the number of backspace key presses that were made.
            int badCounter = backspaceKeyCount;

            while (!done && 
                excerptIndex < excerptWords.Length && 
                typedIndex < typedWords.Length)
            {
                // If the words in typed word is the same as the excerpt word, we're good.
                if (excerptWords[excerptIndex] == typedWords[typedIndex])
                {
                    excerptIndex++;
                    typedIndex++;
                    continue;
                }

                // There's a mismatch between the typed and excerpt words so log it as an error.
                badCounter++;
                excerptIndex++;
                typedIndex++;

                // If we've hit the limit of the excerpt words array, signify that we 
                // need to bail out of the next iteration of the loop.
                if (excerptIndex >= excerptWords.Length)
                {
                    // Increase the bad counter by the difference between the array sizes.
                    // This will account for each additional word in the largest array.
                    badCounter += Math.Abs(excerptWords.Length - typedWords.Length);
                    done = true;
                }

                // If we've hit the limit of the typed words array, signify that we 
                // need to bail out of the next iteration of the loop.
                if (typedIndex >= typedWords.Length)
                {
                    // Increase the bad counter by the difference between the array sizes.
                    // This will account for each additional word in the largest array.
                    badCounter += Math.Abs(excerptWords.Length - typedWords.Length);
                    done = true;
                }
            }

            // Calculate the arracy of the typing.  If it's so bad, restrict it to 0.
            decimal accuracy = 100M - (100 * (decimal)badCounter / (decimal)maxArraySize);
            if (accuracy < 0) accuracy = 0;

            return accuracy;
        }

        /// <summary>
        /// Calculates how long it would take to type the whole of the text passage
        /// based on how long it's taken to type the excerpt.
        /// </summary>
        /// <param name="passageLength">The length of the text passage</param>
        /// <param name="excerptLength">The length of the excerpt the user has just typed</param>
        /// <param name="secondsTaken">The time the user has taken to type the excerpt</param>
        /// <returns></returns>
        public TimeSpan CalculateTimeToTypeTextPassage(
            int passageLength, 
            int excerptLength,
            double secondsTaken)
        {
            double secondsForPassage = secondsTaken * ((double)passageLength / (double)excerptLength);
            return TimeSpan.FromSeconds(secondsForPassage);
        }

        public int CalculateWordsPerMinute(double secondsTaken, decimal numberOfWords)
        {
            return (int)((double)numberOfWords * (60 / secondsTaken));
        }
    }
}
