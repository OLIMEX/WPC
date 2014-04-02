// for run program use : geometry < in.txt

#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;
const double PI = 3.14159265 ;

double angle ( double x , double y );
int main()
{
    double x1,y1 /*A*/,  x2,y2 /*B*/,  x3,y3 /*C*/,  x,y /*center of the circle*/ ;
    double a,b,c ; // a - angle A , b angle B , c angle C

    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 ;
    cout << "A("<<x1<<","<<y1<<") " ;
    cout << "B("<<x2<<","<<y2<<") " ;
    cout << "C("<<x3<<","<<y3<<")" << endl  ;

    if ( (x3 - x1)*(y2 - y1) == (x2 - x1)*(y3 - y1)) {
        cout << "the point's is collinear" << endl ;
        return 0 ;
    }

    // compute center of the circle described about the triangle ABC
    x = (y2-y1)*(x3*x3-x1*x1+y3*y3-y1*y1)-(y3-y1)*(x2*x2-x1*x1+y2*y2-y1*y1) ;
    x = x / ( 2 * ((x3-x1)*(y2-y1)-(x2-x1)*(y3-y1)));

    y = (x2-x1)*(x3*x3-x1*x1+y3*y3-y1*y1)-(x3-x1)*(x2*x2-x1*x1+y2*y2-y1*y1) ;
    y = y / ( 2 * ((y3-y1)*(x2-x1)-(y2-y1)*(x3-x1)));

    //cout << "coord cneter " << x << "," << y << endl ;

    // translate coord system in center of the circle described about the triangle ABC
    // new coord A, B , C
    x1 -= x;  y1 -= y;
    x2 -= x;  y2 -= y;
    x3 -= x;  y3 -= y;
    // change with the polar coordinate system
    // for  points A,B,C , r is equal
    // calculate the angle
    a = angle(x1,y1) ; // point A
    b = angle(x2,y2) ; // point B
    c = angle(x3,y3) ; // point C

    if (a < b && a < c  ) {
        if ( b < c )
            cout << "the points are counter clockwise" << endl ;
        else
            cout << "the points are  clockwise" << endl ;
        return 0 ;
    }

    if (a > b && a < c  ) {
        cout << "the points are  clockwise" << endl ;
        return 0 ;
    }

    if (a > c && a < b  ) {
        cout << "the points are counter clockwise" << endl ;
        return 0 ;
    }

    if (a > b && a > c  ) {
        if ( b > c )
            cout << "the points are counter clockwise" << endl ;
        else
            cout << "the points are  clockwise" << endl ;
        return 0 ;
    }
    return 0;
}

double angle ( double x , double y ) {
    if ( x > 0 && y > 0 )   // I
        return atan ( y / x ) ;

    if ( x < 0 && y > 0 )   // II
        return ( atan (abs(x) / y  ) + PI /2 )  ;

    if ( x < 0 && y < 0 )   // III
        return (atan ( abs(y) /abs(x)) + PI ) ;

    if ( x > 0 && y < 0 )   // IV
        return (atan ( x /abs(y)) + PI*3/2) ;

    if ( x == 0 && y > 0 )
        return PI /2 ;

    if ( x > 0 && y == 0 )
        return 0;

    if ( x < 0 && y == 0 )
        return PI ;

    if ( x == 0  && y < 0 )
        return PI * 3 / 2 ;

    return -1 ;  // panic ERROR

}
