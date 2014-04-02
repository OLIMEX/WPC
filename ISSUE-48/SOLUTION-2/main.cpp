#include <iostream>

using namespace std;
/* Weekend Programming Challenge – Week #48 Geometry
Problem:
Let have three points A(x,y), B(x,y), C(x,y). Make code
which prints if A->B->C sequence makes clockwise,
counter clockwise turn, or A,B,C stay in one line.
Idea: Form the determinant which gives twice area of triangle.
2*area=(bx-ax)*(cy-ay)-(by-ay)*(cx-ax);
If area > 0 then a-b-c is counterclockwise.
If area < 0, then a-b-c is clockwise.
If area = 0, then a-b-c are on the same line. */



int main()
{
    float ax,ay,bx,by,cx,cy,area;

    cout<<"Enter coordiates of A (ax,ay) dot:"<<endl;
    cin>>ax>>ay;
    cout<<"Enter coordiates of B (bx,by) dot:"<<endl;
    cin>>bx>>by;
    cout<<"Enter coordiates of C (cx,cy) dot:"<<endl;
    cin>>cx>>cy;
    area=(bx-ax)*(cy-ay)-(by-ay)*(cx-ax);
   // area=2*area;
    if(area>0) cout<<"A-B-C is counterclockwise.";
    else if(area<0) cout<<"A-B-C is clockwise.";
    else cout<<"A-B-C stay in one line.";


    return 0;
}
