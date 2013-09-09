/* In my opinion, goto is evil. */
#include <stdio.h>
int main()
{
    Line: printf("Hello World!\n");
    goto Line;
    return 0;
}
