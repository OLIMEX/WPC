#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    while(1)
    {
        bool a;
        a=!a;
        printf("Infinite Output: %u \n",  a);
    }
    return 1;

}
