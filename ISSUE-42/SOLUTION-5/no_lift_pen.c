// use theorem for euler
// there are two example graphs which are described in file in.txt (in.jpg  view) ,
// in1.txt (in1.jpg view )
// for run: no_lift_pen <file>

#include <stdio.h>
#include <stdlib.h>

#define LIM 20
int main(int argc , char* argv[] )
{
    FILE *fp ;
    int a , b , i , j  , odd , even  , s , start , flag ;
    int mat[LIM][LIM];

    if ( argc < 2 ) {
        printf ( "use: no_lift_pen  file") ;
        return 1;
    }

    fp = fopen ( argv[1] , "r" ) ;
    if ( fp == NULL ) {
        printf ( "can't open in.txt\n");
        return 1 ;
    }

    for ( i=0 ; i < LIM ; i++)
        for ( j=0 ; j < LIM ; j++)
            mat[i][j] = 0 ;
    i = j = -1  ;
    while ( 1 ) {
        fscanf ( fp , "(%d,%d)", &a , &b  ) ;
        if ( i==a && j==b )  break ;
        i=a ; j=b;
        mat[i-1][j-1] = 1 ; mat[j-1][i-1] = 1 ;
    }
    fclose ( fp ) ;
    //check  exist solution , euler graph
    even =  0 ; odd = 0 ; start = 0 ;
    for ( i=0 ; i < LIM ; i++ ) {
        s = 0 ;
        for ( j=0 ; j<LIM ;j++ )
               if ( mat[i][j] == 1 )
                    ++s ;
        if ( s % 2 ) { ++odd ; start = i ; }
        else ++even ;
    }

    if ( odd != 2 && odd != 0 ) {
        printf ( "can't solution \n") ;
        return 1 ;
    }

    // make solution , find Euler cicle in graph
    i = start ;
    printf ( "%d" , i+1 );
    while ( 1 ) {
        for ( j=0 ; j < LIM ; j++ )
            if ( mat[i][j] != 0 ) {
                mat[i][j] = 0 ;
                mat[j][i] = 0 ;
                printf ( ",%d" , j+1 );
                i = j ;
                break ;
            }
         flag = 0 ;
         for ( a=0 ; a < LIM ;a++)  {
            if ( flag ) break ;
            for ( b=0 ; b < LIM ;b++)
                 if ( mat[a][b] != 0 ) {
                    flag = 1 ;
                    break ;
                 }

         }
         if ( flag == 0 ) break ;  // solution
      }
    return 0;
}
