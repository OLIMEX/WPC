using System;
using System.IO;

namespace Olimex_Programming_Challenge_11
{
    /// <summary>
    /// Problem:
    /// 
    /// Let’s have maze with size X x Y where X and Y are integer (3..100) .
    /// The maze is defined with strings, where in the string ‘W’ is wall, ‘@’ is obstacle and ' ' is air.
    /// Make code which finds the largest by area of connected obstacles in the maze.
    /// 
    /// For instance:
    /// Input:
    /// 
    /// WWWWWWWWWW
    /// W  WW    W
    /// W       WW
    /// W  @@    W
    /// W @@     W
    /// W      @ W
    /// W@    @@ W
    /// WWWWWWWWWW
    /// 
    /// should output: 4 as the largest area obstracles is composed by 4 @ connected together.
    /// </summary>
    class Program
    {
        static void Main(string[] args)
        {
            // Loop round until the user hits the Enter key.
            while (true)
            {
                // Get the name of the test maze file.
                Console.WriteLine("To quit, press the Enter key.");
                Console.Write("Enter the number of the maze file, e.g. 1 : ");
                string fileId = Console.ReadLine();
                if (fileId.Length == 0) break;

                // Build the path to the text file containing the maze to check.
                string filename = 
                    Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "TestFiles", fileId + ".txt");

                if (File.Exists(filename))
                {
                    // Read the maze from the file.
                    string[] lines = File.ReadAllLines(filename);

                    try
                    {
                        // Parse the maze into a 2-dimensional array.
                        Maze maze = new Maze(lines);

                        // Show the parsed maze for optical verification.
                        DrawMatrix(maze);

                        // Calculate the largest obstacle in the maze.
                        int largestObstacle = maze.CalculateLargestObstacle();

                        Console.WriteLine(
                            string.Format("The largest obstacle occupies {0} squares.", largestObstacle));
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine(ex.Message);
                    }
                }
                else
                {
                    Console.WriteLine("File doesn't exist : " + filename);
                }
                Console.WriteLine();
                Console.WriteLine();
            }
        }

        /// <summary>
        /// Draws the maze after parsing for optical verification that it's done a good job.
        /// </summary>
        /// <param name="matrix">The maze object which contains the 2-dimensional array.</param>
        private static void DrawMatrix(Maze matrix)
        {
            for (int y = 0; y < matrix.Dimensions.Y; y++)
            {
                for (int x = 0; x < matrix.Dimensions.X; x++)
                {
                    if (matrix.MazeMatrix[x, y] == 0)
                        Console.Write(" .");
                    else
                        Console.Write(matrix.MazeMatrix[x, y].ToString().PadLeft(2,' '));
                }
                Console.WriteLine();
            }
            Console.WriteLine();
        }
    }
}
