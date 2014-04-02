using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WPCWeek48;

namespace WPCWeek48
{
    class Program
    {
        static void Main(string[] args)
        {
            Point[] points = new Point[3];

            string p = "A";
            for (int i = 0; i <= 2; i++)
            {
                if (i == 1) p = "B";
                if (i == 2) p = "C";

                points[i] = new Point();
                points[i].Name = p;
                Console.Write("{0}(X): ", p);
                points[i].X = Int32.Parse(Console.ReadLine());
                Console.Write("{0}(Y): ", p);
                points[i].Y = Int32.Parse(Console.ReadLine());
                Console.WriteLine();
            }

            bool sameLine = (points[0].X == points[1].X) && points[0].X == points[2].X ? true : false;

            if (sameLine) Console.WriteLine("Points are in a same line!");
            else
            {
                int posA = 0;
                int posB = 0;
                int posC = 0;

                for (int i = 0; i < 2; i++)
                {
                    for (int j = 1; j <= 2; j++)
                    {
                        if (points[i].X > points[j].X)
                        {
                            Point temp = points[i];
                            points[i] = points[j];
                            points[j] = temp;
                        }
                    }
                }

                for (int i = 0; i <= 2; i++)
                {
                    if (points[i].Name == "A") posA = i;
                    if (points[i].Name == "B") posB = i;
                    if (points[i].Name == "C") posC = i;
                }

                string turn = "";

                if (posA == 0)
                {
                    if (posB == 1)
                    {
                        if (points[posB].Y > points[posA].Y) turn = "Clockwise";
                        else turn = "Counter clockwise";
                    }
                    else
                    {
                        if (points[posC].Y > points[posB].Y) turn = "Counter clockwise";
                        else turn = "Clockwise";
                    }
                }
                else if (posA == 1)
                {
                    if (posB == 0)
                    {
                        if (points[posB].Y < points[posA].Y) turn = "Counter clockwise";
                        else turn = "Clockwise";
                    }
                    else
                    {
                        if (points[posC].Y > points[posB].Y) turn = "Counter clockwise";
                        else turn = "Clockwise";
                    }
                }
                else
                {
                    if (posB == 0)
                    {
                        if (points[posB].Y > points[posC].Y) turn = "Counter clockwise";
                        else turn = "Clockwise";
                    }
                    else
                    {
                        if (points[posB].Y > points[posC].Y) turn = "Counter clockwise";
                        else turn = "Clockwise";
                    }
                }

                Console.WriteLine("Turn: {0}", turn);
            }


        }
    }
}