/* 2013-05-19 by kantal59
   License: LGPL
   Compile: gcc -o circle  circle.c  -lm

   OLIMEX WPC#9:
            Let have N (3..100) points with X,Y coordinates. 
            Make code which checks if there is circle which to pass through all of them.
   
   From the first 3 points, if they aren't on the same line, the center point of the circle and the radius are calculated.
   For all the other points, the distance from the center point is checked.
   The precision can be set by the 'DELTA' constant. Here the precision means a heuristic one only :-)
   Each line in the data file contains the x and y long double coordinates of a point separeted with whitespace(s). 
   The file can contains empty line or line beginning with '#'.
   Duplicated input point datas count one. 
*/

#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include <string.h>

#define MAXNP   300
#define DELTA   0.0000001   

typedef struct { long double x, y; } point_t;


//-----------------------------------
        int line( point_t* pa)

// It checks if the first 3 points are on the same line  
// x1*(y2-y3)- x2*(y1-y3)+ x3*(y1-y2) == 0       
//------------------------------------
{   
    int i;
    // for( i=0; i<3;i++){ printf("%.18Lf, %.18Lf\n", pa[i].x, pa[i].y); }    
    if( fabsl( pa[0].x* (pa[1].y-pa[2].y)- pa[1].x* (pa[0].y-pa[2].y)+ pa[2].x* (pa[0].y-pa[1].y) ) < DELTA ){
        return(1);     
    }    
    return(0);
}

//------------------------------------------------
        long double tangent( point_t* pts)
    
// There must be 2 points at least!    
// m= (bx-ax)/(ay-by)
//-------------------------------------------------    
{    
    return( (pts[1].x-pts[0].x)/(pts[0].y-pts[1].y) );
}

//---------------------------------------------
        long double ctag( point_t* pts)
        
// y= m1*x + b1
// b1= (ay+by)/2- m1*(ax+bx)/2        
//---------------------------------------------
{   
    return( 0.5*( (pts[0].y+pts[1].y)- tangent( pts)*(pts[0].x+pts[1].x) ) );
}

//-------------------------------------------------
        int find_circle( int n, point_t* pa )
//-------------------------------------------------        
{
    long double xm,ym,r2,dist;
    int i;
    
    if( n<3 ){         
        puts("Not enough points.");
        return(-1);
    }    
    if( line( pa) ){
        puts("Points are on the same line.");
        return(-2);
    }        
    
    if( pa[0].y==pa[1].y ){ 
        // xm=(ax+bx)/2 
        xm=0.5*(pa[0].x+pa[1].x);
        // ym= m2*xm+ b2
        ym= tangent( pa+1)*xm+ ctag(pa+1);
    }
    else{
        if( pa[1].y==pa[2].y ){ 
            // xm=(bx+cx)/2 
            xm=0.5*(pa[1].x+pa[2].x);
            // ym= m1*xm+ b1
            ym= tangent( pa)*xm+ ctag(pa);
        }
        else{
            // xm= (b1-b2)/(m2-m1)
            xm= ( ctag(pa)-ctag(pa+1) )/( tangent(pa+1)-tangent(pa) );
            // y= m1*x+ b1
            ym= tangent(pa)*xm+ ctag(pa);
        }    
    }
    
    r2= (xm-pa[0].x)*(xm-pa[0].x)+(ym-pa[0].y)*(ym-pa[0].y);
    printf("A circle for the first 3 points: Center(%Lf, %Lf) with the Radius %Lf\n", xm,ym, sqrtl(r2) ); 
    
    for( i=3; i<n; i++){
    
        dist= (xm-pa[i].x)*(xm-pa[i].x)+(ym-pa[i].y)*(ym-pa[i].y);          
        if( fabsl( dist- r2) > DELTA  ){
            puts("There is no circle to pass through all the points.\n");
            return(-3);
        }
    }
    
    printf("The circle passes all the %d points through with precision DELTA=%e\n",n,DELTA );
    return(0);
}

//---------------------------------------------------------------
        int read_data( char *fname, point_t *parr, int num)
        
// Duplicated points will be removed.        
//---------------------------------------------------------------        
{    
 FILE* fs;
 char *pbuff, *ptr, *tailptr;
 size_t blth;
 int linenum,rtcd, dup,index,j;
 char *whsp= " \t\r\f\n";
 long double x,y;
 
 rtcd=0;
 if( (fs=fopen( fname,"r"))==NULL ){ 
            puts("File open error");
            return(-1);
 }
 
 pbuff=NULL;
 blth=0;
 linenum=index= 0;
 while( getline( &pbuff, &blth, fs) > 0 ){ 	
    linenum++; 
    if( index >= num ) break;
	ptr= pbuff;
	ptr+= strspn( pbuff,whsp); 
	if( *ptr=='#' || *ptr==0 ) continue; // comment or empty line
    x= strtold( ptr, &tailptr);
    if( ptr==tailptr ){
        printf("Syntax error in line %d\n", linenum);
        rtcd= -2; 
        break;
    }
    y= strtold( (ptr=tailptr), &tailptr);
    if( ptr==tailptr ){
        printf("Syntax error in line %d\n", linenum);
        rtcd= -3;
        break;
    }
    
    for( dup=j=0; j<index; j++){
            if( x== parr[j].x && y== parr[j].y ){
                dup++;
                printf("Duplication removed from line %d\n", linenum);
                break;
            }
    }    
    if( !dup){
            parr[ index].x=x;
            parr[ index].y=y;
            index++;
    }    
    
 }
 
 
 if( rtcd==0 ){
    printf("Number of points read: %d\n", index);
    rtcd= index;
 }
    
 fclose( fs);
 return(rtcd);
}

//----------------------------------------------
        int main( int argc, char *argv[])
//----------------------------------------------        
{
 point_t *parr;
 int test=0, num;
 int i;
 
 
 printf("\nLDBL_DIG: %d, LDBL_EPSILON: %.25Lf\nDELTA: %e\nMAX NUMBER OF POINTS: %d\n", LDBL_DIG, LDBL_EPSILON, DELTA, MAXNP);

 if( argc!=2 ){ 
               puts("\nUsage: $> circle datafile\n- using test data now\n");  
               test=1;               
 }
 else{ printf("Input file: %s\n", argv[1]); }  
                
 if( (parr= malloc( MAXNP*sizeof(point_t))) == NULL ){
              puts("Memory allocation error.");  
              return(-1); 
 } 
 
 if( !test){
       if( (num=read_data( argv[1], parr, MAXNP))<=0 ){
                puts("Data read error."); 
                free(parr);
                return(-2);
       }
 } 
 else{ // test data
         num= MAXNP;         
          for( i=0;i<num;i++){ 
                parr[i].x= (long double)1/(i+1); 
                parr[i].y= sqrtl(25-parr[i].x*parr[i].x); 
          }  
          printf("Number of test points: %d\n", num);
 } 
 
 
 find_circle( num,parr);
 free( parr);
 return(0);
}


