/* Isogram.c -- Outputs the longest isogram inside a file or stdin
 *
 * To compile: gcc isogram.c -O2 -o isogram
 * NOTE: Needs 32bit+ int size. It won't work on anything less...
 *
 */
#include <stdio.h>

int main(int argc, char *argv[]) {
	FILE *fp;
	int flags; /* Using an array of chars would make it work on 8bit and 16bit machines...but it would be slower, and half the fun! :) */
	char curr_isogram[27];
	char max_isogram[27];

	int i,c,bit,maxlen,currlen,skipping,is_letter;

	if (argc == 1) fp = stdin;
	else if (argc != 2) {
		fprintf(stderr, "Usage: isogram [<file>]\n");
		return 1;
	}
	else if ((fp = fopen(argv[1],"rb")) == NULL) {
		fprintf(stderr, "isogram: cannot open file \"%s\"\n", argv[1]);
		return 1;
	}

	currlen = maxlen = skipping = 0;

	while ((c = getc(fp)) != EOF) {
		c &= 223; /* to uppercase */
		is_letter = (c >= 65 && c <= 90);
		if (skipping) {
			if (is_letter) continue; /* skip until first non-letter found */
			skipping = currlen = flags = 0;
		}
		else if (is_letter) {
			bit = 1 << (c-65);
			if (flags & bit) skipping = 1;
			else {
				flags |=  bit;
				curr_isogram[currlen++] = (char) c;
			}
		}
		else {
			if (currlen && currlen >= maxlen) { /* ...or simply (currlen > maxlen) if you want just the first longest isogram (less verbose output) */
				curr_isogram[currlen] = 0;
				fprintf(stderr, "Found isogram %s (%d letters)\n", curr_isogram, currlen);
				for (i=0;i<=currlen;i++) max_isogram[i] = curr_isogram[i];
				maxlen = currlen;
			}
			currlen = flags = 0;
		}
	}

	if (maxlen) printf("%s\n", max_isogram);
	else fprintf(stderr, "Blank file\n");

	return 0;
}
