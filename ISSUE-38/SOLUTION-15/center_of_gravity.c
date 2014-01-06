// Generate spot and fixing center of gravity

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define DIM  50


int main()
{
    char matrix[DIM][DIM] ; // 254 ;
    int i , j ,  l ;
    int xc , yc ; // coordinate of center  of gravity
    int sx , sy ;   // moment for x and y line
    int f ; // space of spot


    // create spot
    srand (time(NULL));
    for ( i = 0 ; i < DIM ; i++)
        for ( j = 0 ; j < DIM ; j++)
            matrix[i][j] = (char)254;

    for ( i = 0 ; i < DIM ; i++ ) {
        l = rand() % (DIM /3) ;
        for ( ; l >= 0 ;--l)
            matrix[i][l] = ' ' ;

        l = rand() % (DIM /3) ;
        for ( ;DIM - l < DIM ;--l)
            matrix[i][DIM - l] = ' ' ;
    }

    // fixing center of gravity
    f = 0 ; sx = sy = 0.0 ;
    for ( i = 0 ; i < DIM ; i++)
        for ( j = 0 ; j < DIM ; j++) {
           if ( matrix[i][j] == (char)254 ) {
                ++f ;
                sx = sx +  i ;
                sy = sy +  j ;
           }

        }
    // coord center of gravity
    xc = (int) sx / f ;
    yc = (int) sy / f ;

    matrix[xc][yc] = '*' ;  // center of gravity

    for ( i = 0 ; i < DIM ; i++) {
        printf ( "\n") ;
        for ( j = 0 ; j < DIM ; j++)
           printf ( "%c" , matrix[i][j]) ;
    }

    printf ( "\ncenter of gravity ( %d , %d ) \n" , xc , yc );

    return 0;
}
