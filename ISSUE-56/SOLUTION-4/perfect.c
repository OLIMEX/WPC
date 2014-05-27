/*
 * Olimex WPC # 56 - Find perfect numbers
 *
 * Compile: gcc perfect.c -lgmp
 *
 */

#include <stdio.h>
#include <gmp.h>

void main()
{
  mpz_t x;
  mpz_init(x);
  mpz_t x1;
  mpz_init(x1);
  mpz_t n;
  mpz_init(n);
  mpz_t ex1;
  mpz_init(ex1);
  mpz_t ex2;
  mpz_init(ex2);
  mpz_t ex3;
  mpz_init(ex3);
  mpz_t base;
  mpz_init(base);
  mpz_set_ui(base,2);
  mpz_t mod;
  mpz_init(mod);
  mpz_set_ui(mod,1);
  mpz_t perf;
  mpz_init(perf);
  int cnt = 0;

  while(1)
  {
    mpz_nextprime(n, x);
    mpz_swap(n,x);
    mpz_pow_ui(ex1, base, mpz_get_ui(x)); // ex1 = 2^x
    mpz_sub_ui(ex2, ex1, 1);              // ex2 = 2^x - 1
    if (mpz_probab_prime_p(ex2,25))
    {
      mpz_sub_ui(x1, x, 1);                  // x1 = x - 1
      mpz_pow_ui(ex3, base, mpz_get_ui(x1)); // ex3 = 2^(x-1)
      mpz_mul(perf, ex3, ex2);
      gmp_printf("Result number %d for p = %Zd\n", ++cnt, x);
      gmp_printf("%Zd\n", perf);
      printf("***\n");
      fflush(NULL);
    }
  }
}
