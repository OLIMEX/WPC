#include <stdio.h>

#include <math.h>


typedef struct {

    int x;

    int y;

} point_t;


double distance(int x1,int y1,int x2,int y2,int x3,int y3){

    double a,b,res;

    if (x1 == x2 && y1 == y2){

        //A and B are the same

        res = -1;

    } else if (x1 == x2){

        //vertical line

        res = abs(x3 - x2);

    } else {

        //all other lines

        a = (double)(y2 - y1)/(x2 - x1);

        b = (x1*y2 - x2*y1)/(x1 - x2);

        res = fabs(a*x3 - y3 + b)/sqrt(a*a + 1);

    }


    return res;

}

int main(void)

{

    point_t A = {1,2};

    point_t B = {3,3};

    point_t C = {3,6};


    double result = distance(A.x,A.y,B.x,B.y,C.x,C.y);


    if (result != -1)

        printf("Distance: %f\n",result);

    else

        printf("An infinite number of lines passing through" \

               "the points A and B, I can not give a straight answer.\n");


    return 0;

}
