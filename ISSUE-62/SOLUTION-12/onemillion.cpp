//for compile& link: g++ -o onemillion  onemillion.cpp
//for run: ./onemillion


#include <iostream>

using namespace std;

int main()
{
    int  x=1 , y=1000000 ;

    while ( !(y%5) ) {
        x*=5;
        y /= 5;
    }
    cout << x << '*'<< y << '=' << x*y << endl ;
    return 0;
}
