#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MIDLE  50
#define LEN  128
#define TREE  6

int main()
{

   char buf[128] ;
   int i , j , relative ;


    memset ( buf , ' ', 128 ) ;
    buf[MIDLE] = '*' ;
    buf[MIDLE+1] = '\0';
    printf ( "%s\n", buf);
    for ( i=1;  i<= TREE ; i++) {
        relative = 1 ;
        for (j=1;j<=i;j++) {
            memset ( buf , ' ', 128 ) ;
            buf[MIDLE - relative] = '/' ;
            buf[MIDLE + relative] = '\\' ;
            buf[64] = '\0';
            printf ( "%s\n", buf);
            relative++ ;
       }
       memset ( buf , ' ', 128 ) ;
       for ( j=MIDLE-relative+1; j < MIDLE+relative ; j++ )
        buf[j] = '-';
       buf[MIDLE+relative] = '\0';
       printf ( "%s\n", buf);
    }
    memset ( buf , ' ', 128 ) ;
    buf[MIDLE - 1] = '|' ;  buf[MIDLE + 1] = '|' ; buf[MIDLE + 2] = '\0' ;
    if ( TREE > 3 ) j = 3;
    else j = 2 ;
    for ( i=0 ; i < j; i++ )
        printf ( "%s\n", buf) ;

    buf[MIDLE - 1] = '-' ; buf[MIDLE] = '-'; buf[MIDLE + 1] = '-' ; buf[MIDLE + 2] = '\0' ;
    printf ( "%s\n", buf) ;

    return 0 ;


}
