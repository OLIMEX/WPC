#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

int container[8][20][8];
int numpackets=0 , M=0 ;
const int CX=8;
const int CY=20;
const int CZ=8;
int N ;  // number packet
int X[100] , Y[100] , Z[100] ;  // coord packets
int sx[100] , sy[100] , sz[100]  ;



void find_solution(int n) ;
int check ( int x , int y , int z , int n ) ;
void  fill ( int x , int y , int z , int n ) ;
void save_solution(void) ;

int main()
{
    cin >> N ;
    if ( N >= 100 ) return 0 ;
    vector<int> v(N);
    for (int i = 0; i < N; ++i)
     v[i] = i;

    for ( int i=0 ; i < N ; i++)
        cin >> X[i] >> Y[i] >> Z[i] ;
//    for ( int i=0 ; i < N ; i++)
//        cout <<  X[i] << ","  <<  Y[i] << ","  <<  Z[i] << endl  ;

    do {
        for ( int i=0 ; i < CX ; i++)
            for ( int j=0 ; j < CY ; j++)
                for ( int k=0 ; k < CZ ; k++)
                    container[i][j][k] = -1 ;
        numpackets = 0 ;
        for ( int i=0 ; i < N ; ++i )
            find_solution(v[i]);

    } while(next_permutation(v.begin(), v.end()));

    for ( int i=0 ; i < N ; i++)
        if ( sx[i] != -1 ) {
            cout << "packet:" <<i+1 << " : " << sx[i] << "," << sy[i] << "," << sz[i] << endl ;
        }


    return 0;
}

void find_solution(int n ) {
    for ( int i=0 ; i < CX ; i++ )
        for ( int j=0 ; j < CY ; j++ )
            for ( int k=0 ; k < CZ ; k++ )
            if ( !check ( i , j , k , n ) ) {
                fill ( i , j , k , n ) ;
                ++numpackets ;
                if ( M < numpackets ) {
                    M = numpackets ;
                    save_solution() ;
                    return ;
                }

            }
    return ;
}

int check ( int x , int y , int z , int n ) {
    if ( x + X[n] >= CX  ) return 1 ;
    if ( y + Y[n] >= CY  ) return 1 ;
    if ( z + Z[n] >= CZ  ) return 1 ;
    for ( int i = x ; i < x + X[n] ; i++ )
        for ( int j = y ; j < y + Y[n] ; j++ )
            for ( int k = z ; k < z + Z[n] ; k++ )
                if ( container[i][j][k] != -1 ) return 1 ;
    return 0 ;

}

void  fill ( int x , int y , int z , int n ) {
    for ( int i = x ; i < x + X[n] ; i++ )
        for ( int j = y ; j < y + Y[n] ; j++ )
            for ( int k = z ; k < z + Z[n] ; k++ )
                container[i][j][k] = n ;
}

void save_solution() {
    for ( int i=0; i < N ; i++ ) {
            sx[i] = -1 ;
            sy[i] = -1 ;
            sz[i] = -1 ;
    }
    for ( int i = 0 ; i < CX ; i++ )
        for ( int j = 0 ; j < CY ; j++ )
            for ( int k = 0 ; k < CZ ; k++ ) {
                    if ( container[i][j][k]  != -1 ) {
                        if (sx[container[i][j][k]] == -1 ) {
                                sx[container[i][j][k]] = i ;
                                sy[container[i][j][k]] = j ;
                                sz[container[i][j][k]] = k ;
                        }

                    }


            }
}
