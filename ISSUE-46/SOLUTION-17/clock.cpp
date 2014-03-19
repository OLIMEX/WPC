#include <iostream>

using namespace std;

int main()
{   int h , m ;
    double   t  ;
    int cross_h[12] , cross_m[12] , cross_s[12];

    for ( int i = 0 ; i < 12 ; i++ )     {
        cross_h[i] = i ;
        t = (i * 30)   / ( 11.0 / 120.0 );
        cross_m[i] = (int)t / 60  ;
        cross_s[i] = int (t -  ((int)t / 60) * 60)   ;
//        cout << "h=" << cross_h[i] << " " ;
//        cout << "m=" << cross_m[i] << " " ;
//        cout << "s=" << cross_s[i] << endl ;
    }
    cout << "input hour(0-11) " ;
    cin >> h ;
    if ( h < 0 || h > 11 ) return 1 ;
    cout << "input minute(0-59) " ;
    cin >> m ;
    if ( m < 0 || m > 59 ) return 1 ;
    for ( int i=0 ; i < 12 ; i++ ) {
        int j = (i+h) % 11 ;
//        cout << j << endl ;
        if ( i == 0 ) {
            if ( cross_m[j] > m  )
                cout <<cross_h[j]<<":"<<cross_m[j]<< ":"<<cross_s[j] << endl ;
            continue ;
        }
        cout <<cross_h[j]<<":"<<cross_m[j]<< ":"<<cross_s[j] << endl ;
        if ( i == 12 ) {
            if ( cross_m[j] <= m  )
                cout <<cross_h[j]<<":"<<cross_m[j]<< ":"<<cross_s[j] << endl ;
        }
    }

    return 0;
}
