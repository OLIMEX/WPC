#include <iostream>


using namespace std;

const char *tabl_template_digit[]={"", "A", "AA", "AAA", "AB", "B", "BA", "BAA", "BAAA","AC"};
//                                 0   1     2     3     4     5     6     7      8      9
const char *tabl_template_degree[]={"IVX", "XLC", "CDM", "M"} ;
//                                    0      10    100   1000
int pw ( int ) ;

int main() {
    char buf[32] ;
    int n  , k  , i , j ;
    cout << "input number ( 1 - 3999) " << endl;
    cin >> n ;
    if ( n < 0 || n > 3999 ) {
        cout << "can't convert number " << endl ;
        return 0 ;
    }
    k = 3  ; j = 0 ;
    while ( k  >=  0 ) {
        i = n /   pw( k) ;
        if ( i > 0 ) {
            for ( char* p = (char*)tabl_template_digit[i]; *p != 0 ; ++p)
                buf[j++] = tabl_template_degree[k][*p - 'A'] ;
        }
        n = n - (i *  pw (k)) ;
        --k ;
    }
    buf[j] = 0 ;
    cout << "roman number " << buf <<  endl ;
    return 0;
}

int pw ( int d ) {
  int s = 1 ;
  if ( d <= 0 ) return s ;
  for ( int i=0 ; i < d ; i++) {
    s = s * 10 ;
  }
  return s ;
}
