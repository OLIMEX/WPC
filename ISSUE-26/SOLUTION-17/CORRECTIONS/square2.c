/*
 2013-09-29 by kantal59
 License: LGPL
 Compile: gcc -o square  square.c
 
 OLIMEX WPC#26: Square
        Write code which check if four points make square.
        input data for squares:
        (0,0),(0,1),(1,1),(1,0)   - normal square
        (0,0),(2,1),(3,-1),(1,-2) - not aligned square
        (0,0),(1,1),(0,1),(1,0)   - different order of the points
        input data for non-squares:
        (0,0),(0,2),(3,2),(3,0) - rectangle
        (0,0),(3,4),(8,4),(5,0) - rhombus
        (0,0),(0,0),(1,1),(0,0) - three points are same
        (0,0),(0,0),(1,0),(0,1) - two points are same
        
 2014-01-30: isSquare() replaced; 
        - see kasimir's comment: http://olimex.wordpress.com/2013/09/30/weekend-programming-challenge-week-26-solutions/#comments
        - degenerate cases allowed, e.g.: (1,1),(1,1),(0,0),(0,0) or (1,1),(1,1),(1,1),(1,1)
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct { double x,y; } point_t;
#define NP      4   // number of points
#define true    1
#define false   0


//------------------------------------------------------------------------------
    int get_coords( int n, char* strcoord[], point_t* pts)
//------------------------------------------------------------------------------
{
 int i,k;
 double s;
 char *endptr;
 
 for( i=0; i<=2*n-1; i++){  
    s= strtod( strcoord[i], &endptr);
    if( endptr== strcoord[i] ) return(false); 
    if( i%2 ) pts[i/2].y= s; else pts[i/2].x= s;
 }   
 
 return(true);
}


//------------------------------------------------------------------------------
    double dist2( point_t p1, point_t p2)
//------------------------------------------------------------------------------    
{
    return( (p2.x-p1.x)*(p2.x-p1.x) + (p2.y-p1.y)*(p2.y-p1.y) );
}      


//------------------------------------------------------------------------------
    int isSquare( int n, point_t* pts)   
//------------------------------------------------------------------------------
{
 double d01,d02,d03,d12,d13,d23;
 
 if( n!=4 ) return(false);
 d01= dist2( pts[0], pts[1]);
 d02= dist2( pts[0], pts[2]);
 d03= dist2( pts[0], pts[3]);
 d12= dist2( pts[1],pts[2]);
 
 if( d01==d02 && d03==d12 ) return(true);   // d03 is a diagonal
 d13= dist2( pts[1],pts[3]);
 if( d01==d03 && d02==d13 ) return(true);   // d02 is a diagonal
 d23= dist2( pts[2],pts[3]);
 if( d02==d03 && d01==d23 ) return(true);   // d01 is a diagonal
  
 return(false); 
}    


//------------------------------------------------------------------------------
    int main( int argc, char* argv[])
//------------------------------------------------------------------------------
{
 int i,k;
 point_t points[NP];
 double a,b,c,s; 
 
 if( argc != 2*NP+1 ){    
    printf("\nUsage: $square x1 y1 ... x%d y%d\n\n", NP, NP);  
    if( NP==4){    
        points[0].x=0;    points[0].y=0; 
        points[1].x=1.5;  points[1].y=1.5; 
        points[2].x=0;    points[2].y=1.5; 
        points[3].x=1.5;  points[3].y=0;
    }
    else return(1);    
       
 }
 else{
     if( get_coords( NP, &argv[1], points) == false ){     puts("Input error");    return(1);    }
 }    
      
 
 for( i=0; i< NP; i++)  printf("(%16.8g, %16.8g)\n", points[i].x, points[i].y);
 
 if( isSquare( NP, points) ) puts("Square\n"); else puts("Not a square\n");
 
 return(0);

}


