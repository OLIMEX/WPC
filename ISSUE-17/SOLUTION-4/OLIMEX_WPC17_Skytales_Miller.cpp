// OLIMEX Weekend Programming Challenge Issue-17  WPC17

// Problem:
//          Write code which crypt and de-crypt message on Skytale, as input
//          you can take message and diameter of the rod.
// Language: C++
// Date: 14/07/2013
// Miller Wang
//
// Test:
//        Input: s="abcdefghijklmnopqrstuvwxyz0123456789"
//        Input: d=5
// Result:
//        Output:
//              afkpuz49
//              bglqv05
//              chmrw16
//              dinsx27
//              ejoty38

#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

int main()
{
    string s;
    int i=0, d, j;
    cin>>s>>d;
    for(j=0; j<d; i=j+1, j++, cout<<endl)   while((i=i+d) < s.length()+d)   cout<<s[i-d];
    system("pause");
    return 0;
}
