#include <stdio.h>

int main(void)
{
    int a = 127, b = 1023;

    long double val = (long double)a/b;

    unsigned int i = 2;
    while(1){
        long double t = (long double)1/i;

        if ((val - t)>0){
            printf("%d, ",i);
            val -= t;
        } else if ((val -t) == 0){
            printf("%d\n",i);
            break;
        }

        if (i>= 16777216)
            break;

        i++;
    }

    return 0;
}

