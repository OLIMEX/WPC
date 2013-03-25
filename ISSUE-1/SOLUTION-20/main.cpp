#include <iostream>
#include <cmath>

using namespace std;

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    int x;
    int y;
    int c;
} Line;

// calculates line equation from two given points
Line pointsToLine(Point A, Point B)
{
    Line d;
    d.x = B.y - A.y;
    d.y = -1*(B.x - A.x);
    d.c = A.y * B.x - A.x * B.y;

    return d;
}

// calculates distance from point to line
float distance(Point C, Line d)
{
    return abs((float)(d.x * C.x + d.y * C.y + d.c) / sqrt(d.x * d.x + d.y * d.y));
}

int main()
{
    Point A, B, C;
    cout << "Enter point A coordinates: ";
    cin >> A.x >> A.y;
    cout << "Enter point B coordinates: ";
    cin >> B.x >> B.y;
    cout << "Enter point C coordinates: ";
    cin >> C.x >> C.y;
    cout << "Distance is " << distance(C, pointsToLine(A,B));
    return 0;
}
