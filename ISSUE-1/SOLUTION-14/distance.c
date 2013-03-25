/* 2013-03-23 by kantal59
   License: LGPL
   Compile: gcc -o distance  distance.c -lm

   It calculates the 2D distance between a 'C' point and a line given by points 'A' and 'B'.
   d= |N * (Rc-Ra)| 	
   Where N is a normal unit vector of the line and Rc,Ra are location vectors of points C,A. 
   '*' means scalar multiplication.
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>

//----------------------------------------------------------------------------------------------
	double distance( long ax, long ay, long bx, long by, long cx, long cy)
//----------------------------------------------------------------------------------------------
{
 long nx, ny, dcax, dcay; 
 double val;

 dcax= cx-ax;
 dcay= cy-ay;
 if( (nx=by-ay)==0 && ax==bx ){ 	   // There is no line, a and b are the same, so it returns the distance between a and c .
				   //  Alternate solution could be:  return(-1);
	 return( sqrt( dcax*dcax + dcay*dcay) ); 
 }									   
 ny=ax-bx;
 val= ( dcax*nx + dcay*ny )/ ( sqrt( ny*ny + nx*nx ) );
 return( val>=0 ? val : -val );

}


//-------------------------------------------
	int main( int argc, char *argv[])
//-------------------------------------------
#define p(n)	strtol(argv[n],NULL,10)
{
 double d;

 if( argc!=7 ){	
	printf( "Usage: $> distance AX AY BX BY CX CY\n"
		" It calculates the 2D distance between a 'C' point and a line given by points 'A' and 'B'.\n"
		" The coordinates are integers and the result will certainly be correct"
		" if the values are in the range [%.0f : %.0f]\n",  -sqrt(LONG_MAX/8), sqrt(LONG_MAX/8) );
	return(1);
 }

 d= distance( p(1),p(2),p(3),p(4),p(5),p(6) );

 printf("The distance between (%ld,%ld)A___B(%ld,%ld) and C(%ld,%ld)=> %f\n", p(1),p(2),p(3),p(4),p(5),p(6), d );
	 
 return(0);
}


