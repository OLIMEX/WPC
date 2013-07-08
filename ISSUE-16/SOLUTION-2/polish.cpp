// for compile & link : g++ -o polish polish.cpp
// for run : ./polish
// test exmaple :
// (((12.34 - 67.98))) + ((23.456 - 23.12 + 17.961)) * 12.123
// ((10.1 - 12.12 ) / 2 + 16.4)
//  2 - 6 ^ 2 + 18
// ......

#include <iostream>
#include <string>
#include <queue>
#include <stack>


using namespace std;


int in_expresion (void) ;
int is_number(string& ) ;
int priority_is (char  ) ;
int convert (void) ;


queue<string> expresion;
queue<string> expresion_polish;

int main () {

if ( in_expresion ( ) )
    return 1 ;

if ( convert() )
    return 1 ;


 while(!expresion_polish.empty()) {
        string str =  expresion_polish.front()  ;
        cout << str << " " ;
        expresion_polish.pop();
     }
 cout << endl;
 return 0 ;


}


int in_expresion() {
    char buf[512] , wrk [2];
    int i , j , k , f , n   ;

    cout  << "input expression : "  << endl ;
    cin.getline  ( buf , 500) ;
    // cout << buf  << endl ;
    // remove space
    for (  i=0 , j=0 ; buf[i] != '\0'; i++)
       if ( buf[i] != ' ')
           buf[j++] = buf[i] ;
    buf[j] = '\0' ;
    // parse expression
    wrk[1] = '\0' ;
    for (i=0 , k = -1  ; buf[i] != '\0'; i++ ) {
        switch ( buf[i]) {
            case '(':
            case ')':
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
                wrk[0] = buf[i] ;
                f = 1 ;
                if ( k != -1 ) {
                  buf[i] = '\0' ;
                  for ( n = k ; n < i ; n++ ) {
                    if ( !isdigit(buf[n]) && buf[n] != '.') {
                      cout << "incorrect number: " << (char*)&buf[k] << endl ;
                      return 1  ;
                    }

                  }

                  expresion.push((char*)&buf[k]);
                  k = -1 ;
                }
                expresion.push(wrk);
            break ;
            default :
              f = 0 ;
            break ;
        }

        if ( k == -1  && f == 0 )   k = i ;  // begin number

    }

    if ( k != -1 ) {
       for ( n = k ; n < i ; n++ ) {
          if ( !isdigit(buf[n]) && buf[n] != '.') {
            cout << "incorrect number: " << (char*)&buf[k] << endl ;
            return 1  ;
           }
       }

      expresion.push((char*)&buf[k]);

    }

/*

     while(!expresion.empty()) {
        string str =  expresion.front()  ;
        cout << str << endl;
        expresion.pop();
     }
     cout << endl;
*/

    return 0 ;
}


int is_number(string& s) {
    string::const_iterator it = s.begin();
    while (it != s.end() && (std::isdigit(*it) ||  *it == '.'  )) ++it;
    return !s.empty() && it == s.end();
}


int priority_is (char c ) {

    switch ( c )   {
        case '-':
        case '+':
          return 1 ;

        case '*':
        case '/':
          return 2 ;

        case '^':
          return 3 ;

        case '(':
        case ')':
          return 4 ;

        default :
          return 0 ;

    }
    return 0 ;

}


int convert ()  {
    stack< char > charStack;
    string str ;
    char c[2] , b[2] ;
    int i , j ;

    c[1] = '\0' ; b[1] = '\0';
    while(!expresion.empty()) {
        str =  expresion.front()  ;
        expresion.pop();
        if ( is_number ( str) ) {
           expresion_polish.push(str);
           continue ;
        }

        c[0] =  *str.c_str()  ;
        if(c[0] == '(') {
			charStack.push(c[0]);
			continue ;
        }

        i =  priority_is ( c[0]  );
        if ( i < 4 ) {
          while ( !charStack.empty() ) {
            b[0] = charStack.top() ;
            j = priority_is ( b[0]  );
            if ( j < 4 && j >= i ) {
              expresion_polish.push(b);
              charStack.pop() ;
            }
            else  break ;
          }
          charStack.push(c[0]);
        }
        else {  //  case ')'
          // put opertors
          while ( !charStack.empty() ) {
            b[0] = charStack.top() ;
            if ( b[0] != '(') {
              expresion_polish.push(b);
              charStack.pop() ;
            }
            else {
             charStack.pop() ;
             break ;
            }
          }  // end of while
          if ( b[0] != '(') {
             cout << "the number of brackets incorrect" << endl ;
             return 1 ;
          }

       }  // end of else

   }  // end of expression

   while ( !charStack.empty() ) {
    c[0] = charStack.top() ;
    charStack.pop() ;
    expresion_polish.push(c);
    if ( c[0] == '(') {
     cout << "the number of brackets incorrect" << endl ;
     return 1 ;
    }

   }

   return 0 ;
}


