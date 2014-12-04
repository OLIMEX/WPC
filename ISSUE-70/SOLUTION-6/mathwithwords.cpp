#include <iostream>
#include <map>
#include <string>
#include <cstdlib>

using namespace std;

map<string, int> NUMB;
void fill(void);
int analysis(void);
char sign;
int main()
{
    int num;
    sign = ' ';
    fill();
    int A = analysis();
    int B = analysis();
    switch(sign) {
        case '+':
            num = A+B;
        break ;
        case '-':
            num = A-B;
        break ;
        case '*':
            num = A*B;
        break ;
        case '/':
            num = A/B;
        break ;

        default:
            cout << "Error" << endl ;
            return 0 ;
    }
    cout << A << sign << B << "=" << num << endl ;
}


void fill(void){
NUMB["zero"] = 0;
NUMB["nought"] = 0;
NUMB["one"] = 1 ;
NUMB["two"] = 2 ;
NUMB["three"] = 3 ;
NUMB["four"] = 4 ;
NUMB["five"] = 5 ;
NUMB["six"] = 6 ;
NUMB["seven"] = 7 ;
NUMB["eight"] = 8 ;
NUMB["nine"] = 9 ;
NUMB["ten"] = 10 ;
NUMB["eleven"] = 11 ;
NUMB["twelve"] = 12;
NUMB["dozen"] = 12 ;
NUMB["thirteen"] = 13 ;
NUMB["fourteen"] = 14 ;
NUMB["fifteen"] = 15 ;
NUMB["sixteen"] = 16 ;
NUMB["seventeen"] = 17 ;
NUMB["eighteen"] = 18 ;
NUMB["nineteen"] = 19 ;
NUMB["twenty"] = 20 ;
NUMB["thirty"] = 30 ;
NUMB["forty"] = 40 ;
NUMB["fifty"] = 50 ;
NUMB["sixty"] = 60 ;
NUMB["seventy"] = 70 ;
NUMB["eighty"] = 80 ;
NUMB["nineteen"] = 90 ;
NUMB["hundred"] = 100 ;
NUMB["thousand"]=1000;
NUMB["hundreds"] = 100 ;
NUMB["thousands"]=1000;
NUMB["and"]=0;
NUMB["plus"]=-1;
NUMB["minus"]=-2;
NUMB["multiplication"]=-3;
NUMB["divide"]=-4;
}

int analysis (void) {
    string in;
    int sum1000 = 0,sum100=0,sum=0  ;  int N ;
    while ( !cin.eof()) {
        cin >> in;
        if ( NUMB.find(in) == NUMB.end()) {
            cout << "not found word" << in << endl;
             exit( 0 ) ;
        }
        N = NUMB[in];
        if (N == 100) {
           if ( sum != 0 ) {
            sum100 = sum * N;
            sum=0;
           }
           continue;
        }

        if (N == 1000) {
           if ( sum != 0 ) {
            sum1000 = (sum + sum100) * N;
            sum=0;
            sum100=0;
           }
           continue;
        }


         if ((N >= 0) && (N < 100)) {
             sum = sum + N ;
         }

         if ( N == -1 ) {
            sign = '+';
            break ;
         }
         if ( N == -2 ) {
            sign = '-';
            break ;
         }
         if ( N == -3 ) {
            sign = '*';
            break ;
         }

         if ( N == -4 ) {
            sign = '/';
            break ;
         }
    }
    sum = sum + sum100+sum1000;
    return sum;
}
