using System;
using System.IO;

namespace WPC35_Maze
{
    /// <summary>
    /// Problem:
    /// Maze with 10×10 squares have obstacles placed on random squares marked with the black.
    /// Make code which finds path which starts from square (1,1) and moves through all Maze 
    /// squares and returns back to square(1,1) without stepping on same square more than once.
    /// 
    /// Assume that valid moves are only up-down-left-right.
    /// 
    /// For example:
    /// 9 . . . . . . . . . .
    /// 8 . . . . . . . B . .
    /// 7 . B . . . . . . . .
    /// 6 . . . . . . . . . .
    /// 5 . . . . B . . . . .
    /// 4 . . . . . . . . . .
    /// 3 . . . . . . . . . .
    /// 2 . . B . . . . B . .
    /// 1 . . . . B . . . . .
    /// 0 . . . . . . . . . .
    ///   0 1 2 3 4 5 6 7 8 9 
    /// 
    /// </summary>
    class Program
    {
        private static int SquareSize;
        private static int solutionsFound = 0;
        private static SquareState[,] matrix;
        private static Square startingSquare;
        private static int targetLength = 0;
        private static StreamWriter sw;             // To write paths found to a log file

        /// <summary>
        /// One complex sample maze to test with.  1 = start/finish, 2 = obstacle
        /// This takes a few minutes to solve!
        /// </summary>
        private static int[,] grid1 = new int[,]
            {
                { 1,0,0,0,0, 0,0,0,0,0 },
                { 0,2,2,2,2, 2,2,2,2,0 },
                { 0,2,2,0,0, 2,2,0,0,0 },
                { 0,2,2,0,0, 2,2,0,0,0 },
                { 0,2,2,0,0, 2,2,0,0,0 },
                { 0,2,2,0,0, 2,2,0,0,0 },
                { 0,2,2,0,0, 2,2,0,0,0 },
                { 0,2,2,0,0, 2,2,0,0,0 },
                { 0,0,0,0,0, 0,0,0,0,0 },
                { 0,0,0,0,0, 0,0,0,0,0 }
            };

        /// <summary>
        /// Another sample maze to test with.  1 = start/finish, 2 = obstacle
        /// This takes *hours* to solve.
        /// </summary>
        private static int[,] grid2 = new int[,]
            {
                { 1,0,0,0,0, 0,0,0,0,0 },
                { 0,0,0,0,0, 0,0,0,0,0 },
                { 0,0,2,2,2, 2,2,2,0,0 },
                { 0,0,2,2,2, 2,2,2,0,0 },
                { 0,0,2,2,2, 2,2,2,0,0 },
                { 0,0,2,2,2, 2,2,2,0,0 },
                { 0,0,2,2,2, 2,2,2,0,0 },
                { 0,0,2,2,2, 2,2,2,0,0 },
                { 0,0,0,0,0, 0,0,0,0,0 },
                { 0,0,0,0,0, 0,0,0,0,0 }
            };

        /// <summary>
        /// A simple one for debugging purposes.  1 = start/finish, 2 = obstacle
        /// This is solved in less than a second.
        /// </summary>
        private static int[,] grid3 = new int[,]
        {
            { 1,0,0,0,0 },
            { 0,2,0,0,0 },
            { 0,2,0,0,0 },
            { 0,2,0,0,0 },
            { 0,0,0,0,0 }
        };

        /// <summary>
        /// All good things have to start somewhere.
        /// </summary>
        /// <param name="args">None, ignored.</param>
        static void Main(string[] args)
        {
            // Setup a matrix to test with.
            matrix = SetupMatrixTest(grid1);

            // Open a log file so we can write out the paths we find.
            string logFile = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "WPC35-solutions.txt");
            sw = new StreamWriter(logFile);
            sw.WriteLine("Olimex Weekend Programming Challenge 35 - 30 Nov 2013");
            sw.WriteLine("-----------------------------------------------------");
            sw.WriteLine();

            // Starting square
            startingSquare = new Square(0, 0);
            startingSquare.PreviousSquare = new Point(-1, -1);
            startingSquare.SquareCounter = 1;

            // Start recursing...
            CheckSquare(startingSquare);

            // Finished.  Close the log file.
            string message = string.Format("Finished!!  Number of paths found = {0}", solutionsFound);
            Console.WriteLine();
            Console.WriteLine(message);
            sw.WriteLine();
            sw.WriteLine(message);
            sw.Close();

            // Wait for user to close the console.
            Console.ReadLine();
        }

