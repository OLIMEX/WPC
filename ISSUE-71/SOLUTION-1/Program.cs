using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Timers;

namespace knock_knock
{
    class Program
    {
        static List<int> timerPauseDuration = new List<int>();
        static List<int> tempSequenceDuration = new List<int>();
        static Timer stateTimer = new Timer(200);
        static Timer stateTimer2 = new Timer(200);
        static int shortInterval = 3; //adjust this for short/long interval
        static bool door = false;
        static public void learn()
        {
            timerPauseDuration.Clear();
            ConsoleKeyInfo key = new ConsoleKeyInfo();
            while (key.Key != ConsoleKey.Enter)
            { 
                key = Console.ReadKey();
                stateTimer.Stop();
                if (key.Key == ConsoleKey.Spacebar)
                {
                    Console.Write("knock");
                    timerPauseDuration.Add(0);
                    stateTimer.Start();
                }
            }
            Console.Write("knock");
            stateTimer.Stop();
        }
        static public void check()
        {
            tempSequenceDuration.Clear();
            ConsoleKeyInfo key = new ConsoleKeyInfo();
            for (int i = 0; i < timerPauseDuration.Count;i++)
            {
                key = Console.ReadKey();
                stateTimer2.Stop();
                if (key.Key == ConsoleKey.Spacebar)
                {
                    tempSequenceDuration.Add(0);
                    stateTimer2.Start();
                }
            }
            stateTimer2.Stop();
                bool mistake = false;
                for (int i = 0; i < timerPauseDuration.Count; i++)
                {
                    if ((timerPauseDuration[i] <= shortInterval
                        && tempSequenceDuration[i] <= shortInterval)
                        ||
                        (timerPauseDuration[i] > shortInterval
                        && tempSequenceDuration[i] > shortInterval))
                        mistake = false;
                    else
                    {
                        mistake = true;
                        break;
                    }
                }
                if (!mistake)
                {
                    door = !door;
                    if (door)
                        Console.WriteLine("Door opened!");
                    else
                        Console.WriteLine("Door closed!");
                }
                else
                {
                    Console.WriteLine("Wrong duration!");
                }
        }
        static void showTextSequence()
        {
            for (int i = 0; i < timerPauseDuration.Count; i++)
            {
                Console.Write("knock");
                if (timerPauseDuration[i] <= shortInterval) Console.Write(" short ");
                if (timerPauseDuration[i] > shortInterval) Console.Write(" long ");
            }
            Console.Write("knock");
        }
        static void Main(string[] args)
        {
            stateTimer.Elapsed += new ElapsedEventHandler(stateTimer_Elapsed);
            stateTimer2.Elapsed += new ElapsedEventHandler(stateTimer2_Elapsed);
            Console.WriteLine("Press L to Learn new sequence, S to show sequence, C to check sequence and if it is correct, it will open/close the door.");
            Console.WriteLine("Note: At the end of input new sequence, press Enter to stop.");
            ConsoleKeyInfo key = new ConsoleKeyInfo();
            while (key.Key != ConsoleKey.Escape)
            {
                key = Console.ReadKey();
                Console.WriteLine("");
                if (key.Key == ConsoleKey.L)
                {
                    Console.WriteLine("Input the sequence to trigger the door!");
                    learn();
                    Console.WriteLine(" ");
                }
                if (key.Key == ConsoleKey.S)
                {
                    Console.WriteLine("Sequence is:");
                    showTextSequence();
                    Console.WriteLine(" ");
                }
                if (key.Key == ConsoleKey.C)
                {
                    Console.WriteLine("Input your sequence to open/ close the door!");
                    check();
                    Console.WriteLine(" ");
                }

            }

        }

        static void stateTimer2_Elapsed(object sender, ElapsedEventArgs e)
        {
            tempSequenceDuration[tempSequenceDuration.Count - 1]++;
        }

        static void stateTimer_Elapsed(object sender, ElapsedEventArgs e)
        {
            timerPauseDuration[timerPauseDuration.Count - 1]++;
        }
    }
}
