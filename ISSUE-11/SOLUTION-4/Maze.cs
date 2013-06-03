using System;
using System.Collections.Generic;
using System.Linq;

namespace Olimex_Programming_Challenge_11
{
    public class Maze
    {
        public int[,] MazeMatrix { get; set; }
        public Size Dimensions { get; set; }

        public Maze(string[] fileLines)
        {
            // Check that the input meets expected design criteria (size and orthogonal shape).
            Dimensions = ValidateInputMaze(fileLines);

            // Parse the input maze into an array.
            MazeMatrix = ParseInput(fileLines);

            // Consolidate adjoining obstacles.
            MazeMatrix = ConsolidateObstacles(MazeMatrix);
        }

        /// <summary>
        /// Parse the input characters into a matrix of obstacle numbers.
        /// </summary>
        /// <param name="fileLines">The lines of text from the input maze file.</param>
        /// <returns>A 2-dimensional array containing a number where an obstacle is located.
        /// </returns>
        private int[,] ParseInput(string[] fileLines)
        {
            // Create an array of the right size to accommodate the maze.
            int[,] matrix = new int[Dimensions.X, Dimensions.Y];

            int obstacle = 0;
            bool foundObstacle = false;
            int x, y;

            // Start at the top left corner and work across the matrix
            // from left to right and moving down through each line.
            // (0,0) is the top left corner of the maze
            for (y = 0; y < Dimensions.Y; y++)
            {
                for (x = 0; x < Dimensions.X; x++)
                {
                    char c = fileLines[y][x];
                    switch (c)
                    {
                        case 'W':
                            foundObstacle = false;
                            break;

                        case '@':
                            // The first time we come across an obstacle, treat it as a new one.
                            if (!foundObstacle)
                            {
                                obstacle++;
                            }

                            // Give the square an obstacle number.
                            matrix[x, y] = obstacle;
                            foundObstacle = true;
                            break;

                        case ' ':
                            foundObstacle = false;
                            break;

                        default:
                            break;
                    }
                }
            }

            return matrix;
        }

        /// <summary>
        /// Takes the 2-dimensional array of obstacle numbers and consolidates them into one
        /// obstacle number for each contiguous block of obstacles.
        /// </summary>
        /// <param name="matrix">The 2-dimensional array of obstacle numbers.</param>
        /// <returns>A consolidated array where each contiguous block of obstacles is represented
        /// by one obstacle number.</returns>
        private int[,] ConsolidateObstacles(int[,] matrix)
        {
            // At this point some of the contiguous obstacles will have the same
            // obstacle number but some, more complex, obstacles won't.  We need
            // to consolidate the values so we can count up the number of obstacles
            // in each contiguous block.
            bool changeMade = true;

            // We may need several passes through this routine until we get to the point
            // where we haven't had to change an obstacle number.
            while (changeMade)
            {
                changeMade = false;
                for (int y = 0; y < Dimensions.Y; y++)
                {
                    for (int x = 0; x < Dimensions.X; x++)
                    {
                        // If the square we're looking is an obstacle, then it's possible 
                        // we may need to consolidate the current matrix value.
                        if (matrix[x, y] != 0)
                        {
                            // Look at the squares surrounding the current one.
                            int above = 0;
                            int left = 0;
                            int right = 0;
                            int below = 0;
                            int aboveLeft = 0;
                            int aboveRight = 0;
                            int belowLeft = 0;
                            int belowRight = 0;

                            if (x > 0) left = matrix[x - 1, y];
                            if (x > 0 && y > 0) aboveLeft = matrix[x - 1, y - 1];
                            if (y > 0) above = matrix[x, y - 1];
                            if (y > 0 && x < Dimensions.X) aboveRight = matrix[x + 1, y - 1];
                            if (x < Dimensions.X) right = matrix[x + 1, y];
                            if (x < Dimensions.X && y < Dimensions.Y) belowRight = matrix[x + 1, y + 1];
                            if (y < Dimensions.Y) below = matrix[x, y + 1];
                            if (y < Dimensions.Y && x > 0) belowLeft = matrix[x - 1, y + 1];

                            // If there's an obstacle in any of the surrounding squares, set the
                            // current matrix value to the minimum obstacle value from the surrounding squares.
                            if (left != 0 || aboveLeft != 0 || above != 0 || aboveRight != 0 ||
                                right != 0 || belowRight != 0 || below != 0 || belowLeft != 0)
                            {
                                int minObstacle = GetMinimumValue(left, aboveLeft, above, aboveRight, right, belowRight, below, belowLeft);
                                if (matrix[x, y] != minObstacle)
                                {
                                    matrix[x, y] = minObstacle;
                                    changeMade = true;
                                }
                            }
                        }
                    }
                }
            }

            // Pass back the consolidated array of obstacle numbers.
            return matrix;
        }


