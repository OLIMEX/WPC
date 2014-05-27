/*
 Euclid proved that [2**(p−1)]*(2p−1) is an even perfect number whenever 2p−1 is prime


Mersenne Number
 2, 3, 5, 7, 13, 17, 19, 31, 61, 89, 107, 127, 521, 607, 1279, 2203, 2281, 3217, 4253, 4423, 9689, 9941,
 11213, 19937, 21701, 23209, 44497, 86243, 110503, 132049, 216091, 756839, 859433, 1257787, 1398269,
 2976221, 3021377, 6972593, 13466917 , 20996011, 24036583, 25964951, 30402457

 gcc -o perfect perfect.c
*/

#include <stdio.h>
#define MN 13
unsigned mPrimes[MN] = {2,3,5,7,13,17,19,31,61,89,107,127,521};
signed k, number[400];
void doubleN(void) {
     unsigned i, carry = 0, temp;

    for (i = 0; i < k; i++) {
        temp = number[i] * 2 + carry;
        number[i] = temp % 10;
        carry = temp / 10;
    }
    if (carry > 0)
        number[k++] = carry;
}


void print(void)
{
    unsigned i;
    for (i = k; i > 0; i--)
        printf("%u", number[i-1]);
    printf("\n");
}

void perfect(unsigned s, unsigned m)
{
    unsigned i;
    k = 1; number[0] = 1;
    for (i = 0; i < m; i++)
        doubleN();
    number[0]--;
    for (i = 0; i < m - 1; i++)
        doubleN();
    printf("%2u-perfect number id = ", s);
    print();
}
int main(void) {
    unsigned i;
    for (i = 1; i <= MN; i++)
        perfect(i, mPrimes[i - 1]);
return 0;
}
