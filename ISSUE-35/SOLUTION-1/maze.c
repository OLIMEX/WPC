/* for complie & link : gcc -o maze maze.c
   for run: ./maze
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIMIT  7

int maze[LIMIT][LIMIT] ;
void findpath(int,int,int) ;
int check() ;
void print () ;
int main()
{
    int i , x , y  ;
    srand (time(NULL));
    for ( i = 0 ; i < LIMIT / 2; i++ ) {
        x = rand() % LIMIT ;
        y = rand() % LIMIT ;
        if ( x == 0 && y == 0 ) { --i ; continue ; }
        if ( maze[x][y] != 0 ) { --i ; continue ; }
        maze[x][y] = -1 ;
    }
    printf ( "\nMaze") ;
    print() ;
    maze[0][0] = 1 ;
    findpath ( 0 , 1 , 2) ;
    findpath ( 1 , 0 , 2) ;
    printf ( "No path\n") ;
    return 0;
}

int check ( ) {
  int i , j ;
  for ( i = 0 ; i < LIMIT ; ++i )
    for ( j = 0 ; j < LIMIT ; ++j )
        if ( maze[i][j] == 0 ) return 0 ;
  return 1 ;
}

void print ( ) {
  int i , j ;
  for ( i = 0 ; i < LIMIT ; ++i ) {
    printf ( "\n")  ;
    for ( j = 0 ; j < LIMIT ; ++j )
        if ( maze[i][j] == -1 )
            printf ( "  * " ) ;
        else
            printf ( "%3d ", maze[i][j]) ;

  }
  printf ( "\n")  ;
  return ;
}

void findpath(int x , int y , int n  ) {
    if ( x == 0 && y == 0 ) {
      if ( check() ) {
        printf ( "Decision")  ;
        print() ;
        exit (0);
      }
    }
    if ( maze[x][y] != 0 )  return ;
    maze[x][y] = n++ ;
    if ( x - 1 >= 0 )
      findpath( x - 1 ,  y ,  n  )  ;
    if ( x + 1 < LIMIT )
      findpath( x + 1 ,  y ,  n  )  ;
    if ( y - 1 >= 0 )
      findpath( x ,  y - 1,  n  )  ;
    if ( y + 1 < LIMIT)
      findpath( x  ,  y + 1  ,  n  )  ;
    maze[x][y] = 0 ;
    return ;
}

