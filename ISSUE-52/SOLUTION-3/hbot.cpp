// for compile and link : g++ -o hbot hbot.cpp
// for run :./hbot

#include <iostream>

using namespace std;

int main()
{
    double X , Y , R ;
    double A , B ;   // motors angle

    cout << "input coord X of point:" ;
    cin >> X ;
    cout << "input coord Y of point:" ;
    cin >> Y ;
    cout <<  "motor shaft radius:" ;
    cin >> R ;
    if ( R <= 0.1 ) return 1 ;
    A=0.0 ; B=0.0;
    if ( X > 0 )  { //move left horizontal, I / IV quadrant
        A =  X / R ;
        B =  X / R ;
    }

    if ( X < 0 )  { //move right horizontal, II / III quadrant
        A =  X / R ;
        B =  X / R ;
    }

    cout << "moving X , angle motor A = " ;
    if ( A > 0 )
        cout << A << " radians clockwise" << endl ;
    else
        cout << -A << " radians anticlockwise " << endl ;
    cout << "moving X , angle motor B = " ;
    if ( B > 0 )
        cout << B << " radians clockwise" << endl ;
    else
        cout << -B << " radians anticlockwise " << endl ;

    A=0.0 ; B=0.0;
    if ( Y > 0 )  { //move up , I / II quadrant
        A =  -Y / R ;
        B =   Y / R ;
    }
    if ( Y < 0 )  { //move down horizontal, III / IV quadrant
        A = -Y / R ;
        B =  Y / R ;
    }

    cout << "moving Y , angle motor A = " ;
    if ( A > 0 )
        cout << A << " radians clockwise" << endl ;
    else
        cout << -A << " radians anticlockwise " << endl ;

    cout << "moving Y , angle motor B = " ;
    if ( B > 0 )
        cout << B << " radians clockwise" << endl ;
    else
        cout << -B << " radians anticlockwise " << endl ;

    return 0;
}
