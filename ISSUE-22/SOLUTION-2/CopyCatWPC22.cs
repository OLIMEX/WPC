/* Author: loloto
 * 
 * Olimex Weekend Programming Challenge – Week #22 Plagiarism detector
 * Problem:
 * Make code which compare two texts and output the % of similarities between
 * the two texts i.e. if they have same words even if the words are in different order.
 * More advanced version may take care for synonyms , 
 * 
 * */

using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

class CopyCatWPC22
{
    static void Main(string[] args)
    {
        // Bigger console input
        Console.SetIn(new StreamReader(Console.OpenStandardInput(8192)));

        string text1;
        Console.WriteLine("Enter text 1:");
        text1 = Console.ReadLine();

        string text2;
        Console.WriteLine("\nEnter text 2:");
        text2 = Console.ReadLine();

        List<string> words1 = GetWords(text1);
        List<string> words2 = GetWords(text2);

        int numberOfEqualWords = IntersectionCountWithDuplicates(words1, words2);
        double equalityCoefficient = numberOfEqualWords / (double)words2.Count;

        Console.WriteLine("\n{0:P} of the words used in text 2 are used in text 1, too.", equalityCoefficient);
    }

    static int IntersectionCountWithDuplicates(List<string> words1, List<string> words2)
    {
        List<string> words2Copy = new List<string>(words2);
        int count = 0;

        foreach (var word in words1)
        {
            if (words2Copy.Contains(word))
            {
                words2Copy.Remove(word);
                count++;
            }
        }

        return count;
    }

    static List<string> GetWords(string text)
    {
        List<string> words = new List<string>();

        int charIndex = 0;
        StringBuilder currentWord = new StringBuilder();

        while (charIndex < text.Length)
        {
            if (!Char.IsLetter(text[charIndex]))
            {
                charIndex++;
            }
            else
            {
                while (charIndex < text.Length && Char.IsLetter(text[charIndex]))
                {
                    currentWord.Append(text[charIndex]);
                    charIndex++;
                }

                words.Add(currentWord.ToString());
                currentWord.Clear();
            }
        }

        return words;
    }
}
