// for translate & link : g++ -o bracket bracket.cpp
// for running : ./bracket < test.c

#include <iostream>
#include <stack>
#include <vector>
#include <list>


using namespace std;

int main()
{

  stack< int > intStack;
  static int limit = 1024 ;
  int  line_comment=0 , comment = 0 , i , pos ;
  char str[limit];

  while ( !cin.eof()) {
     cin.getline(str, limit );
     // cout << str << endl ;
     cout <<  endl ;
     line_comment = 0  ;

     for ( i=0 ; str[i] != '\0' ; i++ ) {

       if ( line_comment == 0 )
        switch (str[i])  {
           case '/' :
              if ( str[i+1] == '/' && comment == 0 ) {
                 // cout << "begin comentar // " << endl ;
                 line_comment = 1 ;
                 break ;
              }

              if ( str[i+1] == '*'  && comment == 0) {
                 // cout << "begin comentar /* " << endl ;
                 comment = 1 ;
                 break ;
              }

           break ;

           case '{' :
              if ( comment == 0 ) {
                 intStack.push( i );
              }
           break ;


           case '}' :
              if ( comment == 0 ) {
                 if ( intStack.empty() ) {
                    cout << endl << "error brackets" << endl ;
                    return 0 ;
                 }
                 pos = intStack.top() ;
                 intStack.pop();
                 cout << endl ;
                 cout.fill(' ');
                 if ( pos == 0 )
                   cout.width(pos);
                 else
                   cout.width(pos+1);
              }
           break ;

           case '*' :
              if ( str[i+1] == '/' && comment == 1 ) {
                 // cout << "end coment  " << endl ;
                 comment = 0 ;
              }
           break ;

        }  // end of switch

        cout << str[i] ;



     }  // end of for

      cout <<  endl ;


  }   // end of while

    if  ( !intStack.empty() )
       cout << endl << "error brackets" << endl ;


   return 0;
}
