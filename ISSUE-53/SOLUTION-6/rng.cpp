// for compile and link: g++ -o rng rng.cpp
// for run : ./rng

#include <iostream>
#include <cstdio>
#include <ctime>

using namespace std;

unsigned int Xn1=0 ;

unsigned int myrand() {
    unsigned int  Xn , a , c , m ;
    m = 0xffffffff & 0x7fffffff;
    a = 1103515245;
    c = 12345;

    Xn = (a * Xn1 + c) % m ;
    Xn = Xn & 0x7fffffff;


    if ( Xn1 == 0 ) {
        time_t t ;
        time(&t) ;
        Xn1 = t ;
    }

    Xn = (a * Xn1 + c) % m ;
    Xn = Xn & 0x7fffffff;

    Xn1 = Xn ;
    return Xn ;

}


int main()
{

    for (int i=0 ; i < 20 ;i++)
      cout << myrand() << endl ;

    return 0;
}
