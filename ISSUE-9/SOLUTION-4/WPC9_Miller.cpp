// OLIMEX Weekend Programming Challenge Issue-9  WPC9
// Problem:
//          Let have N (3..100) points with X,Y coordinates. Make code which checks if there is circle which to
//          pass though all of them.
// Language: C++
// Date: 19/05/2013
// Miller Wang


// Introduction:
// 1. With three points we have fixed circle(circumcircle) if these three points are not in the same line.
// 2. This program gets three points first from user and judge whether those three points are in the same
//    line at the beginning.
//    If it is, then return False, no such circle exists.
//    And if not, calculate value of (x) x coordinate, (y) y coordinate and (r) radius of the fixed circle.
// 3. Get the fourth, fifth until Nth x and y coordinates and judge each time one point to check
//    whether distance between center point (x,y) and Pn(Pn.x, Pn.y) is close to 0.0000.
//    If it is, then return True. Point Pn is on the circle. Repeat the process until Point N.
//    In case we found Point N (Pn.x, Pn.y) is on the circle, then return True. The circle exists.


#include <iostream>
#include <cmath>
#include <stdlib.h>
using namespace std;

// Define Point class includes member x and y as x and y coordinates.
class Point
{
    public:
        Point();
        double x;
        double y;
};

//Initialize value of x and y.
Point::Point():x(0.0),y(0.0)
{}

int main()
{
    //x, y, r as x coordinate, y coordinate and radius of the circle.
    double x, y, r;
    //i as loop variant, N as total points to test 3 <= N <= 100.
    int i, N;
    //flag to judge whether there is such circle exists.
    bool flag=false;
    cout<<"Input N points to test 3 <= N <= 100:"<<endl;
    cin>>N;
    //Creat Point P1, P2, P3, Pn. Point Pn will be used for > 3 points.
    Point P1, P2, P3, Pn;
    cout<<"Input three coordinates first:"<<endl;
    cin>>P1.x>>P1.y>>P2.x>>P2.y>>P3.x>>P3.y;
    // Judge whether x coordinate and y coordinate of the three points are close to 0.000000.
    if (((abs(P1.x-P2.x)<0.000001) && (abs(P1.x-P3.x)<0.0000001)) ||  ((abs(P1.y-P2.y)<0.000001) && (abs(P1.y-P3.y)<0.0000001)))
        {
            flag=false;
        }
    else
        {
            flag=true;
            // x, y coordinate of fixed circle calculated by formula which the distance from center point (x, y) to P1(P1.x, P1.y), P2(P2.x, P2.y) and P3(P3.x, P3.y) is the same.
            x=((P2.y-P1.y)*(P3.y*P3.y-P1.y*P1.y+P3.x*P3.x-P1.x*P1.x)-(P3.y-P1.y)*(P2.y*P2.y-P1.y*P1.y+P2.x*P2.x-P1.x*P1.x))/(2*(P3.x-P1.x)*(P2.y-P1.y)-2*((P2.x-P1.x)*(P3.y-P1.y)));
            y=((P2.y-P1.x)*(P3.x*P3.x-P1.x*P1.x+P3.y*P3.y-P1.y*P1.y)-(P3.x-P1.x)*(P2.x*P2.x-P1.x*P1.x+P2.y*P2.y-P1.y*P1.y))/(2*(P3.y-P1.y)*(P2.x-P1.x)-2*((P2.y-P1.y)*(P3.x-P1.x)));
            // When we have center point (x, y), we can calculate radius of the circle.
            r= sqrt((P1.x-x)*(P1.x-x)+(P1.y-y)*(P1.y-y));
            // Judege each time one point from the fourth point to Point N.
            for (i=4; i<=N; i++)
            {
                cout<<"Input coordinates of point "<<i<<":"<<endl;
                cin>>Pn.x>>Pn.y;
                if (sqrt((Pn.x-x)*(Pn.x-x)+(Pn.y-y)*(Pn.y-y)) - r < 0.0001)
                    flag=true;
                else
                {
                    //Found any point is not on the circle, end the loop immediately.
                    flag=false;
                    break;
                }
            }
        }
    
    if (flag==true)
        cout<<"There is a circle pass through all points."<<endl;
    else
        cout<<"There is not a circle pass through all points."<<endl;

    system("pause");
    return 0;
}