        /// <summary>
        /// The main recursion routine that checks whether a square is valid for the current path and
        /// moves the path along to that square.  Then we call ourself again to recurse further along 
        /// the path.
        /// </summary>
        /// <param name="tracker">The current square we're looking at in the maze.</param>
        /// <returns>true when a valid solutin is found (all squares occupied); false otherwise</returns>
        private static bool CheckSquare(Square tracker)
        {
            Square clone;

            // Check if we've reached the start/finish point
            if (tracker.CurrentSquare == startingSquare.CurrentSquare)
            {
                // Check whether all the squares in the maze are occupied.  If they are, we have
                // a valid solution.
                if (AllSquaresFilled())
                {
                    // It's a valid path!
                    solutionsFound++;
                    DrawSolutionPath();
                    return true;
                }
            }

            // We could have occupied all squares in the maze but hit a dead-end.  This detects that
            // and quits the recursion to back-track to the previous square.
            if (tracker.SquareCounter >= targetLength)
            {
                // Reset the current square to an empty one
                matrix[tracker.CurrentSquare.X, tracker.CurrentSquare.Y] = SquareState.Empty;
                return false;
            }

            // Get the state of the squares adjoining the current one
            SquareState squareAboveState = GetAdjoiningSquareState(Direction.UP,    tracker);
            SquareState squareRightState = GetAdjoiningSquareState(Direction.RIGHT, tracker);
            SquareState squareBelowState = GetAdjoiningSquareState(Direction.DOWN,  tracker);
            SquareState squareLeftState  = GetAdjoiningSquareState(Direction.LEFT,  tracker);

            // If it's OK to move up, do so
            if (squareAboveState == SquareState.Empty || squareAboveState == SquareState.StartFinish)
            {
                // Mark the square as being on the path.
                if (squareAboveState == SquareState.Empty || squareLeftState == SquareState.StartFinish)
                    MarkTravelDirection(tracker, Direction.UP);

                // Create a clone of the current square to pass into the next recursion
                clone = new Square(tracker);

                // Bump the counter that keeps track of the number of squares are along the path
                clone.SquareCounter++;

                // Move to the square above
                clone.PreviousSquare.X = clone.CurrentSquare.X;
                clone.PreviousSquare.Y = clone.CurrentSquare.Y;
                clone.CurrentSquare.Y++;

                // And check that.
                if (CheckSquare(clone))
                {
                    // Reset the current square
                    matrix[tracker.CurrentSquare.X, tracker.CurrentSquare.Y] = SquareState.Empty;
                    return false;
                }
            }

            // If it's OK to move right, do so
            if (squareRightState == SquareState.Empty || squareRightState == SquareState.StartFinish)
            {
                // Mark the square as being on the path.
                if (squareRightState == SquareState.Empty || squareLeftState == SquareState.StartFinish)
                    MarkTravelDirection(tracker, Direction.RIGHT);

                // Create a clone of the current square to pass into the next recursion
                clone = new Square(tracker);

                // Bump the counter that keeps track of the number of squares are along the path
                clone.SquareCounter++;

                // Move to the square to the right
                clone.PreviousSquare.X = clone.CurrentSquare.X;
                clone.PreviousSquare.Y = clone.CurrentSquare.Y;
                clone.CurrentSquare.X++;

                // And check that.
                if (CheckSquare(clone))
                {
                    // Reset the current square
                    matrix[tracker.CurrentSquare.X, tracker.CurrentSquare.Y] = SquareState.Empty;
                    return false;
                }
            }

            // If it's OK to move down, do so
            if (squareBelowState == SquareState.Empty || squareBelowState == SquareState.StartFinish)
            {
                // Mark the square as being on the path.
                if (squareBelowState == SquareState.Empty || squareLeftState == SquareState.StartFinish)
                    MarkTravelDirection(tracker, Direction.DOWN);

                // Create a clone of the current square to pass into the next recursion
                clone = new Square(tracker);

                // Bump the counter that keeps track of the number of squares are along the path
                clone.SquareCounter++;

                // Move to the square below
                clone.PreviousSquare.X = clone.CurrentSquare.X;
                clone.PreviousSquare.Y = clone.CurrentSquare.Y;
                clone.CurrentSquare.Y--;

                // And check that.
                if (CheckSquare(clone))
                {
                    // Reset the current square
                    matrix[tracker.CurrentSquare.X, tracker.CurrentSquare.Y] = SquareState.Empty;
                    return false;
                }
            }

            // If it's OK to move left, do so
            if (squareLeftState == SquareState.Empty || squareLeftState == SquareState.StartFinish)
            {
                // Mark the square as being on the path.
                if (squareLeftState == SquareState.Empty || squareLeftState == SquareState.StartFinish)
                    MarkTravelDirection(tracker, Direction.LEFT);

                // Create a clone of the current square to pass into the next recursion
                clone = new Square(tracker);

                // Bump the counter that keeps track of the number of squares are along the path
                clone.SquareCounter++;

                // Move to the square to the left
                clone.PreviousSquare.X = clone.CurrentSquare.X;
                clone.PreviousSquare.Y = clone.CurrentSquare.Y;
                clone.CurrentSquare.X--;

                // And check that.
                if (CheckSquare(clone))
                {
                    // Reset the current square
                    matrix[tracker.CurrentSquare.X, tracker.CurrentSquare.Y] = SquareState.Empty;
                    return false;
                }
            }

            // No more routes available from the current square so it's not viable.
            // As long as the current square is not the start/finish, clear it and go back to
            // the caller to try another route from the previous square along the path.
            if (matrix[tracker.CurrentSquare.X, tracker.CurrentSquare.Y] != SquareState.StartFinish)
            {
                matrix[tracker.CurrentSquare.X, tracker.CurrentSquare.Y] = SquareState.Empty;
            }

            return false;
        }


