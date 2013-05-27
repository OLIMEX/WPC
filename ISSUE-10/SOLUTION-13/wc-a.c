#include <stdio.h>
#include <stdlib.h>

/*

Works by finding and removing the largest remaining multiple of the
numerator in the common demoninator until exhausted.

 - notzed

compile: gcc -O wc-a.c
run: ./a.out a b

examples:

$ ./a.out 6 7
input : 6/7
output: 2, 3, 42
input~: 0.857143
check~: 0.857143
$ ./a.out 1972 197987
input : 1972/197987
output: 116, 986, 4292, 18241, 36482, 155179, 310358, 2638043, 11483246, 195215182
input~: 0.009960
check~: 0.009960
$

*/

int main(int argc, char **argv) {
	if (argc < 3) {
		printf("Usage: %s a b\n", argv[0]);
		return 1;
	}

	int a = atoi(argv[1]);
	int b = atoi(argv[2]);

	if (a <=0 || b <= 0) {
		printf("both a and b must be non-zero and positive\n");
		return 1;
	}

	// scaled by a/a
	int n = a*a;
	int d = a*b;

	printf("input : %d/%d\n", a, b);
	printf("output: ");

	double sum = 0;

	while (n > 0) {
		int i;

		// Find biggest 1/i which fits
		for (i=1;d/i> 0;i+=1) {
			int s = d / i;
			int r = d % i;

			if (r== 0 && s <= n) {
				if (n < a*a)
					printf(", ");
				printf("%d", i);
				fflush(stdout);
				n -= s;
				sum += 1.0 / i;
				break;
			}

		}
	}
	printf("\n");

	printf("input~: %f\n", (double)a/b);
	printf("check~: %f\n", sum);

	return 0;
}
