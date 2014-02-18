#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
struct card {
    char name[64];
    int beginIIN ;
    int endIIN ;
    int  minlen ;
    int  maxlen ;
    int active ;    // 0 - no , 1 yes
    int crc ;       // 0 - no , 1 yes
};

int luhn_alg ( char* ) ;  // 0 - ok , 1 - err

int main()
{
   struct card base[] = {
    {"American Express" , 34 , 34  , 15 , 15 , 1 , 1  } ,
    {"American Express" , 37 , 37 , 15 , 15  , 1  , 1 } ,
    {"Bankcard"	 , 5610 , 5610  , 16 , 16 , 0 , 1  } ,
    {"Bankcard"	 , 560221 , 560225 , 16 , 16 , 0 , 1  } ,
    {"China UnionPay" , 62  ,62 , 16 , 19 , 1 , 0 } ,
    {"China UnionPay" , 88 , 88 , 16 , 19 , 1 , 0 } ,
    {"Diners Club Carte Blanche" , 300 , 305 ,14 ,14 ,  1 , 1 } ,
    {"Diners Club enRoute" ,2014 , 2014 , 15 , 15 , 0 , 0 } ,
    {"Diners Club enRoute" ,2149  ,2149 ,  15 , 15 , 0 , 0 } ,
    {"Diners Club International" , 300 , 305  , 14 , 14, 1 , 1 } ,
    {"Diners Club International" , 309 , 309 ,  14 , 14, 1 , 1 } ,
    {"Diners Club International" , 36 , 36 , 14 , 14, 1 , 1 } ,
    {"Diners Club International" , 38 , 39 , 14 , 14, 1 , 1 } ,
    {"Diners Club United States & Canada" , 54 , 55 , 16 , 16 , 1 , 1 } ,
    {"Discover Card" ,6011, 6011 , 16 , 16 , 1 , 1 } ,
    {"Discover Card" ,622126 , 622925 , 16 , 16 , 1 , 1 } ,
    {"Discover Card" ,644 , 649 , 16 , 16 , 1 , 1 } ,
    {"Discover Card" ,65 , 65 , 16 , 16 , 1 , 1 } ,
    {"InstaPayment" , 637 , 639 , 16 , 16 ,1 ,1 } ,
    {"JCB" , 3528 , 3589 , 16 , 16 , 1 , 1 } ,
    {"Laser", 6304, 6304 , 16 , 19 , 1 , 1 } ,
    {"Laser",  6706,  6706,  16 , 19 , 1 , 1 } ,
    {"Laser",  6771,  6771,  16 , 19 , 1 , 1 } ,
    {"Laser",  6709,  6709 , 16 , 19 , 1 , 1 } ,
    {"Maestro" , 5018, 5018 , 12 , 19 , 1, 1 } ,
    {"Maestro" , 5020, 5020 , 12 , 19 , 1, 1 } ,
    {"Maestro" , 5038, 5038 , 12 , 19 , 1, 1 } ,
    {"Maestro" , 5612, 5612 , 12 , 19 , 1, 1 } ,
    {"Maestro" , 5893, 5893 , 12 , 19 , 1, 1 } ,
    {"Maestro" , 6304, 6304 , 12 , 19 , 1, 1 } ,
    {"Maestro" , 6759, 6759 , 12 , 19 , 1, 1 } ,
    {"Maestro" , 6761, 6763 , 12 , 19 , 1, 1 } ,
    {"Maestro" , 6390, 6390 , 12 , 19 , 1, 1 } ,
    {"Dankort" , 5019, 5019 , 16 , 16 , 1 , 1 } ,
    {"MasterCard" , 50 , 55 , 16 , 16 , 1, 1, } ,
    { "Solo" , 	6334, 6334 , 16 , 19 , 0 , 1 } ,
    { "Solo" , 	6767, 6767 , 16 , 19 , 0 , 1 } ,
    {"Switch" , 4903, 4903 , 16 , 19 , 0 , 1 } ,
    {"Switch" , 4905, 4905 , 16 , 19 , 0 , 1 } ,
    {"Switch" , 4911, 4911 , 16 , 19 , 0 , 1 } ,
    {"Switch" , 4936, 4936 , 16 , 19 , 0 , 1 } ,
    {"Switch" , 564182, 564182 , 16 , 19 , 0 , 1 } ,
    {"Switch" , 633110, 633110 , 16 , 19 , 0 , 1 } ,
    {"Switch" , 6333, 6759 , 16 , 19 , 0 , 1 } ,
    {"Visa" , 4 , 4	 , 13, 16 , 1, 1 } ,
    {"Visa Electron" , 	4026, 4026 , 16 , 16 , 1, 1, } ,
    {"Visa Electron" , 	417500, 417500 , 16 , 16 ,1, 1, } ,
    {"Visa Electron" , 	4405, 4405 , 16 , 16, 1, 1, } ,
    {"Visa Electron" , 	4508, 4508 , 16 , 16 ,1, 1, } ,
    {"Visa Electron" , 	4844, 4844 , 16 , 16 ,1, 1, } ,
    {"Visa Electron" , 	4913, 4913 , 16 , 16 ,1, 1, } ,
    {"Visa Electron" , 	4917, 4917 , 16 , 16 ,1, 1, } ,
  };

  cout << "Input number bank card: "  ;
  char cardnum [64] ;
  cin >> cardnum ;
  int numrec , flag ;

  numrec = sizeof ( base ) / sizeof (card ) ;
  flag = 0 ;
  for ( int i = 0 ; i < numrec ; i++ ) {
      for ( int j = base[i].beginIIN ; j <= base[i].endIIN ; j++ ) {
        char wrk [64] ; int n ;
        n = sprintf ( wrk , "%d" , j ) ;
        if ( !strncmp ( wrk , cardnum , n )) {
                int l = strlen ( cardnum ) ;
                if ( l < base[i].minlen || l > base[i].maxlen) continue ;
                if ( base[i].crc == 1 ) {
                    if (!luhn_alg ( cardnum ) ) {
                        cout << "type of card  " << base[i].name  ;
                        if ( base[i].active) cout << " active" ;
                        else cout << " no active " ;
                        cout << endl ;
                        flag = 1 ;
                    }
                }
                else {
                    cout << "type of card  " << base[i].name  ;
                    if ( base[i].active) cout << " active" ;
                    else cout << "  no active " ;
                    cout << endl ;
                    flag = 1 ;
                }

        }
      }

  }
    if ( !flag ) cout << "can't fix card type" << endl ;
    return 0;
}

int luhn_alg ( char* p ) {
    int l , crc , k  , s  ;
    l  = strlen( p )  ;
    if ( isdigit(p[l-1]))
        crc = p[l-1] - '0' ;
    s = 0 ;
    for ( int i = 2 ; l - i >= 0 ; i+=2) {
            if ( isdigit(p[l-i])) {
              k = p[l-i] - '0' ;
              k *= 2 ;
              if ( k > 9  )
                k = (k%10) + 1 ;
              s += k ;
            }
            else return 1 ;
    }
    s *= 9 ;
    s %= 10 ;
    if ( crc == s ) return 0 ;
return 1 ;
}
