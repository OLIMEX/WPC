/*
 *
 * Weekend Programming Challenge – Week #67 Missing pages in book
 *
 * There is a book and a number of consecutive pages are missing from this book.
 * All we know is that the sum of the page numbers of these pages is 9808.
 * Make code which calculates which are the missing pages and displays the result.
 *
 *  Created: 04.10.2014
 *  Author:  michael koch
 *  email:	 chefkoch.michael@arcor.de
 *
 */

#include <stdio.h>
#include <stdlib.h>

# define DELTA 9808

int main () {
    int front, end;
    int sum;

    front = 0;
    end = 0;
    sum = 0;

    while (DELTA != sum) {
        while (sum < DELTA) {
            end++;
            sum += end;
            }

        while (sum > DELTA) {
            front++;
            sum -= front;
            }

        }
    printf("Missing pages between %i and %i", front, end);
    return 0;
    }