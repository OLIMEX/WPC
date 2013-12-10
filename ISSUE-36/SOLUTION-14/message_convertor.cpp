#include <iostream>
#include <cstdio>
#include <cstring>


using namespace std;

int main()
{
    char btn[128][6] ;
    memset ( (char*)btn , 0 , 128*6);
    strcpy ( btn['a'], "2 ") ;
    strcpy ( btn['b'], "22 ") ;
    strcpy ( btn['c'], "222 ") ;
    strcpy ( btn['d'], "3 ") ;
    strcpy ( btn['e'], "33 ") ;
    strcpy ( btn['f'], "333 ") ;
    strcpy ( btn['g'], "4 ") ;
    strcpy ( btn['h'], "44 ") ;
    strcpy ( btn['i'], "444 ") ;
    strcpy ( btn['j'], "5 ") ;
    strcpy ( btn['k'], "55 ") ;
    strcpy ( btn['l'], "555 ") ;
    strcpy ( btn['m'], "6 ") ;
    strcpy ( btn['n'], "66 ") ;
    strcpy ( btn['o'], "666 ") ;
    strcpy ( btn['p'], "7 ") ;
    strcpy ( btn['q'], "77 ") ;
    strcpy ( btn['r'], "777 ") ;
    strcpy ( btn['s'], "7777 ") ;
    strcpy ( btn['t'], "8 " ) ;
    strcpy ( btn['u'], "88 ") ;
    strcpy ( btn['v'], "888 ") ;
    strcpy ( btn['w'], "9 ") ;
    strcpy ( btn['x'], "99 ") ;
    strcpy ( btn['y'], "999 ") ;
    strcpy ( btn['z'], "9999 ") ;

    char in[128] ;
    cout << "input word " ;
    cin >> in ;

    for ( int i = 0 ; in[i] ; i++ ) {
       if ( !isalpha(in[i]) ) {
          cout << "is not alphabetic letter" << endl ;
          return 1 ;
       }
       in[i] = tolower (in[i]);
    }

    for ( int i = 0 ; in[i] ; i++ )
      cout << btn[(int)in[i]];
    cout << endl ;

    return 0;
}
