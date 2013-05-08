/*
 by notzed

 build:
  gcc -O3 wc-7.c -lm
 run:
  ./a.out

  Weekend challenge #7 - Cat stairs problem.

  Considering only the last step, it can either be a single or a
  double jump.

  If it is a single jump, then the number of ways to reach the end is
  simply the same as the number of ways to get to that last but one
  step.

  If it is a double jump, then the number of ways to reach the end is
  likewise the same as the number of ways to get to that last but two
  step (ignoring the two-single step case handled above).

  So the total ways to get to the last step is just their sum.

  This can be defined recursively for any location.

   S(n) = S(n-1) + S(n-2)
  where
   S(1) = 1 (only possibility)
   S(2) = 2 (can either two two single jumps or one double jump).

  Which is just the definition for a Fibonnaci number of fib(n+1),
  which has analytical solutions.

  Code implements recursive, loop, and analytical algorithms to the
  limit of patience/precision/space.

 */

#include <sys/time.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

// Patience limit for the recursive thing
#define LIMIT_REC 40
// This is the limit of uint64_t
#define LIMIT_LOOP 91
// 100 is enough to show
#define LIMIT_FIB 100

#define LIMIT 100

// naive recursive implementation
uint64_t jumps_rec(int n) {
	return n <= 2 ? n : jumps_rec(n-2) + jumps_rec(n-1);
}

// obvious loop implementation
uint64_t jumps_loop(int n) {
	uint64_t l1 = 2;
	uint64_t l2 = 1;
	int j;

	if (n <= 2)
		return n;

	for (j=2;j<n;j++) {
		uint64_t ln = l1 + l2;

		l2 = l1;
		l1 = ln;
	}

	return l1;
}

// https://en.wikipedia.org/wiki/Fibonacci_number#Computation_by_rounding
double jumps_fib(int n) {
	return round(pow((1.0 + sqrt(5)) / 2.0, n) / sqrt(5.0));
}

// timing
struct timeval tvs, tve;
static void start(void) {
	gettimeofday(&tvs, NULL);
}
static uint64_t end(void) {
	uint64_t mss, mse;

	gettimeofday(&tve, NULL);

	mss = tvs.tv_sec * 1000000LL + tvs.tv_usec;
	mse = tve.tv_sec * 1000000LL + tve.tv_usec;

	return mse - mss;
}

int main(int argc, char **argv) {
	int i;
	uint64_t rec[LIMIT_REC+1];
	uint64_t loop[LIMIT_LOOP+1];
	double fib[LIMIT_FIB+1];
	uint64_t ms_rec;
	uint64_t ms_loop;
	uint64_t ms_fib;

	start();
	for (i=1;i<=LIMIT_REC;i++)
		rec[i] = jumps_rec(i);
	ms_rec = end();

	start();
	for (i=1;i<=LIMIT_LOOP;i++)
		loop[i] = jumps_loop(i);
	ms_loop = end();

	start();
	for (i=1;i<=LIMIT_FIB;i++)
		fib[i] = jumps_fib(i+1);
	ms_fib = end();

	printf("Steps              Recursive          Non-Recursive               Analytic\n");
	for (i=1;i<=LIMIT;i++) {
		if (i <= LIMIT_REC)
			printf("%4d %22lld %22lld %22.0lf\n", i, rec[i], loop[i], fib[i]);
		else if (i <= LIMIT_LOOP)
			printf("%4d %22c %22lld %22.0lf\n", i, '-', loop[i], fib[i]);
		else
			printf("%4d %22c %22c %22.0lf\n", i, '-', '-', fib[i]);
	}

	printf("\nAlgorithm   Time(s)\n");
	printf(" recursive %3lld.%06lld\n", ms_rec / 1000000, ms_rec % 1000000);
	printf(" loop      %3lld.%06lld\n", ms_loop / 1000000, ms_loop % 1000000);
	printf(" analytic  %3lld.%06lld\n", ms_fib / 1000000, ms_fib % 1000000);

	return 0;
}
