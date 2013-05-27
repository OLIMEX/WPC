/* 2013-05-25 by kantal59
   License: LGPL
   Compile: gcc -o reciprocal  reciprocal.c  -lm

   OLIMEX WPC#10:
            Let 0 < (a/b) < 1 where a and b are positive integers. Make program which enters the numbers a and b
            then represent a/b with as sum of numbers 1/n + 1/n2 + 1/n3… and prints the n numbers.
   
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
          

void reciprocal( unsigned long int a, unsigned long int b, long double eps)
{
 long double v,n;
 
 v= (long double)a/b;
 
 eps= fabsl(eps);
 while( v > eps){ 
                    // printf( "v=%.20Lf, 1/v=%.20Lf, ceill=%.20Lf\n ", v, 1.0/v, ceill(1.0/v)); // debugging
    n= ceill( 1.0/v);  
    v-= 1.0/n ; 
    printf("%.Lf ", n);
 } 

 puts("");

}


long double epsilon()  
{ // based on Todor Nikodimov's code from WPC#9
    long double eps= 1;
    while( (1.0 + eps) > 1.0 )  eps= eps/10.0 ;
    return( eps*100);
} 


int main( int argc, char *argv[])
{

 long int a,b;
 long double eps; 
 #define NTEST  6
 unsigned long int tdata[NTEST][2]= { 6,7, 3,4, 5,19, 8,11, 5,7, 3,5000 };
 int i;
  
 eps= epsilon();
 
 if( argc!=3 || (a=strtol(argv[1],NULL,10))<=0 || (b=strtol(argv[2],NULL,10))<=0 || a>=b ){
    puts("\nWrong input\nUsage: $> reciprocal a b\n- where a,b are positive integers and a<b\n");
    for(i=0; i<NTEST; i++){
        printf("- using test data a=%lu, b=%lu --> ", tdata[i][0], tdata[i][1] ); 
        reciprocal( tdata[i][0], tdata[i][1], eps );
    }  
 } 
 else{  
    reciprocal( a,b, eps);
 }
    
 printf("Epsilon was: %Le\n\n", eps);
 
 return(0);
}


