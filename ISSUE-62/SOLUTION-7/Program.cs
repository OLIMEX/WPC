using System;
using System.Diagnostics;
using System.Threading;

namespace WPC62_OneMillion
{
    /// <summary>
    /// One million is good round number :) 
    /// Your task for the weekend challenge is to write code which check if you can 
    /// find two numbers X and Y which product makes exactly 1 000 000, the catch 
    /// is that none of these numbers should contain 0 inside it.
    /// How fast is your code?
    /// </summary>
    class Program
    {
        const int TARGET = 1000000;
        static Stopwatch stopwatch = new Stopwatch();

        static void Main(string[] args)
        {
            // We're going to run the code 10 times to see whether the time taken
            // by each run is consistent.
            for (int j = 0; j < 10; j++)
            {
                // Ok start timing...
                stopwatch.Start();

                // Only scan to half the target to avoid duplication of checks.
                for (int x = 1; x <= TARGET / 2; x++)
                {
                    // If we can divide the target by x with no remainder, this is
                    // a candidate value.
                    if (TARGET % x == 0)
                    {
                        // x is an integer product of the target value.  Get the other product.
                        int y = TARGET / x;

                        // This could be slow but let's see how slow it could be.
                        string strX = x.ToString();
                        string strY = y.ToString();
                        if (ValueHasAZero(strX) || ValueHasAZero(strY)) continue;

                        // We have a hit!
                        Console.WriteLine("{0} x {1} = {2}", x, y, TARGET);
                    }
                }

                // Done so check how long it's taken, roughly.
                stopwatch.Stop();
                long ticks = stopwatch.ElapsedTicks;

                Console.WriteLine("                        Finished.  Took {0} milliseconds", (double)ticks / 10000);
                Console.WriteLine();

                // Rest the app before starting the next timed run.
                Thread.Sleep(200);
                stopwatch.Reset();
            }

            Console.Read();
        }

        static bool ValueHasAZero(string value)
        {
            for (int i = 0; i < value.Length; i++)
            {
                if (value[i] == '0') return true;
            }

            return false;
        }
    }
}
