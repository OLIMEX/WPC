#include <iostream>

using namespace std;

// Gregorian Easter - Meeus algorithm

void gregorianEasterMeeus(int year){
int a,b,c,d,e,f,g,h,l,m,n,month,day;
    a = year % 19;
    b = year / 100;
    c = year % 100;
    d = b / 4;
    e = b % 4;
    f = (b + 8) / 25;
    g = (b - f + 1) / 3;
    h = (19 * a + b - d - g + 15) % 30;
    l = (32 + 2 * e + 2 * (c / 4) - h - (c % 4)) % 7;
    m = (a + 11 * h + 22 * l) / 451;
    n = h + l - 7 * m + 114;
    month = n / 31;
    day = n % 31 + 1;
    cout<<"Month: "<<month<<" Day: "<<day;

};
// Julian Easter - Meeus algorithm
void julianEasterMeeus(int year){
  int a,b,c,d,e,f,month,day;
  a = year % 4;
  b = year % 7;
  c = year % 19;
  d = (19 * c + 15) % 30;
  e = (2 * a + 4 * b - d + 34) % 7;
  f = d + e + 114;
  month = f / 31;
  day = f % 31 + 1;
 cout<<"Month: "<<month<<" Day: "<<day;
}

int main()
{
int year;
cout<<" Enter year: ";
cin>>year;
cout<<"Gregorian Easter :" ;
gregorianEasterMeeus(year);
cout<<endl;
cout<<"Julian Easter :" ;
julianEasterMeeus(year);




    return 0;
}
