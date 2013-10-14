using System;
using System.Collections.Generic;
using System.Linq;

namespace WPC28_Sudoku
{
    /// <summary>
    /// WPC 28 - Sudoku puzzle solver
    /// </summary>
    class Program
    {
        private static int[,] initialState;
        private static int[,] solution;
        private static List<int>[,] possibles;

        static void Main(string[] args)
        {
            // Populate initial state.
            // Uncomment one of these lines to test that particular puzzle.
            initialState = InitializeEasyPuzzle();        // solved
            //initialState = InitializeHardPuzzle();        // solved
            //initialState = InitializeHarderPuzzle();      // unsolved
            //initialState = InitializeMildPuzzle();        // unsolved
            //initialState = InitializeEasy2Puzzle();       // solved

            Draw("Initial State", initialState);

            // Copy the initial state into the solution
            solution = CopyState(initialState);

            bool solutionHasBeenUpdated = false;
            do
            {
                // Populate possible numbers for all empty squares in the solution
                possibles = PopulatePossibilities(solution);

                // If there are any squares that have only 1 possibility, that's the
                // solution for that square.
                solutionHasBeenUpdated = UpdateSolutionWithDefinites();

#if SHOW_INTERIM_SOLUTIONS
                // Draw the solutions
                Draw("Interim Solution", solution);
#endif
                // If there are no more possibles, we're done
                if (NoMorePossibles()) break;
            }
            while (solutionHasBeenUpdated) ;

            // Check whether we're done
            int iteration = 0;
            if (!GotTotalSolution())
            {
                iteration = 0;
                do
                {
                    ShowPossibles();

                    // There's still some squares to populate with a number.
                    // Look through each row, column and square to see if any
                    // have 2 squares with the same 2 possible digits.  If we have,
                    // we can remove those possibles from the other squares.  This
                    // might leave a square with just one possible digit which can
                    // then be populated.
                    bool anyEliminated = EliminatePossibles();
                    ShowPossibles();
                    solutionHasBeenUpdated = UpdateSolutionWithDefinites();

                    if (solutionHasBeenUpdated) iteration = 0;
                    else iteration++;

#if SHOW_INTERIM_SOLUTIONS
                    Draw("Interim Solution", solution);
#endif
                }
                while (solutionHasBeenUpdated || iteration < 2);
            }

            // Draw the solution
            Draw("Solution", solution);

            Console.WriteLine("Press a key to exit...");
            Console.Read();
        }



        /// <summary>
        /// Checks whether we have a number in each square in the solution.
        /// If we have, we're done.
        /// </summary>
        /// <returns></returns>
        private static bool GotTotalSolution()
        {
            for (int x = 0; x < 9; x++)
            {
                for (int y = 0; y < 9; y++)
                {
                    if (solution[y, x] == 0) return false;
                }
            }
            return true;
        }

