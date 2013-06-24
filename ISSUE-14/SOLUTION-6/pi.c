// for compile  gcc -o pi pi.c -lgmp
// for run ./pi


#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#define LIMIT 10000

int main(void) {


  int i ;
  char buf[4096] ;
  mpf_t x, y , result ;
  mpf_set_default_prec(LIMIT);
  mpf_init ( x );
  mpf_init ( y );
  mpf_init (result) ;




   mpf_set_str(result, "1" , 10 );

   for ( i = 1 ; i < LIMIT ; i++ ) {
     sprintf ( buf , "%d" , (2*i + 1) ) ;
     mpf_set_str(x, buf , 10 );
     mpf_ui_div (y, 1, x) ;
     if ( i % 2 ) {
       mpf_sub ( x , result , y ) ;
       mpf_set (result , x) ;
     }
     else {
       mpf_add ( x , result , y ) ;
       mpf_set (result , x) ;
     }
   }

   mpf_mul_ui (x, result, 4 )  ;


   printf("\n pi = " ) ;
   mpf_out_str (stdout , 10, 0, x) ;
   printf ("\n") ;


   mpf_clear (x);
   mpf_clear (y);
   mpf_clear (result);

   return EXIT_SUCCESS;

}

