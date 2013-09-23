using System;
using System.Collections.Generic;
using System.IO;

namespace WPC25_EqualTravelPaths
{
    class Program
    {
        /// <summary>
        /// Problem:
        /// If we have matrix with size M x N and two points A(xa,ya) and B(xb,yb), 
        /// C obstacles which are entered with their coordinates and and length of path L
        /// 
        /// Make code which:
        /// 
        /// inputs the matrix size M and N
        /// inputs the point A(x,y) coordinates
        /// inputs the point B(x,y) coordinates
        /// inputs the number of Obstracles C
        /// inputs the obstracles C(x,y) coordinates
        /// inputs the path length
        /// 
        /// Then displays all variants (if any) one can move from point A to point B by 
        /// traveling via L cells. You can step on one cell just once and only if the 
        /// cell have no obstracle.
        /// 
        /// The valid moves are only up-down-left-right
        /// 
        /// For example:
        /// 9 . . . . . . . . . .
        /// 8 . . . . . . . . . .
        /// 7 . . . . . . . . . .
        /// 6 . . . . . . . . . .
        /// 5 . . . . . . B . . .
        /// 4 . . C . . . . C . .
        /// 3 . . . C . . . . . .
        /// 2 . . . . C . . . . .
        /// 1 . A . . . C . . . .
        /// 0 . . . . . . . . . .
        ///   0 1 2 3 4 5 6 7 8 9 
        /// </summary>
        private static CellIs[,] matrix;
        private static int solutionsFound = 0;                      // Keeps track of how many different paths we find
        private static int matrixWidth = 0;                         // The number of cells along the X axis
        private static int matrixHeight = 0;                        // The number of cells along the Y axis
        private static int startX, startY = 0;                      // The coordinates of the starting point A
        private static int finishX, finishY = 0;                    // The cordinates of the finish point B
        private static int noOfObstacles = 0;                       // The number of obstacle cells C in the matrix
        private static List<Point> obstacles = new List<Point>();   // The coordinates of each obstacle in the matrix
        private static int pathLength = 0;                          // The length of path to find
        private static Point startPoint;                            // Starting point A
        private static Point finishPoint;                           // Finishing point B
        private static StreamWriter sw;                             // To write paths found to a log file
        private static string message;                              // General string

        static void Main(string[] args)
        {
            // Get the input values from the user.
            GetInputParameters();

            // Setup the matrix of squares, indicating the start, finish and obstacle cells.
            matrix = new CellIs[matrixWidth, matrixHeight];
            matrix[startPoint.X, startPoint.Y] = CellIs.StartPoint;
            matrix[finishPoint.X, finishPoint.Y] = CellIs.FinishPoint;
            foreach (Point o in obstacles)
            {
                matrix[o.X, o.Y] = CellIs.Obstacle;
            }

            // Keep track of how many paths we find.
            solutionsFound = 0;

            // Open a log file so we can write out the paths we find.
            string logFile = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "WPC25-PathsFound.txt");
            sw = new StreamWriter(logFile);
            WriteLogFileHeader();

            DrawMatrix();
            Console.WriteLine("Press any key to proceed...");
            Console.ReadLine();

            // We use an object to keep track of values as we recurse back and forth along test paths.
            // This is the initial object containing the starting point A.
            Cell startingCell = new Cell();
            startingCell.CurrentCell = startPoint;
            startingCell.PreviousCell = new Point(-1, -1);
            startingCell.MoveCount = 0;

            message = "Valid paths are shown below";
            Console.WriteLine(message);
            sw.WriteLine(message);

            // Start recursing...
            CheckCell(startingCell);
            
            // Write messages to user an log.
            message = string.Format("Success!!  Number of paths found = {0}", solutionsFound);
            Console.WriteLine(message);
            sw.WriteLine();
            sw.WriteLine(message);
            sw.Close();

            // Wait for user to close the console.
            Console.ReadLine();
        }

