/*
  Name: Ways
  Author: Sinan Zikri
  Date: 21.09.13 17:16
*/


#include<iostream>
#include<list>
using namespace std;

struct Point
	{
		int x, y;
	};

int matrix[100][100]; //Matrix
bool used[100][100]; //Store the used cells
list<Point> Path; //List that contains the path

//Solve function also known as Depth-First-Search (DFS)
void Solve(Point start, Point final, int len)
	{
		if(len == 0)
			if(start.x == final.x && start.y == final.y) //Check if we have reached the final point
				{
					//Print list with coords
					list<Point>::iterator Iter = Path.begin();
					for(Iter; Iter != Path.end(); Iter++)
						{
							cout << "(" << Iter->x << ", " << Iter->y << "), ";
						}
					cout << endl;
					return;
				}
			else return;

		Point next;
		//check cell x-1, y;
		next.x = start.x - 1;
		next.y = start.y;
		if(matrix[next.x][next.y] == 1 && !used[next.x][next.y]) //Check if the cell is used and if there is an obstacle
			{
				Path.push_back(next); //Push the current coords in the Path list
				used[next.x][next.y]= true; //Mark the cell as used
				
				Solve(next, final, len-1); //Call recursion
				
				used[next.x][next.y]= false; //Mark the cell as not used
				Path.pop_back(); //Pop the element from the list
			}

		//check cell x, y+1;
		next.x = start.x;
		next.y = start.y + 1;
		if(matrix[next.x][next.y] == 1 && !used[next.x][next.y]) //Check if the cell is used or there is an obstacle
			{
				Path.push_back(next); //Push the current coords in the Path list
				used[next.x][next.y]= true; //Mark the cell as used
				
				Solve(next, final, len-1); //Call recursion
				
				used[next.x][next.y]= false; //Mark the cell as not used
				Path.pop_back(); //Pop the element from the list
			}

		//check cell x+1, y;
		next.x = start.x + 1;
		next.y = start.y;
		if(matrix[next.x][next.y] == 1 && !used[next.x][next.y]) //Check if the cell is used or there is an obstacle
			{
				Path.push_back(next); //Push the current coords in the Path list
				used[next.x][next.y]= true; //Mark the cell as used
				
				Solve(next, final, len-1); //Call recursion
				
				used[next.x][next.y]= false; //Mark the cell as not used
				Path.pop_back(); //Pop the element from the list
			}

		//check cell x, y-1;
		next.x = start.x;
		next.y = start.y - 1;
		if(matrix[next.x][next.y] == 1 && !used[next.x][next.y]) //Check if the cell is used or there is an obstacle
			{
				Path.push_back(next); //Push the current coords in the Path list
				used[next.x][next.y]= true; //Mark the cell as used
				
				Solve(next, final, len-1); //Call recursion
				
				used[next.x][next.y]= false; //Mark the cell as not used
				Path.pop_back(); //Pop the element from the list
			}

	}

int main()
	{
		int m, n;
		cout << "Size -> m and n: ";
		cin >> m >> n; //Enter m and n

		//fill matrix
		for(int i = 0; i < m; i++)
			for(int j = 0; j < n; j++)
				matrix[i][j] = 1;

		//Enter start and final point
		cout << "Start point: ";
		Point start, final;
		cin >> start.x >> start.y;
		cout << "Final point: ";
		cin >> final.x >> final.y;

		//Enter the number of obstacles
		cout << "Obstacles: ";
		int obs;
		cin >> obs;
		int x, y;
		for(int i = 0; i < obs; i++) //Enter obstacles
			{
				cout << "Obst. <" << i+1 << ">: ";
				cin >> x >> y;
				matrix[x][y] = 0;
			}

		cout << "Path length: ";
		int len;
		cin >> len; //Enter path length

		cout << endl;
		cout << "Ways:" << endl;
		used[start.x][start.y] = true; //Mark the start point as used
		Path.push_back(start); //Push the start point in the list
		Solve(start, final, len); //Call function
		

		system("pause");
		return 0;
	}