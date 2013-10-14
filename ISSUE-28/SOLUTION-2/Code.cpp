#include <iostream>
#include <windows.h>
using namespace std;

void setcolor(unsigned short color)
    {
        HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hcon,color);
    }

int board[9][9];
int change[9][9];

void StartGame()
	{
		for(int i = 1; i <= 9; i++)
			for(int j = 1; j <= 9; j++)
				{
					board[i][j] = 0;
					change[i][j] = 0;
				}
	}

//There must be a better way to check for conflicts
bool Check_Conflicts(int p, int i, int j)
      {
        for(int k = 1; k <= 9; k++)
          if(board[i][k] == p) return false;
          
        for(int q = 1; q <= 9; q++)
          if(board[q][j] == p) return false;
        
        /*
          *00
          000
          000
        */
        if((j == 1 || j == 4 || j == 7) && (i == 1 || i == 4 || i == 7))
          {
             if(board[i][j+1] == p || board[i][j+2] == p || board[i+1][j] == p || 
                 board[i+2][j] == p || board[i+1][j+1] == p || board[i+1][j+2] == p || 
                     board[i+2][j+1] == p || board[i+2][j+2] == p)return false;     
          } 
         
        /*
          000
          *00
          000
        */            
        if((j == 1 || j == 4 || j == 7) && (i == 2 || i == 5 || i == 8))
          {
             if(board[i-1][j] == p || board[i-1][j+1] == p || board[i-1][j+2] == p || 
                 board[i][j+1] == p || board[i][j+2] == p || board[i+1][j] == p || 
                     board[i+1][j+1] == p || board[i+1][j+2] == p)return false;  
          } 
          
		/*
          000
          000
          *00
        */  
        if((j == 1 || j == 4 || j == 7) && (i == 3 || i == 6 || i == 9))
          {
             if(board[i-1][j] == p || board[i-2][j] == p || board[i][j+1] == p || 
                 board[i][j+2] == p || board[i-1][j+1] == p || board[i-1][j+2] == p || 
                     board[i-2][j+1] == p || board[i-2][j+2] == p)return false;   
          }
        
        /*
          0*0
          000
          000
        */            
        if((j == 2 || j == 5 || j == 8) && (i == 1 || i == 4 || i == 7))
          {
             if(board[i][j-1] == p || board[i][j+1] == p || board[i+1][j+1] == p || 
                 board[i+1][j-1] == p || board[i+1][j] == p || board[i+2][j-1] == p || 
                     board[i+2][j] == p || board[i+2][j+1] == p)return false;  
          }
          
        /*
          000
          0*0
          000
        */            
        if((j == 2 || j == 5 || j == 8) && (i == 2 || i == 5 || i == 8))
          {
             if(board[i-1][j] == p || board[i-1][j-1] == p || board[i-1][j+1] == p || 
                 board[i][j+1] == p || board[i][j-1] == p || board[i+1][j+1] == p || 
                     board[i+1][j] == p || board[i+1][j-1] == p)return false;  
          }
          
        
        /*
          000
          000
          0*0
        */            
        if((j == 2 || j == 5 || j == 8) && (i == 3 || i == 6 || i == 9))
          {
             if(board[i][j-1] == p || board[i][j+1] == p || board[i-1][j] == p || 
                 board[i-1][j+1] == p || board[i-1][j-1] == p || board[i-2][j] == p || 
                     board[i-2][j+1] == p || board[i-2][j-1] == p) return false;  
          }  
          
        /*
          00*
          000
          000
        */            
        if((j == 3 || j == 6 || j == 9) && (i == 1 || i == 4 || i == 7))
          {
             if(board[i][j-1] == p || board[i][j-2] == p || board[i+1][j] == p || 
                 board[i+1][j-1] == p || board[i+1][j-2] == p || board[i+2][j] == p || 
                     board[i+2][j-1] == p || board[i+2][j-2] == p) return false;  
          } 
          
        /*
          000
          00*
          000
        */            
        if((j == 3 || j == 6 || j == 9) && (i == 2 || i == 5 || i == 8))
          {
             if(board[i-1][j] == p || board[i-1][j-1] == p || board[i-1][j-2] == p || 
                 board[i][j-1] == p || board[i][j-2] == p || board[i+1][j] == p || 
                     board[i+1][j-1] == p || board[i+1][j-2] == p) return false;  
          }
          
        /*
          000
          000
          00*
        */            
        if((j == 3 || j == 6 || j == 9) && (i == 3 || i == 6 || i == 9))
          {
             if(board[i][j-1] == p || board[i][j-2] == p || board[i-1][j] == p || 
                 board[i-1][j-1] == p || board[i-1][j-2] == p || board[i-2][j] == p || 
                     board[i-2][j-1] == p || board[i-2][j-2] == p) return false;  
          }      
     
        return true;                          
      }

bool Solve(int row, int col)
	{
		while(change[row][col] == 1) //Check if we can change the value of the cell
			{
				col++;
				if(col > 9) 
					{
						col = 0;
						row++;
					}
				if(row > 9) return true;
			}
		int NextRow, NextCol;
		for(int i = 1; i < 10; i++)
			{
				if(Check_Conflicts(i, row, col)) //Check for conflicts
					{
						board[row][col] = i;
						NextRow = row;
						NextCol = col+1;
						if(NextCol > 9)
							{
								NextCol = 1;
								NextRow = row+1;
							}
						if(NextRow == 10) return true; //If we have reached the end of the board return true
						if(Solve(NextRow, NextCol)) return true; //Find value for the next cell
					}
			}
		board[row][col] = 0; //If we are at this point of the program that means that we 
							//haven't found a suitable value for this cell and we need to go back
		return false;
	}

//Print the board
void PrintBoard()
	{
		for(int i = 1; i <= 9; i++)
			{
				for(int j = 1; j <= 9; j++)
					{
						if(change[i][j] == 1) setcolor(12);
						cout << board[i][j] << " ";
						setcolor(7);
						if(j%3 == 0 && j != 9) cout << "| ";
					}
				cout << endl;
				if(i%3 == 0 && i != 9) cout << "------+-------+------" << endl;
			}
		cout << endl;
	}

//Input the start values
void Input()
	{
		PrintBoard();
		cout << "How many values do you want to enter?: ";
		int num;
		cin >> num;
		for(int i = 0; i < num; i++)
			{
				int row, col, number;
				cout << "Row (1-9): ";
				cin >> row;
				cout << "Col (1-9): ";
				cin >> col;
				cout << "Number: ";
				cin >> number;
				if((row > 0 && row < 10) && (col > 0 && col < 10))
					{
						change[row][col] = 1;
						board[row][col] = number;
					}
				else 
					{
						cout << "Wrong input! Try again!" << endl;
						i--;
						Sleep(1000);
					}
				system("CLS");
				PrintBoard();
			}
		system("CLS");
	}

int main()
	{
		StartGame();
		Input();
		Solve(1, 1);
		PrintBoard();
		system("pause");
		return 0;
	}