// for translate & link : gcc -o similar similar.c
// for running :  ./similar


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

    FILE *fd ;
    char buf[256] , wrk[256] ;
    int lenw , lenb , i , flag  ;
    char in[256]  ;

    fd = fopen ( "alice.txt" , "r" ) ;
    if ( fd == NULL ) {
        printf ( "Can't open alice.txt\n") ;
        return 1 ;
    }


    printf ( "input word : ") ;
    scanf ( "%s" , in ) ;

    lenw = strlen ( in ) ;

    while ( 1 ) {
      fscanf ( fd , "%s" , buf ) ;
      if ( feof ( fd ) ) {
        printf ( "end of file \n") ;
        return 0 ;
      }

      lenb = strlen ( buf ) ;

      if ( lenb == lenw ) {
            flag = 0 ;
            for ( i = 0 ; i < lenw ; i++ )
              if ( buf[i] != in[i]) ++flag ;
            if ( flag == 1 )
               printf ( "%s : %s\n" , in , buf ) ;
            continue ;
      }


      if ( (lenb + 1) == lenw ) {

            for ( i = 0 ; i < lenw ; i++ ) {
                 if  ( buf[i] != in[i] ) break  ;
                 else wrk[i] = buf[i] ;
            }

            wrk[i] = in[i] ;  // insret symbol

            for ( ;i < lenb ;++i )
              wrk [i+1] = buf[i] ;

            wrk[i+1] = '\0' ;

           if ( !strcmp (wrk ,in ) )
              printf ( "%s : %s\n" , in , buf ) ;

           continue ;


      }



      if ( (lenb - 1) == lenw ) {

            for ( i = 0 ; i < lenw ; i++ ) {
                 if  ( buf[i] != in[i] ) break  ;
                 else wrk[i] = buf[i] ;
            }

            ++i ;  // skip symbol

            for ( ;i < lenb ;++i )
              wrk [i-1] = buf[i] ;

            wrk[i] = '\0' ;

           if ( !strcmp (wrk ,in ) )
              printf ( "%s : %s\n" , in , buf ) ;

      }

   } // end of while


    return 0;
}
