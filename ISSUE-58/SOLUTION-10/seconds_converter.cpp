// for compile & link : g++ -o seconds_converter  seconds_converter.cpp
// for run: ./seconds_converter


#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    char in[128] ;
    cout << "input date Day/Month/Year : " ;
    cin >> in ;
    int Day , Month , Year ;
    sscanf (in , "%d/%d/%d", &Day , &Month , &Year ) ;
    if ( Month <= 0 || Month >= 13 ) {
        cout << "incorrect date" << endl ;
        return 1;
    }

    if ( Year < 0  ) {
        cout << "incorrect date" << endl ;
        return 1;
    }

    int M[] = {0,31,28,31,30,31,30,31,31,30,31,30,31} ;
    if ( Year > 0 && !(Year % 4) )
        M[2] = 29 ;


    if ( Day <=0 || Day >= (M[Month]+1) ) {
        cout << "incorrect date" << endl ;
        return 1;
    }

    int Y ;
    if ( Year > 0 )
        Y = Year-1;
    else
        Y =  Year ;

    long long  Seconds = 0 ;

    for ( int i = 0 ;  i < Y ; i++ ) {
        if ( i % 4 && i > 0 )
            Seconds += 60 * 60  * 24  * 365 ;
        else
            Seconds += 60 * 60  * 24  * 366 ;
    }

    int MM = Month - 1 ;

    for ( int i = 1 ; i <= MM ; i++ ) {
        Seconds += 60 * 60  * 24  * M[i] ;
    }


    Seconds += 60 * 60  * 24  * Day ;

    cout << "Seconds = " << Seconds << endl;



    return 0;
}
