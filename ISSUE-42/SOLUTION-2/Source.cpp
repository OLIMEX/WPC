/*
Task: Write code which enters N segments with their coordinates X1,Y1,X2,Y2 
	  then check if it’s possible to draw all segments without lifting your pen and if 
	  YES write the path sequence.
Date: 9th February 2014
Author: Sinan Zikri
*/

#include<iostream>
#include<list>
using namespace std;

struct Point //We make a structure so we can save the entered points
{
	int x;
	int y;
};

const int OFFSET = 50; //The OFFSET allows us to use negative index
int n; //This is the number of the line segments that we are going to enter
list<Point> figure[OFFSET * 2][OFFSET * 2]; //Thanks to OFFSET we can work with indexes in the range [-50; 50];
bool usedLines[OFFSET * 2][OFFSET * 2][OFFSET * 2][OFFSET * 2]; //This helps us to mark 
																//a line segment from one point to another as used
list<Point> Path; //We save our path so far in this list of points
bool wayFound = false; //This variable tells us if we have found a way to draw everything
					  //If we don't have it, the program will output all possible ways to draw the shape

void PrintPath() //This is a simple function that iterates through the Path list and outputs the points
{
	list<Point>::iterator Iter = Path.begin();

	cout << endl;
	cout << "PATH: " << endl;
	cout << "START, ";
	for(Iter; Iter != Path.end(); Iter++)
	{
		cout << "(" << Iter->x - OFFSET << ", " << Iter->y - OFFSET<< "), "; //We substract the OFFSET so we can see
																			//the correct indexes of the points
	}
	cout << "END" << endl;
}

//This is a Depth-First-Search(DFS) algorithm to iterate through graph's vertices
//Wikipedia link: http://en.wikipedia.org/wiki/Depth-first_search
void FindPath(Point point, int len)
{
	if(len == n) //If we have drawn all line segments we output the path
	{
		PrintPath();
		wayFound = true;
		return;
	}

	list<Point>::iterator Iter = figure[point.x][point.y].begin(); 
	for(Iter; Iter != figure[point.x][point.y].end() && !wayFound; Iter++)
	{
		Point p = *Iter;
		if(!usedLines[point.x][point.y][p.x][p.y]) //If we haven't drawn a segment with this coordinates we draw it
		{
			usedLines[point.x][point.y][p.x][p.y] = true; //We mark the line segment between these two points as drawn
			usedLines[p.x][p.y][point.x][point.y] = true;
			Path.push_back(p); //We push the current point in the path

			FindPath(p, len + 1); //And then we start drawing from point p

			usedLines[point.x][point.y][p.x][p.y] = false; //If we come back we mark the line segment as not used
			usedLines[p.x][p.y][point.x][point.y] = false;
			Path.pop_back();// And delete it from the path
		}
	}
}


int main()
{
	cin >> n; //We insert the number of line segments
	Point startPoint; //This Point variable will hold the starting point
	for(int i = 0; i < n; i++)
	{
		Point point1, point2;
		cin >> point1.x >> point1.y >> point2.x >> point2.y; //We read the coordinates of each line segment

		point1.x += OFFSET; //Then we add the OFFSET
		point1.y += OFFSET;
		point2.x += OFFSET;
		point2.y += OFFSET;

		if(i == 0) //If this is the first line segment we mark the first point as starting point
		{
			startPoint.x = point1.x;
			startPoint.y = point1.y;
		}

		figure[point1.x][point1.y].push_back(point2); //And then we connect our graph
		figure[point2.x][point2.y].push_back(point1);
	}

	Path.push_back(startPoint); //We push the start point in the path
	FindPath(startPoint, 0); //And then the searching begins

	return 0;
}

/*
Figure 1 from the example at 
http://olimex.wordpress.com/2014/02/07/weekend-prorgamming-challenge-week-42-no-lift-pen-drawings/
3
-2 3 2 3
2 3 -2 -3
-2 -3 2 -3
*/

/*
Figure 2 from the example at 
http://olimex.wordpress.com/2014/02/07/weekend-prorgamming-challenge-week-42-no-lift-pen-drawings/
6
-2 0 2 0
-2 0 0 3
0 3 2 0
-2 0 -2 -3
-2 -3 2 -3
2 -3 2 0
*/

