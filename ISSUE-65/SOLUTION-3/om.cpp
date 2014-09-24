#include <iostream>

using namespace std;

int main()
{
    const double roCU = 0.0168;
    double width;
    cout << "input width  in units: (mm) "  ;
    cin >>  width;

    double thickness;
    cout << "input thickness  in units: (mm) "  ;
    cin >>  thickness;

    double length;
    cout << "input length  in units: (mm) "  ;
    cin >>  length;

    int number;
    cout << "input number of vias  "  ;
    cin >>  number;

    double  plating ;
    cout << "input  plating  of vias  "  ;
    cin >>   plating ;

    double drill  ;
    cout << "input drill diameter   in units: (mm) "  ;
    cin >>  drill ;


    cout << width << ";" << thickness << ";" << length << ";" << number << ";" << plating << ";"<< drill << ";" << roCU << endl ;


    double R , r1 , r2   ;

    R = roCU * length  / (thickness * width * 1000 ) ;
    double l = 3.14 * drill / 2 ;
    r1 =  roCU * l  / (thickness * width * 1000 ) ;
    r2 =  roCU * drill / (plating * (drill * drill / 4.0 * 3.14) * 1000 * 1000 ) ;
    R = R  + number * ( r1 * r1 * r2 ) / ( r1*r1 + 2*r1*r2) ;

    cout << "Om resistance = " << R << endl ;


    return 0;
}
