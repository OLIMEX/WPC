/*
 * OLIMEX WEEKEND PROGRAMMING CHALLENGE ISSUE #7
 * author: Hanspeter Portner
 * language: C
 * filename: cat_climbs_stair.c
 * compilation:
 *  >> gcc -O3 -o cat_climbs_stair cat_climbs_stair.c
 * usage:
 *  >> ./cat_climbs_stair 50
 */

#include <stdio.h>
#include <stdint.h>

void choice (uint64_t *p, uint64_t n) {
	if (n <= 1ULL)
		(*p)++;
	else {
		choice (p, n - 1ULL);
		choice (p, n - 2ULL);
	}
}

int main (int argc, char **argv) {
	uint64_t n = atoi (argv[1]);
	uint64_t p = 0ULL;
	if (n)
		choice (&p, n);
	printf ("%llu\n", p);
	return 0;
}
