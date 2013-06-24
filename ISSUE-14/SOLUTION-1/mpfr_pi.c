/*
 2013-06-21 by kantal59 
 License: LGPL
 OLIMEX WPC#14: 
    Compute Pi to the maximal precision you can in relatively real time.
    Tip: Use Leibniz formula and find way to work with very big numbers like hundreds/thousands of digits.
    
 It doesn't compute Pi via an explicit algorithm, the mpfr library(http://www.mpfr.org/) make it better:-)
 The used precision in the computation isn't equal the one of the Pi calculated!
 
 The mpfr lib must be installed, and the header files, too: 
    sudo apt-get install libmpfr-dev libgmp-dev
       
 COMPILE: gcc mpfr_pi.c -lmpfr -lgmp -lm    
 
*/

#include <stdio.h>
#include <math.h>
#include <gmp.h>
#include <mpfr.h>

int main (int argc, char *argv[])
{
  mpfr_t pi;
  
  unsigned long decprec;
  unsigned long bitprec;
 
  if( argc!=2 ){ 
               puts("\nUsage: $> mpfr_pi  decimal_precision  [ >pi.txt ]\n"); 
               decprec=1000; 
  }
  else decprec= strtol( argv[1],NULL,10);
 
  bitprec= ceil( decprec*log2(10));
  printf("Let mpfr calculate Pi using binary precison %ld in computation (decimal prec. was %ld).\n\n", bitprec, decprec);
  
  mpfr_set_default_prec(bitprec);
  mpfr_init( pi);
  mpfr_const_pi( pi, MPFR_RNDN);
  
  mpfr_out_str(stdout, 10, 0, pi, MPFR_RNDN);
  puts("");
  mpfr_clear(pi);
  mpfr_free_cache();
  
  return( 0);
}
