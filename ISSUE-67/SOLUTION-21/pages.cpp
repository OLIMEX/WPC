#include <iostream>

using namespace std;

int main()
{
    int a1 , n ;

    for ( n= 1 ; 1 ; n++ )
    {
        a1 = (2*9808 / n - n + 1) / 2;
        if ( a1 > 0 ) cout << "begin page:"<<a1<< "  numbers page:"<<n<< endl ;
        else break ;
    }
    return 0 ;
}