        /// <summary>
        /// Gets the state of a square adjacent to the specified one.
        /// </summary>
        /// <param name="direction">The direction to look in (left, right, up or down)</param>
        /// <param name="square">The reference square.</param>
        /// <returns>Whether the square is empty, the start or finish point, an obstacle or 
        /// one that's on the current path</returns>
        private static SquareState GetAdjoiningSquareState(Direction direction, Square square)
        {
            int xOffset = 0;
            int yOffset = 0;

            if (direction == Direction.UP && square.CurrentSquare.Y + 1 < SquareSize)
                yOffset = 1;
            else if (direction == Direction.DOWN && square.CurrentSquare.Y - 1 >= 0)
                yOffset = -1;
            else if (direction == Direction.RIGHT && square.CurrentSquare.X + 1 < SquareSize)
                xOffset = 1;
            else if (direction == Direction.LEFT && square.CurrentSquare.X - 1 >= 0)
                xOffset = -1;
            else
                return SquareState.InvalidSquare;

            return matrix[square.CurrentSquare.X + xOffset, square.CurrentSquare.Y + yOffset];
        }


        /// <summary>
        /// Check whether there are any empty squares in the matrix.
        /// </summary>
        /// <returns>false if there's an empty square; true if all are occupied</returns>
        /// <remarks>This could be done a bit more efficiently I know but it's just a weekend
        /// challenge!</remarks>
        private static bool AllSquaresFilled()
        {
            for (int y = 0; y < SquareSize; y++)
            {
                for (int x = 0; x < SquareSize; x++)
                {
                    if (matrix[x, y] == SquareState.Empty)
                        return false;
                }
            }
            return true;
        }


