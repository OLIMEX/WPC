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
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct { double x; double y; } point_t;
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
 double a,b,c, diag;
 double s=0;
 
 if( n!=4 ) return(false);
 c= dist2( pts[0], pts[3]);
 if( (a= dist2( pts[0], pts[1])) == (b= dist2( pts[0], pts[2])) ){ s=a; diag=c; }
  else if( a==c ){ s=a; diag=b;}
        else if( b==c){ s=b; diag=a; }
  
 if( s!=0 && 2*s==diag ) return(true);
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
     if( get_coords( NP, &argv[1], points) == -1 ){     puts("Input error");    return(1);    }
 }    
      
 
 for( i=0; i< NP; i++)  printf("(%16.8g, %16.8g)\n", points[i].x, points[i].y);
 
 if( isSquare( NP, points) ) puts("Square\n"); else puts("Not a square\n");
 
 return(0);

}


