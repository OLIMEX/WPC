This entry is written in C#.

- Program.cs is a console application that allows the user to choose the input maze file.
- Maze.cs holds the main analyzing logic.

The logic goes through a few steps:

1.  It parses the input file and creates a 2-dimensional array of integers where there's an obstacle.  The logic's not that smart at this stage so a contiguous block of obstacles may be represented by several numbers.

2.  The obstacle numbers in the array are consolidated so the each contiguous block of obstacles is represented by one unique number.

3.  The array is scanned to count up the number of obstacles in each contiguous block.  The maximum is returned back to the console app to be reported.

The console app also displays the resulting array to provide optical verification that it's done its job right.

Enjoy!

Nigel