        /// <summary>
        /// Initialise our rich matrix from a simple 2-dimensional int array containing the 
        /// start/finish and obstacles.
        /// </summary>
        /// <param name="grid">The simple int array that says where the start/finish and
        /// obstacles are located.</param>
        /// <returns>The array of squares that make up the maze which identifies the state
        /// of each square in the maze.</returns>
        private static SquareState[,] SetupMatrixTest(int[,] grid)
        {
            SquareSize = grid.GetUpperBound(0) + 1;
            SquareState[,] matrix = new SquareState[SquareSize, SquareSize];
            for (int y = 0; y < SquareSize; y++)
            {
                for (int x = 0; x < SquareSize; x++)
                {
                    matrix[x, y] = (SquareState)grid[x, y];
                    if (grid[x, y] == 0) targetLength++;
                }
            }

            // Include the start and finish square as being along the path
            targetLength += 2; ;

            return matrix;
        }
        
        
        /// <summary>
        /// Marks the square in the matrix to indicate the direction we're moving through the
        /// square.  This allows us to render the path simply using ASCII art.
        /// </summary>
        /// <param name="tracker">The current square in the maze that we're looking at</param>
        /// <param name="outDirection">The direction the path takes when leaving the current 
        /// tracker square (up, right, down or left).</param>
        private static void MarkTravelDirection(Square tracker, Direction outDirection)
        {
            SquareState currentSquareTravel = SquareState.OnThePath;

            if (outDirection == Direction.UP)
            {
                if (tracker.CurrentSquare == startingSquare.CurrentSquare)
                {
                    return;
                }
                else if (tracker.PreviousSquare.X == tracker.CurrentSquare.X)
                {
                    currentSquareTravel = SquareState.TravelNS;
                }
                else if (tracker.PreviousSquare.X - 1 == tracker.CurrentSquare.X)
                {
                    currentSquareTravel = SquareState.TravelNE;
                }
                else if (tracker.PreviousSquare.X + 1 == tracker.CurrentSquare.X)
                {
                    currentSquareTravel = SquareState.TravelNW;
                }
            }
            else if (outDirection == Direction.RIGHT)
            {
                if (tracker.CurrentSquare == startingSquare.CurrentSquare)
                {
                    return;
                }
                else if (tracker.PreviousSquare.Y == tracker.CurrentSquare.Y)
                {
                    currentSquareTravel = SquareState.TravelWE;
                }
                else if (tracker.PreviousSquare.Y - 1 == tracker.CurrentSquare.Y)
                {
                    currentSquareTravel = SquareState.TravelNE;
                }
                else if (tracker.PreviousSquare.Y + 1 == tracker.CurrentSquare.Y)
                {
                    currentSquareTravel = SquareState.TravelSE;
                }
            }
            else if (outDirection == Direction.DOWN)
            {
                if (tracker.CurrentSquare == startingSquare.CurrentSquare)
                {
                    return;
                }
                else if (tracker.PreviousSquare.X == tracker.CurrentSquare.X)
                {
                    currentSquareTravel = SquareState.TravelNS;
                }
                else if (tracker.PreviousSquare.X - 1 == tracker.CurrentSquare.X)
                {
                    currentSquareTravel = SquareState.TravelSE;
                }
                else if (tracker.PreviousSquare.X + 1 == tracker.CurrentSquare.X)
                {
                    currentSquareTravel = SquareState.TravelSW;
                }
            }
            else if (outDirection == Direction.LEFT)
            {
                if (tracker.CurrentSquare == startingSquare.CurrentSquare)
                {
                    return;
                }
                else if (tracker.PreviousSquare.Y == tracker.CurrentSquare.Y)
                {
                    currentSquareTravel = SquareState.TravelWE;
                }
                else if (tracker.PreviousSquare.Y - 1 == tracker.CurrentSquare.Y)
                {
                    currentSquareTravel = SquareState.TravelNW;
                }
                else if (tracker.PreviousSquare.Y + 1 == tracker.CurrentSquare.Y)
                {
                    currentSquareTravel = SquareState.TravelSW;
                }
            }

            matrix[tracker.CurrentSquare.X, tracker.CurrentSquare.Y] = currentSquareTravel;
        }


        /// <summary>
        /// Draws the path to traverse through every square in the maze.
        /// </summary>
        private static void DrawSolutionPath()
        {
            for (int y = SquareSize - 1; y >= 0; y--)
            //for (int y = 0; y < SquareSize - 1; y++)
            {
                for (int x = 0; x < SquareSize; x++)
                {
                    switch (matrix[x, y])
                    {
                        case SquareState.Empty:
                            // Shouldn't be any empty squares but useful for debugging
                            Console.Write(".");
                            sw.Write(".");
                            break;

                        case SquareState.StartFinish:
                            Console.Write("S");
                            sw.Write("S");
                            break;

                        case SquareState.Obstacle:
                            Console.Write("@");
                            sw.Write("@");
                            break;

                        default:
                            // It's a square along the path
                            switch (matrix[x, y])
                            {
                                case SquareState.TravelNE:
                                    Console.Write("└");
                                    sw.Write("└");
                                    break;
                                case SquareState.TravelNS:
                                    Console.Write("|");
                                    sw.Write("|");
                                    break;
                                case SquareState.TravelNW:
                                    Console.Write("┘");
                                    sw.Write("┘");
                                    break;
                                case SquareState.TravelSE:
                                    Console.Write("┌");
                                    sw.Write("┌");
                                    break;
                                case SquareState.TravelSW:
                                    Console.Write("┐");
                                    sw.Write("┐");
                                    break;
                                case SquareState.TravelWE:
                                    Console.Write("─");
                                    sw.Write("─");
                                    break;
                            }
                            break;
                    }
                    Console.Write(" ");
                    sw.Write(" ");
                }
                Console.WriteLine();
                sw.WriteLine();
            }
            Console.WriteLine();
            sw.WriteLine();
            sw.Flush();
        }
    }
}