        /// <summary>
        /// Rationalise the list of possible numbers for each square by seeing if we have
        /// 2 squares containing the same pair of numbers.  These can be removed from the
        /// other possible digits for the row, column and 3x3 grid.
        /// </summary>
        /// <returns></returns>
        private static bool EliminatePossibles()
        {
            int x, y;
            string s = string.Empty;
            bool possibilityEliminated = false;

            // Check columns for duplicate 2 digit possibilities
            for (x = 0; x < 9; x++)
            {
                List<string> values = new List<string>();
                bool duplicateFound = false;

                for (y = 0; y < 9; y++)
                {
                    if (possibles[y, x] != null)
                    {
                        s = string.Empty;
                        foreach (int i in possibles[y, x])
                        {
                            s += i.ToString();
                        }

                        if (values.Contains(s))
                        {
                            duplicateFound = true;
                            break;
                        }
                        else
                        {
                            values.Add(s);
                        }
                    }
                }

                // Deal with 2 digit matches for the moment
                if (duplicateFound && s.Length == 2)
                {
                    int[] digits = possibles[y, x].ToArray<int>();

                    for (int yy = 0; yy < 9; yy++)
                    {
                        if (possibles[yy, x] != null)
                        {
                            // Build a string of the possible digits for this square being checked.
                            string s1 = string.Empty;
                            foreach (int i1 in possibles[yy, x])
                            {
                                s1 += i1.ToString();
                            }

                            // Only remove duplicates from the squares that have other possible digits.
                            if (s1 != s)
                            {
                                foreach (int duplicate in digits)
                                {
                                    possibles[yy, x].Remove(duplicate);
                                }
                                possibilityEliminated = true;
                            }
                        }
                    }
                }
            }

            // Check rows for duplicate 2 digit possibilities
            for (y = 0; y < 9; y++)
            {
                List<string> values = new List<string>();
                bool duplicateFound = false;

                for (x = 0; x < 9; x++)
                {
                    if (possibles[y, x] != null)
                    {
                        s = string.Empty;
                        foreach (int i in possibles[y, x])
                        {
                            s += i.ToString();
                        }

                        if (values.Contains(s))
                        {
                            duplicateFound = true;
                            break;
                        }
                        else
                        {
                            values.Add(s);
                        }
                    }
                }

                // Deal with 2 digit matches for the moment
                if (duplicateFound && s.Length == 2)
                {
                    int[] digits = possibles[y, x].ToArray<int>();

                    for (int xx = 0; xx < 9; xx++)
                    {
                        if (possibles[y, xx] != null)
                        {
                            // Build a string of the possible digits for this square being checked.
                            string s1 = string.Empty;
                            foreach (int i1 in possibles[y, xx])
                            {
                                s1 += i1.ToString();
                            }

                            // Only remove duplicates from the squares that have other possible digits.
                            if (s1 != s)
                            {
                                foreach (int duplicate in digits)
                                {
                                    possibles[y, xx].Remove(duplicate);
                                }
                                possibilityEliminated = true;
                            }
                        }
                    }
                }
            }

            // Check the 3x3 square the square being checked is in.
            for (x = 0; x < 9; x+=3)
            {
                for (y = 0; y < 9; y+=3)
                {
                    int x3 = (x / 3) * 3;
                    int y3 = (y / 3) * 3;

                    for (int yy = y3; yy < y3 + 3; yy++)
                    {
                        List<string> values = new List<string>();
                        bool duplicateFound = false;

                        for (int xx = x3; xx < x3 + 3; xx++)
                        {
                            if (possibles[yy, xx] != null)
                            {
                                // Build a string of the possible integers for this square.
                                s = string.Empty;
                                foreach (int i in possibles[yy, xx])
                                {
                                    s += i.ToString();
                                }

                                // Check whether we've already seen this sequence of possible integers
                                if (values.Contains(s))
                                {
                                    duplicateFound = true;
                                    break;
                                }
                                else
                                {
                                    values.Add(s);
                                }
                            }
                        }

                        // Deal with the 2 digit matches
                        if (duplicateFound && s.Length == 2)
                        {
                            int[] digits = possibles[y, x].ToArray<int>();

                            for (int xxx = x3; xxx < x3 + 3; xxx++)
                            {
                                for (int yyy = y3; yyy < y3 + 3; yyy++)
                                {
                                    if (possibles[yyy, xxx] != null)
                                    {
                                        // Build a string of the possible digits for this square being checked.
                                        string s1 = string.Empty;
                                        foreach (int i1 in possibles[yyy, xxx])
                                        {
                                            s1 += i1.ToString();
                                        }

                                        // Only remove duplicates from the squares that have other possible digits.
                                        if (s1 != s)
                                        {
                                            foreach (int duplicate in digits)
                                            {
                                                possibles[yyy, xxx].Remove(duplicate);
                                            }
                                            possibilityEliminated = true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            return possibilityEliminated;
        }

        /// <summary>
        /// Check whether we've finished the solution by seeing if there are any possible
        /// values left.
        /// </summary>
        /// <returns></returns>
        private static bool NoMorePossibles()
        {
            for (int x = 0; x < 9; x++)
            {
                for (int y = 0; y < 9; y++)
                {
                    if (possibles[y, x] != null)
                        return false;
                }
            }
            return true;
        }

        /// <summary>
        /// Update the solution grid where there's only one possible digit.
        /// </summary>
        /// <returns></returns>
        private static bool UpdateSolutionWithDefinites()
        {
            bool solutionUpdated = false;

            for (int x = 0; x < 9; x++)
            {
                for (int y = 0; y < 9; y++)
                {
                    if (possibles[y, x] != null && possibles[y, x].Count == 1)
                    {
                        solution[y, x] = possibles[y, x][0];
                        RemoveDefiniteFromPossibles(x, y, solution[y, x]);
                        solutionUpdated = true;
                    }
                }
            }
            return solutionUpdated;
        }

        /// <summary>
        /// This is called after a square is filled in the solution with a definite
        /// number.  It removes this number from the list of possibles left.
        /// </summary>
        /// <param name="column">The x co-ordinate of the square in the solution that has been filled</param>
        /// <param name="row">The y co-ordinate of the square in the solution that has been filled</param>
        /// <param name="digitAdded">The digit that was added to the solution, i.e. the digit to remove
        /// from the row, column and 3x3 square of possible digits.</param>
        private static void RemoveDefiniteFromPossibles(int column, int row, int digitAdded)
        {
            int x, y;

            // Do the column first.
            for (y = 0; y < 9; y++)
            {
                if (possibles[y, column] != null && possibles[y, column].Contains(digitAdded))
                    possibles[y, column].Remove(digitAdded);
            }

            // Then do the row
            for (x = 0; x < 9; x++)
            {
                if (possibles[row, x] != null && possibles[row, x].Contains(digitAdded))
                    possibles[row, x].Remove(digitAdded);
            }

            // Then do the 3x3 grid that the square is in.
            int x3 = (column / 3) * 3;
            int y3 = (row / 3) * 3;
            for (y = y3; y < y3 + 3; y++)
            {
                for (x = x3; x < x3 + 3; x++)
                {
                    if (possibles[y, x] != null && possibles[y, x].Contains(digitAdded))
                        possibles[y, x].Remove(digitAdded);
                }
            }
        }

        /// <summary>
        /// Scan through the current state array and populate another array with
        /// all possible numbers for each square in the Sudoku grid.  If the square in the
        /// solution already contains a number, the corresponding position in the array
        /// returned by this function will be null.
        /// </summary>
        /// <param name="currentState"></param>
        /// <returns></returns>
        private static List<int>[,] PopulatePossibilities(int[,] currentState)
        {
            List<int>[,] possibilities = new List<int>[9, 9];

            for (int y = 0; y < 9; y++)
            {
                for (int x = 0; x < 9; x++)
                {
                    if (currentState[y, x] == 0)
                    {
                        // The currentState is an empty square.


                        // Go through each value from 1 - 9
                        for (int possibleValue = 1; possibleValue <= 9; possibleValue++)
                        {
                            bool possibleValueAlreadyExists = false;
                            int index;

                            // Scan along the current row to see if this possible value is on it.
                            // If it is, skip to the next possible value
                            for (index = 0; index < 9; index++)
                            {
                                if (currentState[y, index] == possibleValue)
                                {
                                    possibleValueAlreadyExists = true;
                                    break;
                                }
                            }
                            if (possibleValueAlreadyExists) continue;

                            // If it isn't, scan along the current column to see if this possible
                            // value is on it.
                            // If it is, skip to the next possible value
                            for (index = 0; index < 9; index++)
                            {
                                if (currentState[index, x] == possibleValue)
                                {
                                    possibleValueAlreadyExists = true;
                                    break;
                                }
                            }
                            if (possibleValueAlreadyExists) continue;

                            // If it isn't, check the 3x3 square to see if this possible value
                            // is in it.
                            // If it is, skip to the next possible value
                            // If it isn't, it's a possible value so add it to the current square's
                            // list.
                            int x3 = (x / 3) * 3;
                            int y3 = (y / 3) * 3;
                            for (int yy = y3; yy < y3 + 3; yy++)
                            {
                                for (int xx = x3; xx < x3 + 3; xx++)
                                {
                                    if (currentState[yy, xx] == possibleValue)
                                    {
                                        //possibilities[y, x] = null;
                                        possibleValueAlreadyExists = true;
                                        break;
                                    }
                                }
                                if (possibleValueAlreadyExists) break;
                            }
                            if (possibleValueAlreadyExists) continue;

                            // It's a valid possible number for the solution.
                            // Add the possible value to the list for this square
                            if (possibilities[y, x] == null)
                                possibilities[y, x] = new List<int>();
                            possibilities[y, x].Add(possibleValue);
                        }
                    }
                }
            }
            return possibilities;
        }

        /// <summary>
        /// Copy one Sudoku grid to another.
        /// </summary>
        /// <param name="sudokuGrid"></param>
        /// <returns></returns>
        private static int[,] CopyState(int[,] sudokuGrid)
        {
            int[,] clone = new int[9, 9];

            for (int y = 0; y < 9; y++)
            {
                for (int x = 0; x < 9; x++)
                {
                    clone[x, y] = sudokuGrid[x, y];
                }
            }
            return clone;
        }
        
        /// <summary>
        /// Draw the Sudoku grid using the state array passed in.
        /// </summary>
        /// <param name="title">Text that will appear above the displayed grid.</param>
        /// <param name="state">The array of numbers in the Sudoku puzzle.</param>
        private static void Draw(string title, int[,] state)
        {
            Console.WriteLine(title);
            Console.WriteLine();
            for (int x = 0; x < 9; x++)
            {
                if (x % 3 == 0) Console.WriteLine("----------+---------+----------");
                Console.Write("|");
                for (int y = 0; y < 9; y++)
                {
                    if (state[x, y] == 0)
                    {
                        Console.Write(" . ");
                    }
                    else
                    {
                        Console.Write(" {0} ", state[x, y]);
                    }
                    if (y % 3 == 2) Console.Write("|");
                }
                Console.WriteLine();
            }
            Console.WriteLine("----------+---------+----------");
            Console.WriteLine();
        }

        /// <summary>
        /// List the possible values for each square out to the console.
        /// useful for checking whether the algorithm is working OK.
        /// </summary>
        private static void ShowPossibles()
        {
#if SHOW_INTERIM_SOLUTIONS
            Console.WriteLine("Possibles");
            for (int y = 0; y < 9; y++)
            {
                for (int x = 0; x < 9; x++)
                {
                    if (possibles[y, x] != null)
                    {
                        string s = string.Empty;
                        for (int z = 1; z <= 9; z++)
                        {
                            if (possibles[y, x].Contains(z))
                            {
                                s += z.ToString();
                            }
                            else
                            {
                                s += ".";
                            }
                        }
                        s += " ";

                        Console.Write(s);
                    }
                    else
                    {
                        Console.Write("......... ");
                    }
                }
                Console.WriteLine();
            }
            Console.WriteLine();
#endif
        }

        /// <summary>
        /// An easy puzzle to solve
        /// </summary>
        /// <returns></returns>
        private static int[,] InitializeEasyPuzzle()
        {
            int[,] puzzle = new int[,]
            {
                { 4,0,0, 0,0,7, 0,3,5 },
                { 1,5,7, 0,0,9, 0,2,0 },
                { 0,0,0, 6,8,0, 0,1,0 },

                { 8,4,0, 0,1,0, 7,0,0 },
                { 0,0,2, 8,0,6, 3,0,0 },
                { 0,0,6, 0,7,0, 0,9,2 },

                { 0,8,0, 0,9,1, 0,0,0 },
                { 0,9,0, 5,0,0, 2,6,4 },
                { 2,3,0, 7,0,0, 0,0,9 }
            };
            return puzzle;
        }

        /// <summary>
        /// An easy puzzle to solve.
        /// </summary>
        /// <returns></returns>
        private static int[,] InitializeEasy2Puzzle()
        {
            int[,] puzzle = new int[,]
            {
                { 1,0,0,4,0,9,0,0,8 },
                { 0,0,0,0,6,0,0,0,0 },
                { 0,0,9,3,0,8,4,0,0 },
                { 3,0,1,5,0,6,8,0,9 },
                { 5,7,0,0,9,0,0,2,6 },
                { 8,9,0,0,0,0,0,4,5 },
                { 0,0,0,0,0,0,0,0,0 },
                { 0,4,0,0,8,0,0,1,0 },
                { 7,8,5,6,2,1,9,3,4 },
            };
            return puzzle;
        }

        /// <summary>
        /// A hard puzzle to solve.
        /// </summary>
        /// <returns></returns>
        private static int[,] InitializeHardPuzzle()
        {
            int[,] puzzle = new int[,]
            {
                { 0,8,0, 2,5,9, 0,0,0 },
                { 6,0,9, 0,0,0, 8,0,0 },
                { 0,7,0, 4,0,8, 0,9,0 },

                { 9,0,7, 0,2,0, 3,0,6 },
                { 4,0,0, 9,0,6, 0,0,2 },
                { 3,0,6, 0,1,0, 5,0,9 },

                { 0,9,0, 1,0,2, 0,3,0 },
                { 0,0,1, 0,0,0, 2,0,4 },
                { 0,0,0, 7,8,3, 0,5,0 }
            };
            return puzzle;
        }

        /// <summary>
        /// An even harder puzzle to solve.
        /// </summary>
        /// <returns></returns>
        private static int[,] InitializeHarderPuzzle()
        {
            int[,] puzzle = new int[,]
            {
                { 2,0,0,1,3,0,0,0,9 },
                { 0,0,0,0,4,0,0,2,0 },
                { 1,0,0,0,0,8,0,0,0 },
                { 0,1,3,0,2,0,0,0,0 },
                { 8,0,4,0,0,0,1,0,5 },
                { 0,0,0,0,8,0,2,4,0 },
                { 0,0,0,8,0,0,0,0,6 },
                { 0,8,0,0,7,0,0,0,0 },
                { 7,0,0,0,6,3,0,0,4 }
            };
            return puzzle;
        }

        /// <summary>
        /// A medium difficulty puzzle to solve.
        /// </summary>
        /// <returns></returns>
        private static int[,] InitializeMildPuzzle()
        {
            int[,] puzzle = new int[,]
            {
                { 2,0,0,5,0,0,4,0,0 },
                { 0,6,0,4,0,0,0,0,0 },
                { 0,5,0,0,0,0,0,7,8 },
                { 3,0,0,0,0,6,0,0,0 },
                { 5,0,2,0,1,0,7,0,9 },
                { 0,0,0,7,0,0,0,0,3 },
                { 9,1,0,0,0,0,0,2,0 },
                { 0,0,0,0,0,1,0,4,0 },
                { 0,0,6,0,0,2,0,0,7 },
            };
            return puzzle;
        }
    }
}
