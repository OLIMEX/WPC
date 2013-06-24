#include <stdio.h>
#include <stdlib.h>

int main()
{
    double i=1.0;
    double j=1.0;
    double Pi=1.0;
    double temp=0.0;

    while(i<1e9)
    {
        j=-j;
        i=i+2.0;
        temp=j/i;
        Pi=Pi+temp;
    }

    printf("%1.16lf\n", Pi*4.0);
    /* Pi=3.1415926555892577 */

    system("pause");
    return 0;
}
