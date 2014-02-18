/*
	Author: Sinan Zikri
	Date: 15th February 2014
	Problem: Make code which enters card number and validate it 
			 i.e. writes VALID or INVALID number has been entered.
	Used algorithm: Luhn algorithm -> http://en.wikipedia.org/wiki/Luhn_algorithm
*/

#include<iostream>
#include<string>
using namespace std;

bool IsValidNumber(string number)
{
	int len = number.length() - 1;
	int pos = 0;
	int num = 0;

	while(len >= 0)
	{
		pos++;

		if(pos % 2 == 0)
		{
			int n = 2 * (number[len] - '0');
			while(n >= 1)
			{
				num += n % 10;
				n = n / 10;
			}
		}
		else num += number[len] - '0';

		len--;
	}

	if(num % 10 == 0) return true;
	else return false;

}

int main()
{
	string cardNumber = "6011000593748746";
	//cin >> cardNumber;

	if(IsValidNumber(cardNumber)) cout << "VALID" << endl;
	else cout << "INVALID" << endl;

	return 0;
}