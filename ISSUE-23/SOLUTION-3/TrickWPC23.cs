/* Author: loloto
 * Olimex Weekend Programming Challenge - Week #23 – Evil code
 * 
 * Invent something small and evil which to be almost invisible and to cause lot of troubles to catch like:
 * #define struct union
 * #define double float
 * #define floor ceil
 * #define true (__LINE__&42) !=42
 * #define private public
 * */

using System;

class TrickWPC23
{
    static void Main(string[] args)
    {
        int a = 5;
        Console.WriteLine("a = {0}", a);
        // stuff
        \u0061 = 3;
        // stuff
        Console.WriteLine("a = {0}", a);
    }
}
