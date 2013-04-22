#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(void)
{
    const unsigned int l = 30;  //needle length
    const unsigned int t = 50; // stripes width
    const unsigned int n = 10000000; //number of needles to be thrown
    unsigned int R = 0; //no of intersections
    unsigned int i=0;

    srand(time(0));

    for (i=0;i<n;i++){
        float x = rand()-RAND_MAX/2;    //get a start on the needle
        float a = rand()/(double)(RAND_MAX)/2*M_PI; //angle of the needle
        float x2 = x + cos(a)*l;    //compute end of needle

        //check if needle cross vertical line (both of ends arn't on the same side of line)
        if ((int)(x/t) != (int)(x2/t) ){
            R++;
        }
    }

    printf("Number of throws: %d\n",n);
    printf("Number of intersections: %d\n",R);
    printf("Estimated Pi = %f\n",2*(double)l*n/((double)t*R));

    return 0;

}

