//  compiler & linking
//  if use linux : g++ -o maze maze.cpp
//  if use windows and bcc32: bcc32 maze.cpp
//  running
//  if use linux : ./maze < in.txt
//  if use windows: maze < in.txt
//  in.txt:
//  WWWWWWWWWW
//  W  WW    W
//  W @  @  WW
//  W  @@    W
//  W @@     W
//  W   @  @ W
//  W@ @  @@ W
//  WWWWWWWWWW



#include <iostream>
#include <cstring>
#include <queue>


using namespace std;

int main()
{
    static const int limit = 128 ;
    char buffer[limit][limit] ;
    int x , y , t , Max = 0 ;
    queue < pair<int,int>  > range ;

    memset ( buffer , ' ' , limit * limit ) ;

    // input data
    for ( x=0 , y = 0 ;  !cin.eof() ; ++x  ) {
     cin.getline ( buffer[x] , limit ) ;
     t  = strlen ( buffer[x] ) ;
     if ( y < t ) y = t ;
    }
    --x ;

    //for ( t=0 ; t < x; t++)
    //  cout <<  buffer[t] << endl ;

    // cout << "x = " << x << " y = " << y << endl ;

    for ( int i = 0  ; i < x ; i++)
      for ( int j = 0 ; j < y ; j++)
        if ( buffer[i][j] == '@') {  // finding spot @
            pair<int, int> aPair = make_pair(i, j ) ;
            buffer[i][j] = ' ' ;     //  counted
            range.push ( aPair ) ;   // add coordinates in queue
            t = 1 ;  // length spot
            while ( !range.empty()  ) {
              pair<int, int> bPair = range.front() ;  // get coordinate
              // locating neighbor @ , commom side
              if ( bPair.first - 1 >=  0 && buffer[bPair.first - 1][bPair.second] == '@'  ) {
                 pair<int, int> aPair = make_pair(bPair.first - 1, bPair.second);
                 buffer[bPair.first - 1][bPair.second] = ' ' ;
                 range.push(aPair) ;
                 ++t;
              }
              if ( bPair.first + 1 <  x && buffer[bPair.first + 1][bPair.second] == '@'  ) {
                 pair<int, int> aPair = make_pair(bPair.first +1 , bPair.second);
                 buffer[bPair.first + 1][bPair.second] = ' ' ;
                 range.push(aPair) ;
                 ++t;
              }

              if ( bPair.second - 1 >=  0 && buffer[bPair.first ][bPair.second-1] == '@'  ) {
                 pair<int, int> aPair = make_pair(bPair.first , bPair.second - 1);
                 buffer[bPair.first][bPair.second - 1] = ' ' ;
                 range.push(aPair) ;
                 ++t;
              }

              if ( bPair.second + 1 < y && buffer[bPair.first ][bPair.second+1] == '@'  ) {
                 pair<int, int> aPair = make_pair(bPair.first , bPair.second + 1);
                 buffer[bPair.first][bPair.second + 1] = ' ' ;
                 range.push(aPair) ;
                 ++t;
              }

              // locating neighbor @ , commom point

              if ( bPair.first - 1 >=  0 && bPair.second - 1 >=  0 &&
                   buffer[bPair.first - 1][bPair.second-1] == '@'  ) {
                 pair<int, int> aPair = make_pair(bPair.first - 1, bPair.second-1);
                 buffer[bPair.first - 1][bPair.second-1] = ' ' ;
                 range.push(aPair) ;
                 ++t;
              }

              if ( bPair.first - 1 >=  0 && bPair.second + 1 < y &&
                   buffer[bPair.first - 1][bPair.second+1] == '@'  ) {
                 pair<int, int> aPair = make_pair(bPair.first - 1, bPair.second+1);
                 buffer[bPair.first - 1][bPair.second+1] = ' ' ;
                 range.push(aPair) ;
                 ++t;
              }

              if ( bPair.first + 1 < x && bPair.second - 1 >=  0 &&
                   buffer[bPair.first + 1][bPair.second-1] == '@'  ) {
                 pair<int, int> aPair = make_pair(bPair.first + 1, bPair.second-1);
                 buffer[bPair.first + 1][bPair.second-1] = ' ' ;
                 range.push(aPair) ;
                 ++t;
              }

              if ( bPair.first + 1 < x && bPair.second + 1 < y &&
                   buffer[bPair.first + 1][bPair.second+1] == '@'  ) {
                 pair<int, int> aPair = make_pair(bPair.first + 1, bPair.second+1);
                 buffer[bPair.first + 1][bPair.second+1] = ' ' ;
                 range.push(aPair) ;
                 ++t;
              }

              range.pop ( ) ;  // remove  coordinates  from queue, we looked all neighbor  points for this point
            }
            // cout << "t= " << t << " i = " << i << " j = " << j <<endl ;
            if ( Max < t ) Max = t ;
        }
    cout << "The largest spot @'s = " << Max << endl ;
    return 0;
}
