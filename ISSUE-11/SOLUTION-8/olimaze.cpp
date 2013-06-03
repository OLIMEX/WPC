// olimaze.cpp
//
// Weekend Programming Challenge ISSUE-11 – Maze
// http://olimex.wordpress.com/2013/05/31/weekend-programming-challenge-issue-11-maze/
//

#include <stdio.h>

//////////////////////////////////////////////////////////////////////////////

static const int MAX_XY = 100;

static char maze_s [MAX_XY+1][MAX_XY+1] =	// could be read from file/console
{
	"WWWWWWWWWW",
	"W  WW    W",
	"W       WW",
	"W  @@    W",
	"W @@     W",
	"W      @ W",
	"W@    @@ W",
	"WWWWWWWWWW",
};

static int X = 10;
static int Y =  8;

//////////////////////////////////////////////////////////////////////////////

static int find_obj (int y, int x)
{
	if (y < 0 || x < 0)		// needed in case there is no outside Wall
		return 0;
	if (maze_s[y][x] != '@')
		return 0;
	maze_s[y][x] = ' ';
	int cnt = 1
			+ find_obj (y  , x-1)
			+ find_obj (y-1, x  )
			+ find_obj (y  , x+1)
			+ find_obj (y+1, x  );
	return cnt;
}

int main (int , char **)
{
	int max_cnt = 0;
	int x, y;
	
	for (y = 0; y < Y; y++)
		for (x = 0; x < X; x++)
		{
			int cnt = find_obj (y, x);
			if (max_cnt < cnt)
				max_cnt = cnt;
		}
	
	printf ("%d as the largest area obstracles is composed by %d @ connected together. ;)\n", max_cnt, max_cnt);
	return 0;
}
