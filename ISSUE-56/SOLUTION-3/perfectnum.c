/*
 2014-06-07 by kantal59 
 License: LGPL
 OLIMEX WPC#56: Perfect Numbers
			Perfect Number is a positive integer that is equal to the sum of its proper positive divisors.
			This weekend try to calculate the largest Perfect Number you can and let us know what result did you got?
			
			
			http://en.wikipedia.org/wiki/Perfect_number
			 All even perfect numbers have the form: 	M_p*(M_p+1)/2
			where M_p is a Mersenne prime and hence p must be a prime (but not all number with format 2^p-1 are prime).
			(Odd perfect number is not known yet.)

			The mpfr lib must be installed, and the header files, too: 
		    sudo apt-get install libmpfr-dev libgmp-dev
		    
			COMPILE: gcc -o perfectnum perfectnum.c -lmpfr -lgmp -lm    
			
			Test without the LL-algorithm ( comment out the CHECK directive):
			$	time ./perfectnum 57885161 > rslt.txt
				real	2m35.463s	on a Pentium4 2.8GHz with 2.5GB RAM
				
			The result can be compared with datas on http://www.mersenne.org/primes/ 
 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>
#include <mpfr.h>

//#define CHECK		// check if the result really a perfect number

int main (int argc, char *argv[])
{
  
 long p;
 
 if( argc!=2   || 	(p= strtol( argv[1],NULL,10)) <= 2  ){
 
               puts("\nUsage: $> perfectnum   prime\n"); 
               p=3;
 }
 
 mpfr_set_default_prec( 2*p);		// default binary precision
 
 mpfr_t s;		mpfr_init(s);
 mpfr_t M;		mpfr_init(M);

 mpfr_ui_pow_ui( M, 2, p, MPFR_RNDN);
 mpfr_sub_ui( M, M, 1, MPFR_RNDN);
 
 
#ifdef  CHECK
/*---- LUCAS-LEHMER ALGORITHM
	Determin if 2^p-1 is Mersenne prime, where p must be prime.
	http://en.wikipedia.org/wiki/Lucas%E2%80%93Lehmer_primality_test
*/
	
 mpfr_set_ui(s, 4, MPFR_RNDN);
 unsigned i;
 for( i=0;	i< p-2;		i++){
									mpfr_mul(s, s, s, MPFR_RNDN);
									mpfr_sub_ui( s, s, 2, MPFR_RNDN);
									mpfr_remainder( s, s, M, MPFR_RNDN); 
 }
 int rtcd= mpfr_zero_p(s);

/*---------------------------------------------------------------------*/
#else
 int rtcd=1;
#endif 
 
 if( ! rtcd ){
 		printf("\nMersenne-prime with exponent %lu not found\n", p);
 } 
 else{
 		char *mm="";
 		#ifndef CHECK
 			mm="(\?\?\?)";
 		#endif	
 		printf("\nMersenne-prime %s with exponent %lu is found:\n",mm,p);
 		mpfr_out_str(stdout, 10, 0, M, MPFR_RNDN);
 		
 		mpfr_set(s,M,MPFR_RNDN);
 		mpfr_add_ui(s,s,1,MPFR_RNDN);
 		mpfr_mul(M,M,s,MPFR_RNDN);
 		mpfr_div_ui(M,M,2,MPFR_RNDN);
 		printf("\nThe perfect %s number:\n",mm);
 		mpfr_out_str(stdout, 10, 0, M, MPFR_RNDN);
 		puts(" ");
 }
 
 mpfr_clear(s);		mpfr_clear(M); 
 mpfr_free_cache();
 return( 0);
 
}


