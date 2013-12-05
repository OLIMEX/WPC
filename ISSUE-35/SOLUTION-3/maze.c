/**
 * Olimex Weekend Programming Challenge - Issue #35 Maze solver
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// gcc -march=native -O3 -s -o maze maze.c
#include <stddef.h>
#include <stdio.h>

/*int maze[2][2] = {
  {1,1},
  {1,1}
};*/

/*int maze[3][3] = {
  {1,1,1},
  {1,1,1},
  {1,1,1},
};*/

/*int maze[3][3] = {
  {1,1,1},
  {1,0,1},
  {1,1,1},
};*/

/*int maze[4][4] = {
  {1,1,1,1},
  {1,1,1,1},
  {1,1,1,1},
  {1,1,1,1}
};*/

/*int maze[4][4] = {
  {1,1,1,0},
  {1,1,1,1},
  {1,1,1,1},
  {1,1,1,0}
};*/

/*int maze[5][5] = {
  {1,1,1,1,1},
  {1,1,0,1,1},
  {1,1,0,1,1},
  {1,1,1,1,1},
  {1,1,0,1,1}
};*/

/*int maze[7][7] = {
  {1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1},
  {1,0,1,1,1,1,1},
  {1,1,1,1,1,1,1},
  {1,1,1,1,0,1,1},
  {1,1,1,1,1,1,1},
  {1,1,0,1,1,1,1}
};*/

/*int maze[8][8] = {
  {1,1,1,1,1,1,1,1},
  {1,1,1,1,1,0,1,1},
  {1,0,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1},
  {1,1,1,0,1,1,1,1},
  {1,1,1,1,1,1,1,1},
  {1,1,0,1,1,1,1,1},
  {1,1,1,1,1,1,1,1}
};*/

/*int maze[9][9] = {
  {1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1},
  {1,1,1,1,0,1,1,1,1},
  {1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1}
};*/

/*int maze[9][9] = { // No solution, takes 10m7.270s to test
  {1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,0,0,0},
  {1,1,1,1,1,1,0,1,1},
  {1,1,1,1,1,1,0,1,1}
};*/

/*int maze[10][10] = { // ~2 minutes to find a solution
  {1,1,1,1,1, 1,1,1,1,1},
  {1,1,1,1,1, 1,1,0,1,1},
  {1,0,1,1,1, 1,1,1,1,1},
  {1,1,1,1,1, 1,1,1,1,1},
  {1,1,1,1,0, 1,1,1,1,1},

  {1,1,1,1,1, 1,1,1,1,1},
  {1,1,1,1,1, 1,1,1,1,1},
  {1,1,0,1,1, 1,1,0,1,1},
  {1,1,1,1,1, 1,1,1,1,1},
  {1,1,1,1,0, 1,1,1,1,1}
};*/

int maze[11][10] = { // No solution, ~12 minutes
  {1,1,1,1,1, 1,1,1,1,1},
  {1,1,1,1,1, 1,1,0,1,1},
  {1,0,1,1,1, 1,1,1,1,1},
  {1,1,1,1,1, 1,1,1,1,1},
  {1,1,1,1,0, 1,1,1,1,1},

  {1,1,1,1,1, 1,1,1,1,1},
  {1,1,1,1,1, 1,1,1,1,1},
  {1,1,0,1,1, 1,1,0,1,1},
  {1,1,1,1,1, 1,1,1,1,1},
  {1,1,1,1,0, 1,1,1,1,1},

  {1,1,1,1,1, 1,1,1,1,1}
};

#define WIDTH (sizeof(maze[0])/sizeof(maze[0][0]))
#define HEIGHT (sizeof(maze)/sizeof(maze[0]))

int d[HEIGHT+2][WIDTH+2]; // zero-padded maze

void zeropad()
{
  size_t i, j;
  for (i = 1; i <= HEIGHT; ++i)
    for (j = 1; j <= WIDTH; ++j)
      d[i][j] = maze[i-1][j-1];
}

void printfield()
{
  size_t i, j;
  for (i = 0; i <= HEIGHT; ++i)
  {
    for (j = 0; j <= WIDTH; ++j)
      printf("%c", d[i][j]==0 ? ' ' : '*');
    printf("\n");
  }
}

void calculate()
{
  size_t i, j;
  for (i = 1; i <= HEIGHT; ++i)
    for (j = 1; j <= WIDTH; ++j)
      if (d[i][j] != 0)
      {
        int x = (d[i-1][j] > 0) + (d[i+1][j] > 0) + (d[i][j-1] > 0) + (d[i][j+1] > 0);
        if (x == 0) x = 1;
        d[i][j] = x;
      }
}

int check1()
{
  if (d[1][1] != 2)
    return 1;
  size_t i, j;
  for (i = 1; i <= HEIGHT; ++i)
    for (j = 1; j <= WIDTH; ++j)
      if (d[i][j] == 1)
        return 1;
  return 0;
}

