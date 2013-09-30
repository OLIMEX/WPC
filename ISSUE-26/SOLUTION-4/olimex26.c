/*

 ==================================================================================================
 Name        : olimex26.c
 Author      : Laurent Haas - Sept 2013 - Tested on Win32 with Cygwin DLL
 Description : Write code which checks if four points form a square.
               Olimex Weekend Programming Challenge – Week #26 – Square
 URL         : http://olimex.wordpress.com/2013/09/27/weekend-programming-challenge-week-26-square/
 ==================================================================================================

 */

#include <stdio.h>

typedef struct Point {
   float x;
   float y;
} Point;

#define EQUAL(A, B)	((A.x == B.x) && (A.y == B.y))	// Vector / point equality

int main() {
    Point A, B, C, D;

    A.x = 0;    // Point A
    A.y = 0;

    B.x = 0;    // Point B
    B.y = 1;

    C.x = 1;    // Point C
    C.y = 1;

    D.x = 1;    // Point D
    D.y = 0;

    // Compute the "center" of these 4 points

    Point center;

    center.x = (A.x + B.x + C.x + D.x) / 4;
    center.y = (A.y + B.y + C.y + D.y) / 4;

    // Compute the vector v1 : A to the center

    Point v1;

    v1.x = center.x - A.x;
    v1.y = center.y - A.y;

    // Compute the vector v2 which is v1 rotated by 90 degrees

    Point v2;

    v2.x = - v1.y;
    v2.y = v1.x;

    // Now compute the three vectors v3, v4 and v5 :
    // Center + v1, Center + v2 and Center - v2.

    Point v3, v4, v5;

    v3.x = center.x + v1.x;
    v3.y = center.y + v1.y;

    v4.x = center.x + v2.x;
    v4.y = center.y + v2.y;

    v5.x = center.x - v2.x;
    v5.y = center.y - v2.y;

    // If these 3 vectors point to the 3 points B C D, so ABCD form a square

    int isASquare;

    isASquare = ( (EQUAL(v3, B) && EQUAL(v4, C) && EQUAL(v5, D)) ||
        (EQUAL(v3, C) && EQUAL(v4, D) && EQUAL(v5, B)) ||
        (EQUAL(v3, D) && EQUAL(v4, B) && EQUAL(v5, C)) ||
        (EQUAL(v3, B) && EQUAL(v4, D) && EQUAL(v5, C)) ||
        (EQUAL(v3, C) && EQUAL(v4, B) && EQUAL(v5, D)) ||
        (EQUAL(v3, D) && EQUAL(v4, C) && EQUAL(v5, B)) );

    printf("ABCD is%s a square.\r\n", (isASquare ? "" : " not"));

    return 0;
}
