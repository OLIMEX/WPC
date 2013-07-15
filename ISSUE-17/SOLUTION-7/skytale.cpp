// for translate & link : g++ -o skytale skytale.cpp
// for running crypt: ./skytale c  < in.txt > out.txt
// for running decrypt: ./skytale d  < in.txt > out.txt

#include <iostream>
#include <cstring>


using namespace std;




int main(int argc , char **argv)
{
   static const  int rod = 8 ;
   static const  int length = 16 ;
   char buf[130] , process[130];
   int  tbl[130] ;
   int i , j  , k  ;

   if ( argc < 2 ) {
     cout << "format: ./skytale c < input > output.file" << endl ;
     cout << "format: ./skytale d < input > output.file" << endl ;
     cout << "max length text 128 bytes" << endl ;
     return 0 ;

   }

   memset ( buf , ' ' , 128 ) ;

   cin.read(buf, 128);


   for ( i = 0 , k = 0  ; i < rod ; i++ )
      for ( j = 1 ; j <= length ; j++)
         tbl[k++] =  i + (j-1)*rod  ;


   if ( *argv[1] == 'd') { //decrypt
      for ( k = 0 ; k < length * rod ; k++) {
        if ( buf[k] == '\0'  ) buf[k] = ' ' ;
        process[tbl[k]] = buf [k] ;

      }
   }
   else {
      for ( k = 0 ; k < length * rod ; k++) {
        if ( buf[tbl[k]] == '\0'  ) buf[tbl[k]] = ' ' ;
        process[k] = buf [tbl[k]] ;
      }

   }

   for ( k= 0 ; k < length * rod ; k++)
      cout << process[k] ;

   return 0;
}


