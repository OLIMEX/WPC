#include <stdio.h>

int main(void) {

    unsigned int N = 2;

    printf("Enter a Number : ");
    scanf("%d", &N);

    unsigned answer = 2 * N * N + 7;
    if (N % 2 == 0)
        answer += 1;
    else
        answer -= 1;

    answer /= 8;

    printf("Answer: %d\n", answer);
    return 0;
}

