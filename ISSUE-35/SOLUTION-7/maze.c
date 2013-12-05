/* 
 2013-12-01 by kantal59
 License: LGPL
 Compile: gcc -o maze  maze.c
 OLIMEX WPC#35: Maze
         Maze with 10×10 cells have obstracles placed on random cells marked with the black. 
         Make code which finds path which starts from cell (1,1) and moves through all Maze cells 
         and returns back to cell(1,1) without stepping on same cell more than once.
         
         There is no great idea in the code, it tries the cells step by step.
         No input interface, the test data are embeded.

*/
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>     

typedef struct { int8_t x,y; } xy_t;
typedef union { 
                xy_t coord;
                uint16_t cell;
} cell_t;                

//--------- INPUT -----------------
/*
#define MSIZE   3
cell_t OB[]={ {2,2} };
*/

/*
#define MSIZE   3
cell_t OB[]={ {3,1},{3,2},{3,3},{2,3},{1,3}};
*/


#define TEST1
#define MSIZE   10
#define OBSIZE  36
cell_t OB[OBSIZE];


/* // It will run forever!
#define MSIZE 10
cell_t OB[]={ {8,2},{2,3},{5,5},{3,8},{8,8},{5,10} };
*/
//----------------------------------

// GLOBALS
cell_t Path[ MSIZE*MSIZE];
cell_t* ppath;
int L;


// FUNCTIONS
#ifdef TEST1
void initObsTest1()
{
    int i,j;
    cell_t *ptr;
    
    ptr=OB;
    for( i=3; i<9; i++) for( j=3; j<9; j++)   *ptr++=(cell_t){i,j};
}
#endif

int start()
{
    Path[0]= (cell_t){1,2};  Path[1]= (cell_t){1,1};  Path[2]= (cell_t){2,1};
    ppath= &(Path[2]);
    L= MSIZE*MSIZE-sizeof(OB)/sizeof(cell_t);
    return( findPath());
}


int isObstacle( cell_t c)
{
    int i;
    for( i=0; i<(sizeof(OB)/sizeof(cell_t)); i++) 
        if( OB[i].cell == c.cell ) return(1);
        
    return(0);
}
        
int isPath( cell_t c)
{
    cell_t* ptr;
    for( ptr=Path; ptr<=ppath; ptr++) if( (*ptr).cell==c.cell ) return(1);
    return(0);
}

int inMatrix( cell_t c)
{
    if( c.coord.x<1 || c.coord.x>MSIZE || c.coord.y<1 || c.coord.y>MSIZE) return(0);
    return(1);
}


int dataCheck()
{
 int i;
 if( (MSIZE*MSIZE-sizeof(OB)/sizeof(cell_t)) %2 ){
    printf("\n Odd number of free cells, there is no solution\n");   
    return(0);
 }
 
 for( i=0; i<sizeof(OB)/sizeof(cell_t); i++){ 
    if(  ! inMatrix( OB[i]) ){
        printf("\n (%d,%d) obstacle is out of the matrix!\n", OB[i].coord.x, OB[i].coord.y);
        return(0);
    }
 }
 
 if( isObstacle( (cell_t){1,1} ) ){
    printf("\n Start point (1,1) is an obstacle!\n");
    return(0);
 }
 
 if( isObstacle( (cell_t){1,2} ) || isObstacle( (cell_t){2,1} ) ){
    printf("\n Start point (1,1) is blocked!\n");
    return(0);
 }

 return(1);
}



int findPath()
{
    cell_t next;
    int i;
    static cell_t step[4]= { {1,0},{0,1},{-1,0},{0,-1} };
    static cell_t cend= {1,2};
    
    for(i=0; i<4; i++){
     
        next.coord.x= (*ppath).coord.x+step[i].coord.x;
        next.coord.y= (*ppath).coord.y+step[i].coord.y;
        
        if( next.cell== cend.cell ){
            if( L==(ppath-Path+1) ) return(1);
            continue;
        }
       
        if( ! inMatrix(next)  ||  isObstacle(next)  ||  isPath(next) ) continue;
        *(++ppath)= next;
        if( findPath() ) return(1);
        ppath--;
        
    }

    return(0);

}


void printPath(){

    cell_t *ptr;
    printf("\n ");
    for( ptr=Path+1; ptr<=ppath; ptr++)   printf("(%d,%d) ",(*ptr).coord.x,(*ptr).coord.y );
    printf("(1,2) (1,1)\n\n" );
}




int main()
{

#ifdef  TEST1
    initObsTest1();
#endif    
 
 
 if( dataCheck() && start() ){  printPath(); }
 else{
        printf("\n Path not found\n\n");
 }


 return(0);
}