        /// <summary>
        /// Gets the user's parameters for the problem.
        /// </summary>
        private static void GetInputParameters()
        {
            Console.Write("Enter the width of the matrix                  default 10    : ");
            string sWidth = Console.ReadLine();
            if (!int.TryParse(sWidth, out matrixWidth)) matrixWidth = 10;

            Console.Write("Enter the height of the matrix                 default 10    : ");
            string sHeight = Console.ReadLine();
            if (!int.TryParse(sHeight, out matrixHeight)) matrixHeight = 10;

            Console.Write("Enter the start co-ordinates (point A) (x,y)   default (1,1) : ");
            string sStart = Console.ReadLine();
            if (string.IsNullOrEmpty(sStart.Trim()))
            {
                startX = 1;
                startY = 1;
            }
            else
            {
                string[] startCoords = sStart.Split(',');
                if (!int.TryParse(startCoords[0], out startX)) startX = 1;
                if (!int.TryParse(startCoords[1], out startY)) startY = 1;
            }
            startPoint = new Point(startX, startY);

            Console.Write("Enter the finish co-ordinates (point B) (x,y)  default (6,5) : ");
            string sFinish = Console.ReadLine();
            if (string.IsNullOrEmpty(sFinish.Trim()))
            {
                finishX = 6;
                finishY = 5;
            }
            else
            {
                string[] finishCoords = sFinish.Split(',');
                if (!int.TryParse(finishCoords[0], out finishX)) finishX = 6;
                if (!int.TryParse(finishCoords[1], out finishY)) finishY = 4;
            }
            finishPoint = new Point(finishX, finishY);

            Console.Write("Enter the number of obstacles                  default 0     : ");
            string sObstacles = Console.ReadLine();
            if (!int.TryParse(sObstacles, out noOfObstacles)) noOfObstacles = 0;

            int obstacleX = 0;
            int obstacleY = 0;
            for (int i = 0; i < noOfObstacles; i++)
            {
                Console.Write("Enter the co-ordinates for an obstacle (point C) (x,y)  : ");
                string sObstacle = Console.ReadLine();
                string[] obstacleCoords = sObstacle.Split(',');
                if (!int.TryParse(obstacleCoords[0], out obstacleX)) obstacleX = 0;
                if (!int.TryParse(obstacleCoords[1], out obstacleY)) obstacleY = 0;
                obstacles.Add(new Point(obstacleX, obstacleY));
            }

            Console.Write("Enter the path length                    default 9     : ");
            string sPathLength = Console.ReadLine();
            if (!int.TryParse(sPathLength, out pathLength)) pathLength = 9;
        }

        /// <summary>
        /// Writes a header message to the log file.
        /// </summary>
        private static void WriteLogFileHeader()
        {
            sw.WriteLine("Olimex Weekend Programming Challenge 25 - 21 Sept 2013");
            sw.WriteLine("------------------------------------------------------");
            sw.WriteLine("Path length to be found = {0}", pathLength);
            sw.WriteLine();
        }

