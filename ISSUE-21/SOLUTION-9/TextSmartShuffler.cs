using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

class TextSmartShuffler
{
    static void Main(string[] args)
    {
        // Bigger console input
        Console.SetIn(new StreamReader(Console.OpenStandardInput(8192)));
        //Console.OutputEncoding = Encoding.UTF8;

        string inputText;
        Console.WriteLine("Enter text to shuffle:");
        inputText = Console.ReadLine();

        StringBuilder outputText = new StringBuilder(inputText.Length);

        int charIndex = 0;
        StringBuilder currentWord = new StringBuilder();
        string currentShuffledWord;

        while (charIndex < inputText.Length)
        {
            if (!Char.IsLetter(inputText[charIndex]))
            {
                outputText.Append(inputText[charIndex]);
                charIndex++;
            }
            else
            {
                while (charIndex < inputText.Length && Char.IsLetter(inputText[charIndex]))
                {
                    currentWord.Append(inputText[charIndex]);
                    charIndex++;
                }

                currentShuffledWord = GetShuffledWord(currentWord.ToString());
                outputText.Append(currentShuffledWord);

                currentWord.Clear();
            }
        }

        Console.WriteLine("Shuffled text:");
        Console.WriteLine(outputText);
    }

    static string GetShuffledWord(string inputWord)
    {
        StringBuilder shuffledWord = new StringBuilder(inputWord);

        List<char> middleLetters = GetMiddleLetters(inputWord);

        Random rand = new Random();

        for (int i = 1; i < inputWord.Length - 1; i++)
        {
            int randomIndex = rand.Next(0, middleLetters.Count);
            shuffledWord[i] = middleLetters[randomIndex];
            middleLetters.RemoveAt(randomIndex);
        }

        return shuffledWord.ToString();
    }

    static List<char> GetMiddleLetters(string inputWord)
    {
        List<char> letters = new List<char>();

        for (int i = 1; i < inputWord.Length - 1; i++)
        {
            letters.Add(inputWord[i]);
        }

        return letters;
    }
}

