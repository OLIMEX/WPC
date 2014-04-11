#include <iostream>
#include <math.h>
#define PI (3.141592653589793)



using namespace std;

//circle midpoint algorithm (integer based)
  void CircleCoordinates(int x0, int y0, int radius)
{
  int x = radius, y = 0;
  int radiusError = 1-x;

  while(x >= y)
  {
    cout<<x + x0<<" "<< y + y0<<endl;
    cout<<y + x0<<" "<< x + y0<<endl;
    cout<<-x + x0<<" "<<y + y0<<endl;
    cout<<-y + x0<<" "<< x + y0<<endl;
    cout<<-x + x0<<" "<< -y + y0<<endl;
    cout<<-y + x0<<" "<< -x + y0<<endl;
    cout<<x + x0<<" "<< -y + y0<<endl;
    cout<<y + x0<<" "<< -x + y0<<endl;
    y++;
    if (radiusError<0)
    {
      radiusError += 2 * y + 1;
    } else {
      x--;
      radiusError+= 2 * (y - x + 1);
    }
  }
}


void dots(int h, int  k, int r) {
    double theta,x,y;


    double step = 2*PI/20;

    for(  theta=0;  theta < 2*PI;  theta+=step)
     {
        x = h + r*cos(theta);
        y = k + r*sin(theta);
        cout<<"("<<x<<","<<y<<")"<<endl;

     }

}

int main()
{
    int x0,y0,radius=50;

    do{
    cout<<"Limits of x0 and y0 are [25,75]!";
    cout<<"Insert x0: ";
    cin>>x0;
    cout<<"Insert y0: ";
    cin>>y0;
    }while(!((x0<=75 & x0>=25 ) &(y0<=75 & y0>=25  )));

    //CircleCoordinates(x0,y0,radius);
    dots(x0,y0,radius);
    return 0;
}