int check2()
{
  size_t i, j;
  for (i = 1; i <= HEIGHT; ++i)
    for (j = 1; j <= WIDTH; ++j)
      if (d[i][j] != 0)
      {
        int x = (d[i-1][j] == 2) + (d[i+1][j] == 2) + (d[i][j-1] == 2) + (d[i][j+1] == 2);
        if (x > 2)
          return 1;
      }
  return 0;
}

int check3()
{
  int c[2] = {0, 0};
  size_t i, j;
  for (i = 1; i <= HEIGHT; ++i)
    for (j = 1; j <= WIDTH; ++j)
      if (d[i][j] != 0)
        ++c[(i+j)&1];
  return c[0] != c[1];
}

int countnonzero()
{
  int count = 0;
  size_t i, j;
  for (i = 1; i <= HEIGHT; ++i)
    for (j = 1; j <= WIDTH; ++j)
      count += (d[i][j] != 0);
  return count;
}

int curpath[WIDTH*HEIGHT+2][2] = {{1,1}};
size_t curpathlen = 1;
inline void pathpush(int y, int x)
{
  curpath[curpathlen][0] = y;
  curpath[curpathlen][1] = x;
  ++curpathlen;
}
inline void pathpop()
{
  --curpathlen;
}
void printpath()
{
  size_t i;
  for (i=0; i<curpathlen; ++i)
    printf(" %d,%d", curpath[i][0], curpath[i][1]);
  printf("\n");
}

inline void lookaround(int *options, int y, int x)
{
  int cnt = 0;
  if (d[y-1][x] > 0) { options[cnt++]=y-1; options[cnt++]=x; }
  if (d[y][x-1] > 0) { options[cnt++]=y; options[cnt++]=x-1; }
  if (d[y][x+1] > 0) { options[cnt++]=y; options[cnt++]=x+1; }
  if (d[y+1][x] > 0) { options[cnt++]=y+1; options[cnt++]=x; }
  while (cnt<6) options[cnt++] = 0;
}

inline void markoptions(int *options, int add)
{
  if (options[0]) d[options[0]][options[1]] += add;
  if (options[2]) d[options[2]][options[3]] += add;
  if (options[4]) d[options[4]][options[5]] += add;
}

int findpath(int y, int x, int remains)
{
  if (y == 1 && x == 1)
    return remains == 1;
  int options[6];
  pathpush(y, x);
  d[y][x] = -d[y][x]; // mark self
  lookaround(options, y, x);
  markoptions(options, -1);

  int ones = 0, oney, onex;
  if (d[options[0]][options[1]] == 1) {oney=options[0]; onex=options[1]; ++ones;}
  if (d[options[2]][options[3]] == 1) {oney=options[2]; onex=options[3]; ++ones;}
  if (d[options[4]][options[5]] == 1) {oney=options[4]; onex=options[5]; ++ones;}

  if (ones == 1 && (y!=1 || x!=2))
  {
    if (findpath(oney,onex,remains-1)) return 1;
  }
  else if (ones == 0 || (y==1 && x==2))
  {
    if (options[0] && findpath(options[0], options[1], remains-1)) return 1;
    if (options[2] && findpath(options[2], options[3], remains-1)) return 1;
    if (options[4] && findpath(options[4], options[5], remains-1)) return 1;
  }

  markoptions(options, +1);
  d[y][x] = -d[y][x]; // unmark self
  pathpop();
  return 0;
}

int solve()
{
  int remains = countnonzero();
  if (findpath(1,2,remains))
  {
    pathpush(1,1);
    return 1;
  }
  else
    return 0;
}

#define L 1
#define R 2
#define U 4
#define D 8

char getdirchar(int sum)
{
  switch (sum)
  {
    case L+R: return '-';
    case U+D: return '|';
    case L+U: return 'J';
    case L+D: return '7';
    case R+U: return 'L';
    case R+D: return 'r';
    default: return '?';
  }
}

int getdir(int y1, int x1, int y2, int x2)
{
  if (y1 == y2)
    return (x1 < x2) ? R : L;
  else
    return (y1 < y2) ? D : U;
}

void drawpath()
{
  char m[HEIGHT+2][WIDTH+2]; 
  size_t i, j;
  for (i = 0; i <= HEIGHT; ++i)
    for (j = 0; j <= WIDTH; ++j)
      m[i][j] = d[i][j]!=0 ? '.' : ' ';

  m[1][1] = getdirchar(D+R);
  for (i = 1; i < curpathlen-1; i++)
  {
    int y = curpath[i][0], x = curpath[i][1];
    int yl = curpath[i-1][0], xl = curpath[i-1][1];
    int yr = curpath[i+1][0], xr = curpath[i+1][1];
    int left = getdir(y,x,yl,xl);
    int right = getdir(y,x,yr,xr);
    m[y][x] = getdirchar(left+right);
  }

  for (i = 0; i <= HEIGHT; ++i)
  {
    for (j = 0; j <= WIDTH; ++j)
      printf("%c", m[i][j]);
    printf("\n");
  }
  printf("\n");
  printpath();
}

int main()
{
  zeropad();
  printfield();
  calculate();
  if (check1() || check2() || check3())
    printf("No solution\n");
  else
    if (solve())
      drawpath();
    else
      printf("Path not found\n");
  return 0;
}

