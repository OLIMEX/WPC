#include <stdio.h>
#include <stdlib.h>

/* Initialize sudoku array */
int Sudoku[9][9]=
{
    {2,0,0,0,6,0,4,0,8},
    {3,0,9,0,0,8,0,0,0},
    {0,1,0,0,5,7,0,0,0},
    {5,0,0,2,0,0,0,7,0},
    {0,4,0,0,0,0,8,0,0},
    {0,0,3,0,0,9,0,0,1},
    {0,0,0,8,1,0,0,3,0},
    {1,0,0,6,0,0,5,0,2},
    {0,0,4,7,0,0,0,1,6}
};

/* Output Sudoku all 81 elements */
void OutputSudoku()
{
     int i, j;
     putchar('\n');
     for(i=0; i<9; i++)
     {
        for(j=0; j<9; j++)
            printf("%d ", Sudoku[i][j]);
        putchar('\n');
     }
}

/* Check row */
int CheckRow(int row, int column, int value)
{
    int i=9;
    while(i--)
        if((Sudoku[row][i]==value) && (column!=i))
            return 0;
    return 1;
}

/* Check column */
int CheckColumn(int row, int column, int value)
{
    int i=9;
    while(i--)
        if((Sudoku[i][column]==value) && (row!=i))
            return 0;
    return 1;
}

/* Check 3*3 small sudoku */
int Check3x3SmallSudoku(int row, int column, int value)
{
    int i, j, a, b;
    i=(row/3)*3;
    j=(column/3)*3;
    for(a=i; a<i+3; a++)
        for(b=j; b<j+3; b++)
            if((Sudoku[a][b]==value) && !(row==a && column==b))
                return 0;
    return 1;
}

/* Check whether value is suitable for the current position*/
int Check(int i, int j, int value)
{
    return CheckRow(i, j, value) && CheckColumn(i, j, value) && Check3x3SmallSudoku(i, j, value);
}

/* Check if all 81 numbers have been filled. */
int FullFill()
{
    int i, j;
    for(i=0; i<9; i++)
        for(j=0; j<9; j++)
            if(!Check(i, j, Sudoku[i][j]) || (Sudoku[i][j]==0))
                return 0;
    return 1;
}

/* Try all possibilities of each position to solve the problem */

void Solver()
{
    int i, j, k;
    if(FullFill())
    {
        OutputSudoku();
        return;
    }
    for(i=0; i<9; i++)
    {
        for(j=0; j<9; j++)
        {
            if(Sudoku[i][j]==0)
            {
                for(k=1; k<10; k++)
                {
                    if(Check(i, j, k))
                    {
                        Sudoku[i][j]=k;
                        Solver();
                    }
                }
                if(k==10)
                {
                    Sudoku[i][j]=0;
                    return;
                }
            }
        }
    }
}

int main()
{
    Solver();
    system("pause");
    return 0;
}