        /// <summary>
        /// The interesting bit that checks whether a cell is suitable for a candidate path.
        /// </summary>
        /// <param name="tracker">An object that keeps track of key variables for a cell 
        /// along a candidate path.  It allows us to use recursion to go forwards and 
        /// backwards along the path.</param>
        /// <returns>True if we reached the target (finish) cell; false otherwise.</returns>
        private static bool CheckCell(Cell tracker)
        {
            Cell clone;

#if SHOWPATHSCHECKED
            DrawMatrix();
#endif

            // Check if we've reached the finish point
            if (tracker.CurrentCell == finishPoint)
            {
                // We've reached the finish cell so check whether the path consists of the required
                // number of cells.
                if (tracker.MoveCount == pathLength)
                {
                    // It's a real McCoy.
                    solutionsFound++;
                    DrawMatrix();
                }
                return true;
            }

            if (tracker.MoveCount >= pathLength)
            {
                // Reset the current cell to an empty one
                matrix[tracker.CurrentCell.X, tracker.CurrentCell.Y] = CellIs.Empty;
#if SHOWPATHSCHECKED
                DrawMatrix();
#endif
                return false;
            }

            // Get the state of the cells adjoining the current one
            CellIs cellAboveState = GetAdjoiningCellState(Direction.UP, tracker);
            CellIs cellRightState = GetAdjoiningCellState(Direction.RIGHT, tracker);
            CellIs cellBelowState = GetAdjoiningCellState(Direction.DOWN, tracker);
            CellIs cellLeftState = GetAdjoiningCellState(Direction.LEFT, tracker);

            // If it's ok to move up, do so
            if (cellAboveState == CellIs.Empty || cellAboveState == CellIs.FinishPoint)
            {
                // Mark the cell as on the path
                if (cellAboveState == CellIs.Empty)
                    matrix[tracker.CurrentCell.X, tracker.CurrentCell.Y + 1] = CellIs.PathCell;

                clone = new Cell(tracker);
                // Bump the counter that keeps track of how many cells are along the path.
                if (++clone.MoveCount > pathLength) return false;

                // As we're moving, set the previous cell to the current one.
                clone.PreviousCell.X = clone.CurrentCell.X;
                clone.PreviousCell.Y = clone.CurrentCell.Y;

                // And then move to the cell above
                clone.CurrentCell.Y++;

                // And check that.
                if (CheckCell(clone))
                {
                    // Reset the current cell
                    matrix[tracker.CurrentCell.X, tracker.CurrentCell.Y] = CellIs.Empty;
#if SHOWPATHSCHECKED
                    // Draw the matrix for checking purposes if we're in debug mode
                    DrawMatrix();
#endif
                    return false;
                }
            }

            // If it's OK to move right, do so
            if (cellRightState == CellIs.Empty || cellRightState == CellIs.FinishPoint)
            {
                // Mark the cell as on the path
                if (cellRightState == CellIs.Empty)
                    matrix[tracker.CurrentCell.X + 1, tracker.CurrentCell.Y] = CellIs.PathCell;

                clone = new Cell(tracker);
                // Bump the counter that keeps track of how many cells are along the path.
                if (++clone.MoveCount > pathLength) return false;

                // As we're moving, set the previous cell to the current one.
                clone.PreviousCell.X = clone.CurrentCell.X;
                clone.PreviousCell.Y = clone.CurrentCell.Y;

                // And then move to the cell to the right
                clone.CurrentCell.X++;

                // And check that.
                if (CheckCell(clone))
                {
                    // Reset the current cell
                    matrix[tracker.CurrentCell.X, tracker.CurrentCell.Y] = CellIs.Empty;
#if SHOWPATHSCHECKED
                    // Draw the matrix for checking purposes if we're in debug mode
                    DrawMatrix();
#endif
                    return false;
                }
            }

            // If it's ok to move down, do so
            if (cellBelowState == CellIs.Empty || cellBelowState == CellIs.FinishPoint)
            {
                // Mark the cell as on the path
                if (cellBelowState == CellIs.Empty)
                    matrix[tracker.CurrentCell.X, tracker.CurrentCell.Y - 1] = CellIs.PathCell;

                clone = new Cell(tracker);
                // Bump the counter that keeps track of how many cells are along the path.
                if (++clone.MoveCount > pathLength) return false;

                // As we're moving, set the previous cell to the current one.
                clone.PreviousCell.X = clone.CurrentCell.X;
                clone.PreviousCell.Y = clone.CurrentCell.Y;

                // And then move to the cell below
                clone.CurrentCell.Y--;

                // And check that.
                if (CheckCell(clone))
                {
                    // Reset the current cell
                    matrix[tracker.CurrentCell.X, tracker.CurrentCell.Y] = CellIs.Empty;
#if SHOWPATHSCHECKED
                    // Draw the matrix for checking purposes if we're in debug mode
                    DrawMatrix();
#endif
                    return false;
                }
            }

            // If it's OK to move left, do so
            if (cellLeftState == CellIs.Empty || cellLeftState == CellIs.FinishPoint)
            {
                // Mark the cell as on the path
                if (cellLeftState == CellIs.Empty)
                    matrix[tracker.CurrentCell.X - 1, tracker.CurrentCell.Y] = CellIs.PathCell;

                clone = new Cell(tracker);
                // Bump the counter that keeps track of how many cells are along the path.
                if (++clone.MoveCount > pathLength) return false;

                // As we're moving, set the previous cell to the current one.
                clone.PreviousCell.X = clone.CurrentCell.X;
                clone.PreviousCell.Y = clone.CurrentCell.Y;

                // And then move to the cell to the left
                clone.CurrentCell.X--;

                // And check that.
                if (CheckCell(clone))
                {
                    // Reset the current cell
                    matrix[tracker.CurrentCell.X, tracker.CurrentCell.Y] = CellIs.Empty;
#if SHOWPATHSCHECKED
                    // Draw the matrix for checking purposes if we're in debug mode
                    DrawMatrix();
#endif
                    return false;
                }
            }

            // Reset the current cell to an empty one
            if (matrix[tracker.CurrentCell.X, tracker.CurrentCell.Y] != CellIs.StartPoint)
                matrix[tracker.CurrentCell.X, tracker.CurrentCell.Y] = CellIs.Empty;
#if SHOWPATHSCHECKED
            // Draw the matrix for checking purposes if we're in debug mode
            DrawMatrix();
#endif
            return false;
        }

