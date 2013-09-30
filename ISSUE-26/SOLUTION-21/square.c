// use:  square < in.txt

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc , char* argv[])
{
   int n  ;
   double x2,y2,x3,y3,x4,y4 ;
   double ax,ay,bx,by,cx,cy,dx,dy ;
   double epsilon , a , a1 , a2 , a3 ;

   epsilon = 1.0 ;
   while ( 1 < (1 + epsilon )   )
       epsilon = epsilon / 10.0 ;
   epsilon = epsilon * 1000 ;

   while ( 1 ) {
      n = scanf (  "(%lf,%lf),(%lf,%lf),(%lf,%lf),(%lf,%lf)\r\n" ,
                   &ax,&ay,&x2,&y2,&x3,&y3,&x4,&y4) ;
      if ( n < 8 ) break ;
      a = 0.0 ;
      if ( a == 0.0) {
        a1 = (ax - x2) * (ax - x2) +  (ay - y2) * (ay - y2) ;
        a2 = (ax - x3) * (ax - x3) +  (ay - y3) * (ay - y3) ;
        a3 = (ax - x4) * (ax - x4) +  (ay - y4) * (ay - y4) ;
      }
      if ( fabs ( a1 - a2 ) <= epsilon ) {
        a = a1 ;
        if ( fabs(a * 2 - a3) > epsilon ) {
           printf("(%lf,%lf),(%lf,%lf),(%lf,%lf),(%lf,%lf) - not square\n" ,
                  ax,ay,x2,y2,x3,y3,x4,y4 );
           continue ;
        }
        bx = x2 ; by = y2 ;
        dx = x3 ; dy = y3 ;
        cx = x4 ; cy = y4 ;
      } else
          if ( fabs ( a1 - a3 ) <= epsilon ) {
            a = a1 ;
            if ( fabs(a * 2 - a2) > epsilon ) {
               printf("(%lf,%lf),(%lf,%lf),(%lf,%lf),(%lf,%lf) - not square\n" ,
                  ax,ay,x2,y2,x3,y3,x4,y4 );
               continue ;
            }
            bx = x2 ; by = y2 ;
            dx = x4 ; dy = y4 ;
            cx = x3 ; cy = y3 ;
          }
          else
            if ( fabs ( a2 - a3 ) <= epsilon ) {
                a = a2 ;
                if ( fabs(a * 2 - a1) > epsilon )  {
                   printf("(%lf,%lf),(%lf,%lf),(%lf,%lf),(%lf,%lf) - not square\n" ,
                     ax,ay,x2,y2,x3,y3,x4,y4 );
                   continue ;
                }
                cx = x2 ; cy = y2 ;
                bx = x3 ; by = y3 ;
                dx = x4 ; dy = y4 ;
            }
            else {
               printf("(%lf,%lf),(%lf,%lf),(%lf,%lf),(%lf,%lf) - not square\n" ,
                       ax,ay,x2,y2,x3,y3,x4,y4 );
               continue ;
           }
         if ( fabs (a-(cx-dx )*(cx-dx )-(cy-dy)*(cy-dy)) > epsilon ) {
               printf("(%lf,%lf),(%lf,%lf),(%lf,%lf),(%lf,%lf) - not square\n" ,
                ax,ay,x2,y2,x3,y3,x4,y4 );
               continue ;

         }
         if ( fabs(a-(bx-cx )*(bx-cx )-(by-cy)*(by-cy)) > epsilon ) {
               printf("(%lf,%lf),(%lf,%lf),(%lf,%lf),(%lf,%lf) - not square\n" ,
                ax,ay,x2,y2,x3,y3,x4,y4 );
               continue ;

         }
         if ( fabs ( a*2-(bx-dx)*(bx-dx)-(by-dy)*(by-dy) ) > epsilon ) {
               printf("(%lf,%lf),(%lf,%lf),(%lf,%lf),(%lf,%lf) - not square\n" ,
                ax,ay,x2,y2,x3,y3,x4,y4 );
               continue ;

         }
         printf("(%lf,%lf),(%lf,%lf),(%lf,%lf),(%lf,%lf) -  square\n" ,
                ax,ay,x2,y2,x3,y3,x4,y4 );

   }
   return 0;
}


