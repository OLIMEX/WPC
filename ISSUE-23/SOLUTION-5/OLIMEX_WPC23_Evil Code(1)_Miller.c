/* Fullfill memory with letter c. */
#include <stdio.h>

int main()
{
    char *c;
    int i=0;
    while(i>=0)
    {
        c[i++]='c';
        putchar(*c);
    }
    return 0;
}

