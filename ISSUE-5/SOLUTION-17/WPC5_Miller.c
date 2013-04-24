#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
	double l=0.0, t=0.0;
	int n=0, h=0, count=0;	
	double x=0.0, angle=0.0;
	double Pi;
	
	printf("Input length of the needle   l:\n");
	scanf("%lf", &l);
	printf("Input width of the scripts   t:\n");
	scanf("%lf", &t);
	printf("Input number of needles to be thrown   n:\n");
	scanf("%d", &count);
	n=count;
	printf("\nl=%lf\nt=%lf\nn=%d\n", l, t, n);
	
	srand(time(NULL));  /* Each time with different random seed. */
    while(count--)
	{	
	   x=(double)((t/2)*rand()/(RAND_MAX+1.0));    /* Random value of x between 0~t/2 */
	   angle=(double)((90.0)*rand()/(RAND_MAX+1.0)); /* Random angle below 0~90 */	
	   if(x<(l/2*(sin(angle*3.1415926/180))) || x==(l/2*(sin(angle*3.1415926/180))))
	   h++;
    }

    printf("\nn=%d   h=%d\n", n, h);
    if(l<t || l==t)
        {
            Pi=(2*l*n)/(t*h); /* Short case */
        }
    else
        {
            Pi=(2*n*(2*l-sqrt(l*l-t*t)-t*(1/sin(t/l))+t*(1/cos(t/l))-l*sqrt((1-(t*t)/(l*l)))))/((h-n)*t);
            /* Long case calculated by the formula when l > t but it seems the result is not close to Pi=3.1415......??? */
        }
    printf("\nPi=%lf\n\n", Pi);	
	system("pause");
}
