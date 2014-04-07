#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

void Gregorian ( int Year ) {
int a = Year % 19 ;
int b = floor (Year / 100);
int c = Year % 100 ;
int d = floor (b / 4);
int e = b % 4 ;
int f = floor ((b + 8) / 25);
int g = floor((b-f+1)/3);
int h = ( 19 * a + b - d - g + 15 ) % 30 ;
int i = floor (c / 4) ;
int k = c % 4;
int L = (32 + 2*e + 2*i - h - k) % 7 ;
int m = floor ((a + 11*h + 22*L) / 451) ;
int month = floor ((h+L-7*m+114)/31);
int day = ((h+L-7*m+114)%31)+1;
cout << "Gregorian : " <<  day << ".0" << month << "." << Year << endl ;
return ;
}

void Julian ( int Year ) {
int a = Year % 4 ;
int b = Year % 7 ;
int c = Year % 19 ;
int d = ( 19 * c + 15) % 30 ;
int e = ( 2 * a + 4 * b - d + 34) % 7 ;
int month = floor ((d + e + 114) / 31) ;
int day = ((d+e+114)%31)+1;
cout << "Julian : " <<  day << ".0" << month << "." << Year << endl ;
return ;
}

int main()
{
cout << "Input year : ";
int Year ;
cin >> Year ;
Gregorian(Year) ;
Julian(Year) ;
return 0 ;
}
