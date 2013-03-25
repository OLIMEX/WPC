From Ian K Rolfe, aka Slothie.

I would have made the x & y elements of the point struct float, but you said integer so.... :)
Its been a while since I've done something "mathy" so it was fun!

Ian

==================

pi@raspberrypi:~/Dev$ cat pointline.c
#include <stdio.h>
#include <math.h>

typedef struct {int x, y; } point;

float distance(point A, point B, point C) {
    float m, b, d;

    /* Stop those pesky divide by zero errors. */
    if (A.x != B.x) {
        /* convert line AB into slope form y = mx + b */
        m = (B.y - A.y)/( B.x - A.x);
        b = A.y - m*A.x;
        /* distance = |Y0 - mX0 -b|/sqrt(m^2+1) */
        d = fabs(C.y - m*C.x - b)/sqrtf(m*m + 1);
    } else {
        d = fabs(C.x - A.x);
    };
    return d;
}

main() {
    /*
     * Points
     */
    point P1 = {1,1}, P2 = {5,5}, P3 = {6,4};
    float d;

    printf("A = (%d,%d)\nB = (%d,%d)\nC = (%d,%d)\n",
            P1.x,P1.y,P2.x,P2.y,P3.x,P3.y);
    d = distance(P1, P2, P3);
    printf("Distance = %f\n", d);
    P2.x = P1.x;
    printf("A = (%d,%d)\nB = (%d,%d)\nC = (%d,%d)\n",
            P1.x,P1.y,P2.x,P2.y,P3.x,P3.y);
    d = distance(P1,P2,P3);
    printf("Distance = %f\n", d);
}

pi@raspberrypi:~/Dev$ gcc pointline.c -o pointline -lm
pi@raspberrypi:~/Dev$ ./pointline 
A = (1,1)
B = (5,5)
C = (6,4)
Distance = 1.414214
A = (1,1)
B = (1,5)
C = (6,4)
Distance = 5.000000
pi@raspberrypi:~/Dev$ 
