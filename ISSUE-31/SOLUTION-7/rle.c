#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void cript ( char* ) ;
void decript ( char *) ;

int main(int argc , char *argv[])
{

    if ( argc < 3 ) {
        printf("use:rle {c|d} string \n" ) ;
        return 0;
    }

    if ( *argv[1] == 'c' || *argv[1] == 'C' ) {
        cript ( argv[2] ) ;
        return 0;
    }

    if ( *argv[1] == 'd' || *argv[1] == 'D' ) {
        decript ( argv[2] ) ;
        return 0 ;
    }
    printf("use:rle {c|d} string \n" ) ;
    return 0 ;
}


void cript ( char* txt ) {
char *p ,*mp ;
int mc , pc , i ;

for ( p = txt , mc = 0 , pc = 0  ; *p ; p++ ) {
   if ( *p == *(p+1)  ) {
      if ( mc > 0  ) {
         printf ( "-%d",mc) ;
         for ( i=0;i<mc;i++)  printf ( "%c",*mp++) ;
         mc = 0 ;
       }
       ++pc ;
    }
    else {
        if ( pc > 0 ) {
           printf ( "%d%c",++pc,*p) ;
           pc = 0 ;
        }
        else {
           if ( mc == 0 )
             mp=p ;
           ++mc ;
        }
    }
}

if ( mc > 0  ) {
 printf ( "-%d",mc) ;
 for ( i=0;i<mc;i++)  printf ( "%c",*mp++) ;
}
return  ;
}


void decript ( char *txt ) {
char *p ;
int sign , cnt , rp;
char buf[8] ;

for ( p = txt , sign = 1 , cnt = 0   ; *p ; ++p ) {
    if ( *p == '-' ) {
        sign = -1 ;
        continue ;
    }
    if ( isdigit ( *p)) {
        buf[cnt++] = *p ;
        continue ;
    }
    buf[cnt] = 0 ;
    rp = atoi ( buf ) ;
    if ( sign == -1 ) {
        while ( rp-- )
            printf ( "%c", *p++ ) ;
        --p ;
    } else {
        while ( rp-- )
            printf ( "%c", *p ) ;
    }
    sign = 1 ; cnt = 0 ;
} // end of while
return ;
}
