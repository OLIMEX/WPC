using System;

class Squares
{
    static void Main()
    {
        string input = Console.ReadLine();
        //string input = "(0,0),(1,1),(0,1),(1,0)";

        //processing the input
        string[] points = input.Split(new char[] { ')' }, StringSplitOptions.RemoveEmptyEntries);
        int[] x = new int[4];
        int[] y = new int[4];
        for (int i = 0; i < points.Length; i++)
        {
            string clean = points[i].Remove(points[i].IndexOf('('), 1);
            string[] coords = clean.Split(new char[] { ',' }, StringSplitOptions.RemoveEmptyEntries);
            x[i] = int.Parse(coords[0]);
            y[i] = int.Parse(coords[1]);
        }

        //calculating the distances between points
        double[] dist = new double[6];
        dist[0] = Math.Sqrt(((x[0] - x[1]) * (x[0] - x[1])) + ((y[0] - y[1]) * (y[0] - y[1])));
        dist[1] = Math.Sqrt(((x[0] - x[2]) * (x[0] - x[2])) + ((y[0] - y[2]) * (y[0] - y[2])));
        dist[2] = Math.Sqrt(((x[0] - x[3]) * (x[0] - x[3])) + ((y[0] - y[3]) * (y[0] - y[3])));
        dist[3] = Math.Sqrt(((x[1] - x[2]) * (x[1] - x[2])) + ((y[1] - y[2]) * (y[1] - y[2])));
        dist[4] = Math.Sqrt(((x[1] - x[3]) * (x[1] - x[3])) + ((y[1] - y[3]) * (y[1] - y[3])));
        dist[5] = Math.Sqrt(((x[2] - x[3]) * (x[2] - x[3])) + ((y[2] - y[3]) * (y[2] - y[3])));

        // finding the smallest side
        double minSide = double.MaxValue;
        for (int i = 0; i < 6; i++)
        {
            if (dist[i] < minSide)
            {
                minSide = dist[i];
            }
        }

        //finding if the sides and diagonals are equal
        int eqSides = 0;
        int eqDiag = 0;
        double diag = 0;
        for (int i = 0; i < 6; i++)
        {
            if (minSide == dist[i])
            {
                eqSides++;
            }
            else
            {
                diag = dist[i];
            }
        }
        for (int i = 0; i < 6; i++)
        {
            if (diag == dist[i])
            {
                eqDiag++;
            }
        }
        if (eqSides == 4 && eqDiag == 2)
        {
            Console.WriteLine("Figure is square");
        }
        else
        {
            Console.WriteLine("Figure is not square");
        }
    }
}

