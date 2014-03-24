//compile and link: g++ -o dates dates.cpp
//run: ./dates

#include <iostream>

using namespace std;

struct date
{
  int d ;
  int m ;
  int y ;
};


int main()
{
    date d1 , d2 , diff ;

    cout << "input date1 > date2" << endl ;

    cout << "input day date1 " ;
    cin >> d1.d ;
    if ( d1.d < 0 || d1.d >31 ) {
        cout << "incorrect data " << endl ;
        return 1 ;
    }
    cout << "input month date1 " ;
    cin >> d1.m ;
    if ( d1.m < 0 || d1.m >12 ) {
        cout << "incorrect data " << endl ;
        return 1 ;
    }
    cout << "input year date1 " ;
    cin >> d1.y ;

    cout << "input day date2 " ;
    cin >> d2.d ;
    if ( d2.d < 0 || d2.d >31 ) {
        cout << "incorrect data " << endl ;
        return 1 ;
    }
    cout << "input month date2 " ;
    cin >> d2.m ;
    if ( d2.m < 0 || d2.m >12 ) {
        cout << "incorrect data " << endl ;
        return 1 ;
    }
    cout << "input year date2 " ;
    cin >> d2.y ;

    cout << d1.y<<"."<<d1.m<<"."<<d1.d<< "-"<< d2.y<<"."<<d2.m<<"."<<d2.d<<"=" ;
    if(d1.d>=d2.d)
        diff.d = d1.d - d2.d;
    else   {
        d1.d = d1.d + 30;
        d1.m = d1.m - 1;
        diff.d = d1.d - d2.d ;
     }
    if(d1.m>=d2.m)
        diff.m = d1.m - d2.m;
    else   {
        d1.m = d1.m + 12;
        d1.y = d1.y - 1;
        diff.m = d1.m - d2.m ;
    }
    if ( d1.y < d2.y ) {
        cout << endl << "incorrect data " << endl ;
        return 1 ;
    }
    diff.y = d1.y - d2.y ;
    cout << diff.y<<"."<<diff.m<<"."<<diff.d << endl  ;
    return 0;
}
