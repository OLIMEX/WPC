#include <iostream>
#include <cmath>

using namespace std;

int main(int argc , char* argv[])
{
   long double eps ;
   long double x1 , y1 , x2 , y2 , x3 , y3 ;
   long double a1 , b1 , a2 , b2 , k1 , k2 ;
   long double xo , yo , R ;
   long double d , xa , ya , xb , yb ;
   long double x , y ;

   eps = 1 ;
   // define computer epsilon
   while ( (1.0 + eps) > 1.0   )
     eps = eps / 10.0 ;
   //cout << "eps =  " << eps  << endl;
   eps = eps * 1000.0 ;


  cin >> x1 >> y1 ;
  cin >> x2 >> y2 ;
  cin >> x3 >> y3 ;

   // check for line

   d = abs ((x3 - x1 ) / (x2 - x1 ) - (y3 - y1 ) / (y2 - y1 ) ) ;

   if ( d <= eps ) {
     cout << "the points are not passing in a circle" << endl ;
     return 0 ;
   }


   xa =  (x1 + x2 ) / 2 ;
   ya =  (y1 + y2 ) / 2 ;

   xb =  (x2 + x3) / 2 ;
   yb =  (y2 + y3) / 2 ;

   a1 = y1 - y2 ;
   b1 = x2 - x1 ;

   a2 = y2 - y3 ;
   b2 = x3 - x2 ;


   if ( abs (a1) > eps && abs (a2) > eps  ) {
     // normal case

      k1 = b1 / a1 ;
      k2 = b2 / a2 ;

      xo = (yb + xa*k1 - xb * k2 - ya ) / ( k1 - k2 ) ;
      yo = ya +  k1 *  ( xo - xa ) ;
   }
   else if ( abs( a1 ) < eps ) {
     // the line is parallel Ox
     xo = xa ;
     k2 = b2 / a2 ;
     yo = yb +  k2 *  ( xo - xb ) ;
   }
   else if ( abs( a2 ) < eps ) {
     // the line is parallel Ox
     xo = xb ;
     k1 = b1 / a1 ;
     yo = ya +  k1 *  ( xo - xa ) ;
   }

   R =  (x1-xo)*(x1-xo) + (y1-yo)*(y1-yo) ;
   // cout << "Radius = " << R << endl ;

   while ( true  ) {

     cin >> x >> y ;
     if ( cin.eof() ) break ;

     // cout << "x = " << x  << "y = " << y << endl ;
     d = (x-xo)*(x-xo) + (y-yo)*(y-yo) ;
     // PROVERKA DALI PRINADLEJAT NA OKRAJNOST
     if ( abs (R - d) > eps ) {

        cout << "the points are not passing in a circle" << endl ;
        return 0 ;

     }
     /*
      // PROVERKA DALI SA VATRE V KRAGA
      if ( R  < d  ) {

        cout << "the points are not passing in a circle" << endl ;
        return 0 ;

     }
     */

   }
   cout << "the points are  passing in a circle" << endl ;

   return 0;
}