        /// <summary>
        /// Gets the state of a cell adjacent to the specified one.
        /// </summary>
        /// <param name="direction">The direction to look in (left, right, up or down)</param>
        /// <param name="cell">The reference cell.</param>
        /// <returns>Whether the cell is empty, the start or finish point, an obstacle or 
        /// one that's on the current path</returns>
        private static CellIs GetAdjoiningCellState(Direction direction, Cell cell)
        {
            int xOffset = 0;
            int yOffset = 0;

            if (direction == Direction.UP && cell.CurrentCell.Y + 1 < matrix.GetLength(1))
                yOffset = 1;

            else if (direction == Direction.DOWN && cell.CurrentCell.Y - 1 >= 0)
                yOffset = -1;
            else if (direction == Direction.RIGHT && cell.CurrentCell.X + 1 < matrix.GetLength(0))
                xOffset = 1;
            else if (direction == Direction.LEFT && cell.CurrentCell.X - 1 >= 0)
                xOffset = -1;
            else
                return CellIs.InvalidCell;

            return matrix[cell.CurrentCell.X + xOffset, cell.CurrentCell.Y + yOffset];
        }

        /// <summary>
        /// Draws the matrix to show the path found.  It also writes it out to the log file.
        /// </summary>
        private static void DrawMatrix()
        {
            int xMax = matrix.GetLength(0);
            int yMax = matrix.GetLength(1);
            for (int y = yMax - 1; y >= 0; y--)
            {
                for (int x = 0; x < xMax; x++)
                {
                    switch (matrix[x, y])
                    {
                        case CellIs.Empty :
                            Console.Write(".");
                            sw.Write(".");
                            break;
                        case CellIs.StartPoint :
                            Console.Write("A");
                            sw.Write("A");
                            break;
                        case CellIs.FinishPoint:
                            Console.Write("B");
                            sw.Write("B");
                            break;
                        case CellIs.Obstacle:
                            Console.Write("C");
                            sw.Write("C");
                            break;
                        case CellIs.PathCell:
                            Console.Write("*");
                            sw.Write("*");
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
        }
    }
}
