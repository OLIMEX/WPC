// for translation & link : g++ -o puzzle  puzzle.cpp
// for running : ./puzzle < in.txt

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>


using namespace std;

int puzzle_word ( char* ) ;

static const int limit = 1024 ;
int main()
{
    char buf[limit] , save[limit];
    char *pch ,*pb , *ps ;
    int l ;
    srand(time(0));
    while ( true ) {
      cin.getline(buf , limit)  ;
      if ( cin.eof() ) break ;
      strcpy ( save , buf ) ;
      pb = buf ; ps = save ;
      pch = strtok (buf," ,.-?!*+=%");
      while ( pch != NULL ) {
         //cout << pch  ;
         puzzle_word ( pch ) ;
         l = pch - pb + strlen (pch)  ;
         cout << *(ps + l ) ;
         if ( *(ps+l) != ' ' ) cout  << " " ;
         pch = strtok (NULL," ,.-?!*+=%");
      }

      cout << endl  ;

    }

    return 0;
}

int puzzle_word ( char* p )  {
   char *pc ;
   char wrk[limit] ;
   int len , i , randomNumber ;


   pc = p ;
   //check is it  word ?

   while ( *pc )
    if  ( !isalpha(*pc++) ) break ;

    if ( *pc ) {
       // isn't word
       cout << p ;
       return 1  ;
    }

    len = strlen ( p ) ;
    if ( len <= 3 ) {
       cout << p ;
       return 1  ;
    }

    memset ( wrk , '\0' , len + 1 )  ;

    i = 1 ; wrk[0] = *p ;  wrk [len-1] = *(p+len-1) ;
    while ( i <= (len - 2) ) {
        randomNumber = rand()%len;
        if ( wrk [randomNumber] )  continue ;
        wrk [randomNumber]  = *(p+i) ;
        ++i ;
    }

    cout << wrk ;
    return 0 ;


}

