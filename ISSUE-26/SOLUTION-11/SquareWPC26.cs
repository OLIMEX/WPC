using System;

class SquareWPC26
{
    static void Main(string[] args)
    {
        Console.WriteLine("Enter four point coordinates in the format (x,y) comma-separated:");
        string input = Console.ReadLine();

        Tuple<int, int>[] pointsTuple = ProcessInput(input);

        bool formingSquare = CheckFormingSquare(pointsTuple);

        Console.Write("\nThe four points are");
        if (!formingSquare)
        {
            Console.Write(" NOT");
        }
        Console.WriteLine(" forming a square.");
    }

    static bool CheckFormingSquare(Tuple<int, int>[] pointsTuple)
    {
        bool formingSquare = false;

        double side;
        double diagonal;

        double dist01 = CalculateDistance(pointsTuple[0], pointsTuple[1]);
        double dist02 = CalculateDistance(pointsTuple[0], pointsTuple[2]);
        double dist03 = CalculateDistance(pointsTuple[0], pointsTuple[3]);
        double dist12 = CalculateDistance(pointsTuple[1], pointsTuple[2]);
        double dist13 = CalculateDistance(pointsTuple[1], pointsTuple[3]);
        double dist23 = CalculateDistance(pointsTuple[2], pointsTuple[3]);

        if (dist01 == dist02 && dist01 != dist03)
        {
            side = dist01;
            diagonal = dist03;

            if (dist12 == diagonal && dist13 == side && dist23 == side)
            {
                formingSquare = true;
            }
        }
        else if (dist01 == dist03 && dist01 != dist02)
        {
            side = dist01;
            diagonal = dist02;

            if (dist13 == diagonal && dist12 == side && dist23 == side)
            {
                formingSquare = true;
            }
        }
        else if (dist02 == dist03 && dist02 != dist01)
        {
            side = dist02;
            diagonal = dist01;

            if (dist23 == diagonal && dist12 == side && dist13 == side)
            {
                formingSquare = true;
            }
        }

        return formingSquare;
    }

    static double CalculateDistance(Tuple<int, int> point1, Tuple<int, int> point2)
    {
        return Math.Sqrt(Math.Pow((point2.Item2 - point1.Item2), 2) + Math.Pow((point2.Item1 - point1.Item1), 2));
    }

    static Tuple<int, int>[] ProcessInput(string input)
    {
        string[] pointsString = input.Split(new string[] { "),(", "), (" }, StringSplitOptions.RemoveEmptyEntries);
        if (pointsString.Length != 4)
        {
            Console.WriteLine("Bad format! More than 4 point coordinates entered!");
            Environment.Exit(0);
        }

        Tuple<int, int>[] pointsTuple = new Tuple<int, int>[4];

        for (int i = 0; i < 4; i++)
        {
            pointsString[i] = pointsString[i].Trim();
            pointsString[i] = pointsString[i].TrimStart(new char[] { '(' });
            pointsString[i] = pointsString[i].TrimEnd(new char[] { ')' });

            string[] current = pointsString[i].Split(new char[] { ',' }, StringSplitOptions.RemoveEmptyEntries);
            if (current.Length != 2)
            {
                Console.WriteLine("Bad format of the coordinates! More than 2 coordinates for one point.");
                Environment.Exit(0);
            }
            int[] currentInt = new int[2];
            int.TryParse(current[0], out currentInt[0]);
            int.TryParse(current[1], out currentInt[1]);

            pointsTuple[i] = new Tuple<int, int>(currentInt[0], currentInt[1]);
        }

        return pointsTuple;
    }
}

