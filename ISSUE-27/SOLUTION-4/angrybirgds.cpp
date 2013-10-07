#include <iostream>
#include <cmath>


using namespace std;

int main()
{
double x ,  y , m , t, k , g ,t0 , v0x ,v0y, a0x , a0y;
double f_initial, angle_initial ;

cout << "input angke  " ;
cin >> angle_initial ;
cout << "input initial forse  " ;
cin >> f_initial ;


cout << "input masa bird  " ;
cin >> m  ;

cout << "input coef resit air   " ;
cin >> k  ;

g = 9.81 ;


v0x = (f_initial / m) * cos(angle_initial) ;
v0y = (f_initial / m) * sin(angle_initial) ;
a0x = (f_initial / m) * (f_initial / m) * k  /m  * cos(angle_initial) ;
a0y = (f_initial / m) * (f_initial / m) * k  /m  * sin(angle_initial) ;
t0 = v0y / (g + a0y) ;
y = 1;
for ( t =1 ; y > 0.0001 ;t++) {
    x = v0x * t - a0x * t * t / 2 ;
    if ( t < t0 )
        y = v0y * t - (g + a0y )* t * t /2 ;
    else
        y = v0y * t - (g - a0y )* t * t /2 ;
    cout << "x=" << x << "," <<"y="<<y << endl ;
    }

return 0;
}

