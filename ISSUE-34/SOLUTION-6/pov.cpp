// for compile & link : g++ -o pov pov.cpp
// for run : ./pov


#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;
#define degree 3.14159265/180


float  center_pixel[140][140][3] ;
float strip[102][3] ;  // first coord x , second coord y , third coord - 0 empty pixel , 1 fill pixel
int fill_center_pixel () ;
int fill_strip_center (int deg) ;
int fill_strip_pixel (int deg) ;


const int cx = 70 ;
const int cy = 70 ;

int main()
{
    fill_center_pixel ()  ;

    for (int  i = 0 ; i < 360 ; i++) {
        fill_strip_center (i) ;
        fill_strip_pixel ( i ) ;
    }

    return 0;
}



int fill_center_pixel () {
int x , y ;
float dx , dy  ;
for ( x = 0 , dx = 0.5 ; x < 140 ; ++x , ++dx  )
 for ( y = 139 , dy = 0.5 ; y >= 0 ; --y , ++dy  ) {
    center_pixel[x][y][0] = dx ;
    center_pixel[x][y][1] = dy ;
    center_pixel[x][y][2] = (x+y)%2  ;  // 1 - fill pixel , 0 - empty pixel , init pixel
 }
 return 1 ;
}


int fill_strip_center (int deg) {

 for (int  d = 0 ; d < 100 ; d++  ) {
    strip[0][0] = cx + d * cos ( deg * degree ) ;
    strip[0][1] = cy + d * sin ( deg * degree ) ;
  }
  return 1 ;
}


int fill_strip_pixel (int deg) {
   float min  , d  ;
   if ( deg > 0 && deg < 90 ) {
     for ( int i = 0 ; i < 100 ; i++) {
      min = 200 ;
      for ( int x = 70 ; x < 140 ; x++ )
        for ( int y = 70 ; y < 140 ; y++ ) {
           d = (strip[i][0] - center_pixel[x][y][0] ) * (strip[i][0] - center_pixel[x][y][0] ) +
               (strip[i][1] - center_pixel[x][y][1] ) * (strip[i][1] - center_pixel[x][y][1] )  ;
           if ( d < min )  { strip[i][2] = center_pixel[x][y][2]  ; min = d ;}
        }

     }
   }


   if ( deg > 90 && deg < 180 ) {
     for ( int i = 0 ; i < 100 ; i++) {
      min = 200 ;
      for ( int x = 0 ; x < 70 ; x++ )
        for ( int y = 70 ; y < 140 ; y++ ) {
           d = (strip[i][0] - center_pixel[x][y][0] ) * (strip[i][0] - center_pixel[x][y][0] ) +
               (strip[i][1] - center_pixel[x][y][1] ) * (strip[i][1] - center_pixel[x][y][1] )  ;
           if ( d < min )  { strip[i][2] = center_pixel[x][y][2]  ; min = d ;}
        }

     }
   }


   if ( deg > 180 && deg < 270 ) {
     for ( int i = 0 ; i < 100 ; i++) {
      min = 200 ;
      for ( int x = 0 ; x < 70 ; x++ )
        for ( int y = 0 ; y < 70 ; y++ ) {
           d = (strip[i][0] - center_pixel[x][y][0] ) * (strip[i][0] - center_pixel[x][y][0] ) +
               (strip[i][1] - center_pixel[x][y][1] ) * (strip[i][1] - center_pixel[x][y][1] )  ;
           if ( d < min )  { strip[i][2] = center_pixel[x][y][2]  ; min = d ;}
        }

     }
   }


  if ( deg > 270 && deg < 360 ) {
     for ( int i = 0 ; i < 100 ; i++) {
      min = 200 ;
      for ( int x = 70 ; x < 140 ; x++ )
        for ( int y = 0 ; y < 70 ; y++ ) {
           d = (strip[i][0] - center_pixel[x][y][0] ) * (strip[i][0] - center_pixel[x][y][0] ) +
               (strip[i][1] - center_pixel[x][y][1] ) * (strip[i][1] - center_pixel[x][y][1] )  ;
           if ( d < min )  { strip[i][2] = center_pixel[x][y][2]  ; min = d ;}
        }

     }
   }

   if ( deg == 0  ) {
     for ( int i = 0 ; i < 100 ; i++) {
      min = 200 ;
      for ( int x = 70 ; x < 140 ; x++ )
        for ( int y = 68 ; y < 72 ; y++ ) {
           d = (strip[i][0] - center_pixel[x][y][0] ) * (strip[i][0] - center_pixel[x][y][0] ) +
               (strip[i][1] - center_pixel[x][y][1] ) * (strip[i][1] - center_pixel[x][y][1] )  ;
           if ( d < min )  { strip[i][2] = center_pixel[x][y][2]  ; min = d ;}
        }

     }
   }
   if ( deg == 90  ) {
     for ( int i = 0 ; i < 100 ; i++) {
      min = 200 ;
      for ( int x = 68 ; x < 72 ; x++ )
        for ( int y = 70 ; y < 140 ; y++ ) {
           d = (strip[i][0] - center_pixel[x][y][0] ) * (strip[i][0] - center_pixel[x][y][0] ) +
               (strip[i][1] - center_pixel[x][y][1] ) * (strip[i][1] - center_pixel[x][y][1] )  ;
           if ( d < min )  { strip[i][2] = center_pixel[x][y][2]  ; min = d ;}
        }

     }
   }
   if ( deg == 180  ) {
     for ( int i = 0 ; i < 100 ; i++) {
      min = 200 ;
      for ( int x = 0 ; x < 70 ; x++ )
        for ( int y = 68 ; y < 72 ; y++ ) {
           d = (strip[i][0] - center_pixel[x][y][0] ) * (strip[i][0] - center_pixel[x][y][0] ) +
               (strip[i][1] - center_pixel[x][y][1] ) * (strip[i][1] - center_pixel[x][y][1] )  ;
           if ( d < min )  { strip[i][2] = center_pixel[x][y][2]  ; min = d ;}
        }

     }
   }
   if ( deg == 270  ) {
     for ( int i = 0 ; i < 100 ; i++) {
      min = 200 ;
      for ( int x = 68 ; x < 72 ; x++ )
        for ( int y = 0 ; y < 70 ; y++ ) {
           d = (strip[i][0] - center_pixel[x][y][0] ) * (strip[i][0] - center_pixel[x][y][0] ) +
               (strip[i][1] - center_pixel[x][y][1] ) * (strip[i][1] - center_pixel[x][y][1] )  ;
           if ( d < min )  { strip[i][2] = center_pixel[x][y][2]  ; min = d ;}
        }

     }
   }
   return 1 ;

}
