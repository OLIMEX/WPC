// for compile & link  : g++ -o panel panel.cpp
// for run: ./panel < in.txt


#include <iostream>

using namespace std;

static const int number = 20;
static const int dim  = 10;

struct pbc {
int x ;
int y ;
int d ;
int i ;
} ;


int minPlace = 20000000 ;


struct pbc pbcs[number] ;

void sort (int) ;

int panel[dim][dim] ;
int decision [dim][dim] ;

void print ( void )  ;
void fill ( int  ) ;
void clear ( int  ) ;
void savemin () ;

int N = 0 ;
int main()
{


    for ( int i=0 ; i < dim; i++)
        for ( int j=0 ; j < dim; j++)
            panel[i][j] = -1 ;

    while ( !cin.eof() ) {
        cin >> pbcs[N].x >> pbcs[N].y >> pbcs[N].d ;
        pbcs[N].i = N + 1 ;
        ++N ;

    }
    --N ;

    sort ( N ) ;

    for ( int j = 0 ; j < N ; j++ )
        cout << "x=" << pbcs[j].x << ",y=" << pbcs[j].y << ",d=" <<  pbcs[j].d << ",input number=" << pbcs[j].i <<  endl ;

    // fix largest
    for ( int i=0 ; i < pbcs[0].x; i++)
        for ( int j=0 ; j < pbcs[0].y; j++)
            panel[i][j] = pbcs[0].i ;

     fill ( 1 ) ;
     print () ;

    return 0;
}



void sort ( int n ) {
    int s ;
    for ( int i = 0 ; i < n-1 ; i++)
        for ( int j = i+1 ; j < n ; j++) {
            if ( pbcs[i].x > pbcs[i].y ) {
                s = pbcs[i].x ;
                pbcs[i].x = pbcs[i].y ;
                pbcs[i].y = s  ;
            }
            if ( pbcs[j].x > pbcs[j].y ) {
                s = pbcs[j].x ;
                pbcs[j].x = pbcs[j].y ;
                pbcs[j].y = s  ;
            }
            if ( pbcs[j].y > pbcs[i].y ) {
                s = pbcs[j].y ;
                pbcs[j].y = pbcs[i].y ;
                pbcs[i].y = s ;

                s = pbcs[j].x ;
                pbcs[j].x = pbcs[i].x ;
                pbcs[i].x = s ;

                s = pbcs[j].d ;
                pbcs[j].d = pbcs[i].d ;
                pbcs[i].d = s ;

                s = pbcs[j].i ;
                pbcs[j].i = pbcs[i].i ;
                pbcs[i].i = s ;

            }

        }

}



void fill ( int n ) {
    if ( n == 0 ) return  ;

    //find space
    for ( int i=0 ; i < dim ; i++ )
       for ( int j=0 ; j < dim ; j++ ) {
          if ( panel[i][j] == -1 ) {
              if ( panel [i+pbcs[n].x ][j+pbcs[n].y] == -1 && (i+pbcs[n].x) < dim && (j+pbcs[n].y) < dim  ) {
                 int flag = 0 ;
                 for ( int k=i ; k < i+pbcs[n].x ; k++ )
                    for ( int l=j ; l < j+pbcs[n].y ; l++ )
                         if ( panel[k][l] != -1 ) flag =1 ;
                  if ( flag == 1 ) continue ;
                 for ( int k=i ; k < i+pbcs[n].x ; k++ )
                    for ( int l=j ; l < j+pbcs[n].y ; l++ )
                        panel[k][l] = pbcs[n].i ;
                        if ( (n+1) == N  ) {

                            savemin() ;
                            clear  ( n ) ;
                        } else {
                            fill ( n+1 ) ;
                            clear  ( n ) ;
                        }

              }

          }

       }
       clear ( n ) ;
       return ;
}


void print ( ) {
cout << endl ;
cout << "decision  =  " << minPlace << endl ;


for ( int i=0 ; i < dim; i++) {
    cout << endl ;
    for ( int j=0 ; j < dim; j++) {
      if ( decision[i][j] == -1 )
         cout << '*' << " " ;
      else
         cout << decision[i][j] << " " ;
}

}
return ;
}


void print1 ( ) {
cout << endl ;
cout << "decision  =  " << endl ;


for ( int i=0 ; i < dim; i++) {
    cout << endl ;
    for ( int j=0 ; j < dim; j++) {
      if ( panel[i][j] == -1 )
         cout << '*' << " " ;
      else
         cout << panel[i][j] << " " ;
}

}
return ;
}



void clear ( int n ) {
for ( int i=0 ; i < dim; i++)
    for ( int j=0 ; j < dim; j++)
      if ( panel[i][j] == pbcs[n].i )
          panel[i][j]  = -1 ;
}

void savemin () {
int  x = 0  , y = 0 ;
int temp ;
for ( int i=0 ; i < dim ; i++ )
  for ( int j = 0 ; j < dim ; j++ )
     if ( panel[i][j] != -1  ) x = i+1 ;


for ( int i=0 ; i < dim ; i++ )
  for ( int j = 0 ; j < dim ; j++ )
     if ( panel[j][i] != -1  ) y = i+1 ;

temp = x * y ;

if ( temp < minPlace ) {
  minPlace = temp ;
  for ( int i = 0  ; i < dim; i++)
    for ( int j = 0  ; j < dim ; j++)
         decision [i][j] = panel[i][j];

}

}