        /// <summary>
        /// Get a tally of how many obstacles comprise each contiguous block.
        /// </summary>
        /// <returns>The number of obstacles in the largest contiguous block.</returns>
        public int CalculateLargestObstacle()
        {
            Dictionary<int, int> obstacles = new Dictionary<int, int>();
            for (int y = 0; y < Dimensions.Y; y++)
            {
                for (int x = 0; x < Dimensions.X; x++)
                {
                    int obstacle = MazeMatrix[x, y];
                    if (obstacle > 0)
                    {
                        if (!obstacles.ContainsKey(obstacle))
                        {
                            obstacles.Add(obstacle, 0);
                        }

                        obstacles[obstacle] += 1;
                    }
                }
            }

            // Find the largest value in the obstacles dictionary.
            int maxObstacles = 0;
            foreach (KeyValuePair<int, int> obstacle in obstacles)
            {
                if (obstacle.Value > maxObstacles) 
                    maxObstacles = obstacle.Value;
            }

            return maxObstacles;
        }

        /// <summary>
        /// Gets the minimum value from a set of 8 values.
        /// </summary>
        /// <param name="value1">One of the 8 values</param>
        /// <param name="value2">One of the 8 values</param>
        /// <param name="value3">One of the 8 values</param>
        /// <param name="value4">One of the 8 values</param>
        /// <param name="value5">One of the 8 values</param>
        /// <param name="value6">One of the 8 values</param>
        /// <param name="value7">One of the 8 values</param>
        /// <param name="value8">This is getting boring but I think you know what this is</param>
        /// <returns></returns>
        private int GetMinimumValue(int value1, int value2, int value3, int value4, 
                                    int value5, int value6, int value7, int value8)
        {
            int minimum = int.MaxValue;
            minimum = GetLower(value1, minimum);
            minimum = GetLower(value2, minimum);
            minimum = GetLower(value3, minimum);
            minimum = GetLower(value4, minimum);
            minimum = GetLower(value5, minimum);
            minimum = GetLower(value6, minimum);
            minimum = GetLower(value7, minimum);
            minimum = GetLower(value8, minimum);
            return minimum;
        }

        /// <summary>
        /// Gets the lower of two positive values.
        /// </summary>
        /// <param name="value1"></param>
        /// <param name="value2"></param>
        /// <returns></returns>
        private int GetLower(int value1, int value2)
        {
            if (value1 != 0 && value1 < value2)
                return value1;
            else
                return value2;
        }

        /// <summary>
        /// Validates that we have a suitable maze in the text file before parsing.
        /// </summary>
        /// <param name="fileLines">The lines of text from the input maze file.</param>
        /// <returns>The dimensions of the maze (the length of the horizontal and 
        /// vertical sides)</returns>
        /// <exception cref="Exception">This will be thrown if the maze fails validation.
        /// </exception>
        private Size ValidateInputMaze(string[] fileLines)
        {
            int x = 0;
            int y = 0;

            if (fileLines.Count<string>() != 0)
            {
                // Check that all lines are of equal length.
                bool allLinesEqualLength = true;
                int lineLength = 0;
                foreach (string line in fileLines)
                {
                    // For the first line, just setup the length we need to check all 
                    // subsequent lines against.
                    if (lineLength == 0)
                    {
                        lineLength = line.Length;
                    }
                    else
                    {
                        if (lineLength != line.Length)
                        {
                            allLinesEqualLength = false;
                            break;
                        }
                    }

                    // Convert the line to upper case.
                    fileLines[y++] = line.ToUpper();
                }

                // We now know the size of the maze.
                x = lineLength;
                y = fileLines.Count<string>();

                // Check that the size conforms to our strict limits.
                if (!allLinesEqualLength || x < 3 || x > 100 || y < 3 || y > 100)
                {
                    throw new Exception(
                        "Input file has lines that are not all the same length " +
                        "or exceeds design limits.");
                }
            }
            else
            {
                throw new Exception("Input file is empty.");
            }

            return new Size(x, y);
        }
    }

    /// <summary>
    /// Data object to hold the dimensions of the maze.
    /// </summary>
    public class Size
    {
        public int X { get; set; }
        public int Y { get; set; }

        public Size(int x, int y)
        {
            X = x;
            Y = y;
        }
    }
}
