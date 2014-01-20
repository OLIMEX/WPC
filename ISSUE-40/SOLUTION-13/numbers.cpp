// for translate & link : todorp@dantooine:~/test/tourney/numbers3$ g++ -o numbers numbers.cpp
// for run : todorp@dantooine:~/test/tourney/numbers3$ ./numbers
// input number: 19
// 19 = 1 * 3  * 3 * 3 / 2 * 3 / 2


#include <iostream>

using namespace std;

const static int dimension = 51 ;

int limit  ;                       // number of nested cycle
int index [dimension] ;            // body nested cycle
int index_limit[dimension][2] ;    // limit every index - low , high value include
int nested_cycle (void) ;          // return 1 , 0 - end of nested cycle
int k ;


int main( int argc , char** argv)
{

int number ;

cout << "input number: " ;
cin >> number ;

for ( limit = 1 ; limit < 50; ++limit ) {
    // init
    for ( int i=0 ; i < limit ; i++ ) {
        index_limit[i][0] = 2 ;
        index_limit[i][1] = 3 ;
        index[i] =  index_limit[i][0]  ;
    }
    k = limit -1  ;
    do {
        // print
        int num = 3 ;
        for ( int i=0 ; i < limit ; i++ )  {
            if ( index[i] == 2 )
                num = num  / 2 ;
            else
                num = num * 3 ;

        }
        if ( num == number ) {
            cout << number <<  " = 1 * 3 " ;
            for ( int i=0 ; i < limit ; i++ )  {
                if ( index[i] == 2 )
                    cout << " / "  << index[i]  ;
                else
                    cout << " * " << index[i]  ;
            }
            cout << endl ;
            return 0 ;
        }
    } while ( nested_cycle  ( ) ) ;

}

cout << "can't find solution " << endl ;

return 0 ;
}

int  nested_cycle  ( )
 {
   int i;

   if( index[k] < index_limit[k][1] ) {
       ++index[k] ;
       return 1 ;
    }
    else
      while  ( --k  >= 0  )
        if (index[k] < index_limit[k][1] ) {
              ++index[k] ;
              for ( i = k+1 ; i < limit ; i++ ) index[i] = index_limit[i][0] ;
              k = limit - 1 ;
              return 1 ;
        }
   return 0;
}


