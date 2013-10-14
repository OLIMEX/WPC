/*
 * Olimex WPC #28
 *
 * Solve a Sudoku puzzle
 *
 * Finds a single solution by recursive depth-first search
 *
 */

#include <stdio.h>
#include <stdlib.h>

#undef basictest

int board[9][9];

int rows[9][10];
int cols[9][10];
int boxs[9][10];

void get_input()
{
    int row, col;
    char* line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    int row_ok = 0;

    printf("Enter 9 rows consisting of 9 characters.\n");
    printf("Every character must either be a digit in the range 1 to 9\n");
    printf("or a space (or period) to represent an empty cell\n\n");

    // Read the 9 rows of input
    for(row=0; row<9; row++)
    {
        read = 0;
        while ((read != 10) || (!row_ok))
        {
            row_ok = 1;
            printf("Row %d:", row+1);
            read = getline(&line, &len, stdin);
            if (read != 10)
            {
                printf("Error: enter exactly 9 digits or blanks\n");
                row_ok = 0;
            }
            else
            {
                // Copy the actual data to a temporary copy
                int tboard[9][9];
                int trows[9][10];
                int tcols[9][10];
                int tboxs[9][10];

                int i,j;
                for(i=0; i<9; i++)
                {
                    for(j=0; j<10; j++)
                    {
                        trows[i][j] = rows[i][j];
                        tcols[i][j] = cols[i][j];
                        tboxs[i][j] = boxs[i][j];
                    }
                    for(j=0; j<9; j++)
                        tboard[i][j] = board[i][j];
                }

                // Verify the 9 entered digits
                for(col=0; col<9; col++)
                {
                    if (line[col] != ' ' && line[col] != '.')
                    {
                        if(line[col]<'1'||line[col] >'9')
                        {
                            printf("Illegal character in input\n");
                            row_ok = 0;
                            break;
                        }
                        else
                        {
                            int box = ((int)(row/3))*3+((int)(col/3));
                            int digit = line[col] - '0';

                            if (trows[row][digit] == 0)
                            {
                                trows[row][digit] = 1;
                            }
                            else
                            {
                                printf("Two identical digits in row %d\n", row+1);
                                row_ok = 0;
                                break;
                            }

                            if (tcols[col][digit] == 0)
                            {
                                tcols[col][digit] = 1;
                            }
                            else
                            {
                                printf("Two identical digits in column %d\n", col+1);
                                row_ok = 0;
                                break;
                            }

                            if (tboxs[box][digit] == 0)
                            {
                                tboxs[box][digit] = 1;
                                tboard[row][col] = digit;
                            }
                            else
                            {
                                printf("Two identical digits in box %d\n", box+1);
                                row_ok = 0;
                                break;
                            }
                        }
                    }
                }

                // If the row is ok, then copy the temporary copy to the actual one
                if (row_ok)
                {
                    for(i=0; i<9; i++)
                    {
                        for(j=0; j<10; j++)
                        {
                            rows[i][j] = trows[i][j];
                            cols[i][j] = tcols[i][j];
                            boxs[i][j] = tboxs[i][j];
                        }
                        for(j=0; j<9; j++)
                            board[i][j] = tboard[i][j];
                    }
                }
            }
        }
    }
    free(line);
}

void print_problem()
{
    printf("\nFinding a solution for:\n");
    int row, col;
    for(row=0; row<9; row++)
    {
        for(col=0; col<9; col++)
            printf("%c ", board[row][col] + ((board[row][col] == 0) ? 46 : 48));
        printf("\n");
    }
    printf("\n");
}

void print_solution()
{
    printf("Solution found:\n");
    int row, col;
    for(row=0; row<9; row++)
    {
        for(col=0; col<9; col++)
            printf("%d ", board[row][col]);
        printf("\n");
    }
    printf("\n");
}

// Try to fit a digit into the next location
int next_one(int arow, int acol)
{
    int try_row, try_col, try_box, status;

    //determine next row and col to be tested
    if (acol >= 8)
    {
        try_row = arow + 1;
        try_col = 0;
    }
    else
    {
        try_row = arow;
        try_col = acol + 1;
    }

    //if the board has been filled then return ok
    if (try_row >= 9)
        return 1;

    //if board has already filled in this specific location
    if(board[try_row][try_col] != 0)
    {
        //then try the next location
        return next_one(try_row, try_col);
    }
    else
    {
        //try the 9 digits
        try_box = ((int)(try_row/3))*3+((int)(try_col/3));
        int digit;
        for(digit=1; digit<=9; digit++)
        {
            //if a digit fits
            if((rows[try_row][digit]==0) &&
                    (cols[try_col][digit]==0) &&
                    (boxs[try_box][digit]==0))
            {
                // then record it
                rows[try_row][digit]=1;
                cols[try_col][digit]=1;
                boxs[try_box][digit]=1;
                board[try_row][try_col]=digit;
                // and try continuing
                status = next_one(try_row, try_col);
                // if continuing was ok then return reporting success
                if (status)
                    return status;
                else
                {
                    // else undo this step and try the next digit
                    rows[try_row][digit]=0;
                    cols[try_col][digit]=0;
                    boxs[try_box][digit]=0;
                    board[try_row][try_col]=0;
                }
            }
        }
        // at this point, all digits have been tried without succes, so return failure
        return 0;
    }
}

// Start the recursive search
void solve()
{
    if (!next_one(0,-1))
        printf("No solution found\n");
    else
        print_solution();
}

#ifdef basictest

int test_board[9][9] =
{
    {5,3,0,0,7,0,0,0,0},
    {6,0,0,1,9,5,0,0,0},
    {0,9,8,0,0,0,0,6,0},
    {8,0,0,0,6,0,0,0,3},
    {4,0,0,8,0,3,0,0,1},
    {7,0,0,0,2,0,0,0,6},
    {0,6,0,0,0,0,2,8,0},
    {0,0,0,4,1,9,0,0,5},
    {0,0,0,0,8,0,0,7,9}
};

int test_solution[9][9] =
{
    {5,3,4,6,7,8,9,1,2},
    {6,7,2,1,9,5,3,4,8},
    {1,9,8,3,4,2,5,6,7},
    {8,5,9,7,6,1,4,2,3},
    {4,2,6,8,5,3,7,9,1},
    {7,1,3,9,2,4,8,5,6},
    {9,6,1,5,3,7,2,8,4},
    {2,8,7,4,1,9,6,3,5},
    {3,4,5,2,8,6,1,7,9}
};

void test_input()
{
    int row, col, digit, box;
    for(row=0; row<9; row++)
    {
        for(col=0; col<9; col++)
        {
            board[row][col] = test_board[row][col];
            if(board[row][col])
            {
                digit = board[row][col];
                rows[row][digit]= 1;
                cols[col][digit]= 1;
                box=((int)(row/3))*3+((int)(col/3));
                boxs[box][digit]= 1;
            }
        }
    }
}

void test()
{
    int row, col;
    test_input();
    print_problem();
    solve();
    for(row=0; row<9; row++)
    {
        for(col=0; col<9; col++)
        {
            if (test_solution[row][col] != board[row][col])
            {
                printf("Test failed\n");
                return;
            }
        }
    }
    printf("Test OK\n");
}
#endif

int main()
{
#ifdef basictest
    test();
#else
    get_input();
    print_problem();
    solve();
#endif
    return 0;
}
