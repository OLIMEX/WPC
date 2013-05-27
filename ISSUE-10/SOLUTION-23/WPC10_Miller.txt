// OLIMEX Weekend Programming Challenge Issue-10  WPC10
// Problem:
//          Let 0 < (a/b) < 1 where a and b are positive integers.
//          Make program which enters the numbers a and b then represent a/b with as
//          sum of numbers 1/n + 1/n2 + 1/n3бн and prints the n numbers.

// Language: C++
// Date: 27/05/2013
// Miller Wang

// Test results:
// 1) Input a=2    b=3   result 2  6
// 2) Input a=6    b=7   result 2  3  42
// 3) Input a=2    b=7   result 4  28
// 4) Input a=3    b=7   result 3  11  231
// 5) Input a=1    b=2   result 2
// 6) Input a=6    b=9   result 2  6
// 7) Input a=3    b=11  result 4  44
// 8) Input a=100  b=101 result 2  3  7  72  50904
// 9) Input a=5    b=4   result error!

#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{
	long a, b, n;	
	cout<<"Input two positive integers:"<<endl;   // Input a, b.
	cout<<"a=";
	cin>>a;
	cout<<"b=";
	cin>>b;
	cout<<"Output:"<<endl;
	
	
	if(a>0 && b>0 && a<b)     // Check if a and b are positive integers and a<b.
	{
		for(n=2; a>=1; n++)
			if((double)a/b >= (double)1/n)     // Compare a/b and 1/n
			{
				
				if(a>1)           // If a/b > 1/n and a>1
				{
					a=a*n-b;      // Let a/b = a/b - 1/n = (a*n-b)/(b*n) so that a = a*n-b.
					b=b*n;        // And then b = b*n
					cout<<n<<"\t";     //When a>1, print n.
				}
				else     // a=1
				{
					cout<<b<<endl;     // The last n is b.
					break;
				}
				
			}
			cout<<endl;
	}
	
	else
		cout<<"Input data error!"<<endl;	
	system("pause");	
	return 0;	
}