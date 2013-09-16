/*
 =============================================================================
 Name        : olimex24.c
 Author      : Laurent Haas - Sept 2013 - Tested on Win32 with Cygwin DLL
 Description : Calculates the number of ways you can express positive natural
               number N as sum of positive natural numbers.
               Also called the "partition function".
               Olimex Weekend Programming Challenge – Week #24 – combinatorics
 =============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * Below, application of the Euler's Pentagonal number theorem
 * Check http://www.mathpages.com/home/kmath623/kmath623.htm
 * for details
 *
 * Warning : This function is limited to n <= 416
 * Over 416, consider using a "big numbers" library !
 *
 */

unsigned long long partitions(int n) {
	unsigned long long* p;

	p = (unsigned long long*)malloc((n + 1) * sizeof(unsigned long long));
	if (p == NULL)	// Not enough memory...
		return 0;

	p[0] = 1;

	unsigned long long s = 0;
	int i;

	for (i = 1; i <= n; i++) {
		int j = 1;
		int k = 1;
		s = 0;
		while(j > 0) {
			j = i - (3 * k * k + k) / 2;
			if (j >= 0)
				s = s - (k % 2 ? -1 : 1) * p[j];

			j = i - (3 * k * k - k) / 2;
			if (j >= 0)
				s = s - (k % 2 ? -1 : 1) * p[j];

			k++;
		}
		p[i]= s;
	}

	free(p);
	return s;
}

int main() {
	int n = 0;

	printf("Enter n : ");
	scanf("%d", &n);	// We assume a number between 1 and 416 is entered

	unsigned long long result = partitions(n);

	if (result)
		printf("%llu partitions for %d\n", result, n);
	else
		printf("Buy some RAM...\n");

	return EXIT_SUCCESS;
}
