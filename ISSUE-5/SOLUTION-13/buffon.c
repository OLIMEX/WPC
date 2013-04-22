/* 2013-04-21 by kantal59
   License: LGPL
   Compile: gcc -o buffon  buffon.c -lm

   OLIMEX WPC#5:
            Calculating Pi using the Buffon’s needle method.
   
   The 'experiment' function doesn't use a hidden Pi value nor trigonometric function. 
   
*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <inttypes.h> 
#include <math.h>

//--------------------------------------------------------------------------------------
    unsigned long experiment( double nlength, double swidth, unsigned long drops)
//--------------------------------------------------------------------------------------    
{
 union{
    uint16_t state[3];
    time_t time;
  } seed;
  
  unsigned long i,crossing=0;
  double d,vx,vy,y;  
  
  seed.time=time(0);
  for( i=0; i<drops; i++){
    do{
      vx= erand48(seed.state);    // selecting the direction vector of the needle using the "direct-surface" method
      vy= erand48(seed.state);   
   }while( vx*vx+vy*vy >1);
   
    d= erand48(seed.state)*swidth/2;     // d is the distance of the needle's center point from the nearest line, d=[ 0, swidth/2 )
    y= 0.5*vy*nlength/sqrt(vx*vx+vy*vy); // d-y is the distance of the needle's end from the line
    if( y >= d ) crossing++;

  }
  
 return( crossing);
}

//-------------------------------------------------------------------------------------------------
    double evaluate( double nlength, double swidth, unsigned long drops,unsigned long crossing)
//-------------------------------------------------------------------------------------------------    
{
 double dratio;
 
 dratio= nlength/swidth;
 if( nlength <= swidth) return( 2*nlength*drops/(swidth*crossing)); // short needle case
 else{                                                                     
   return( 2*drops* ( acos(1/dratio)+ dratio - sqrt( dratio*dratio-1) ) /crossing ); // long needle case
 }
 
}


/* ---------------------------
        T E S T I N G
----------------------------*/        
int main( int argc, char *argv[])
{
 
 double nlength, swidth, npi;
 long drops, crossing;
 
 if( argc!=4 || (nlength=strtod( argv[1],NULL))<=0 || (swidth=strtod(argv[2],NULL))<=0 || (drops=strtol(argv[3],NULL,10))<=0 ){ 
    puts("\n\tUsage: $> buffon  needle_length  stripes_width  drops\n");
    nlength=1;
    swidth=1;
    drops=213000;
 }    
 
 crossing= experiment( nlength, swidth, drops);
 npi=        evaluate( nlength, swidth, drops, crossing);
 printf( "needle length=%f\nstripes width=%f\ndrops=%ld\ncrossing=%ld\npi~%.6f\n", nlength, swidth, drops, crossing, npi);
 
 return(0);
}


