/*
* ============================================================================
*  Name         : main.cpp
*  Part of      : NOKIA text message converter
*  Description  : Developed for Olimex's Weekend Programming Challenge #36
*  Author       : Leon Anavi
*  Email        : leon@anavi.org
*
* ============================================================================
*/

#include <cctype>
#include <iostream>
#include <map>

using namespace std;

typedef map<char,int> keypad;

//declarations
void init(keypad& keypadDigits, keypad& keypadRepeats);

int main (int argc, char *argv[])
{
	if (2 != argc)
	{
		cout << "Please enter a word as an argument" << endl;
		return 1;
	}

	keypad keypadDigits;
	keypad keypadRepeats;
	
	init(keypadDigits, keypadRepeats);

	//print
	int nIter = 0;
	while ('\0' != argv[1][nIter])
	{
		char nChar = tolower(argv[1][nIter]);
		nIter++;
		if (keypadRepeats.end() == keypadRepeats.find(nChar))
		{
			//skip unknown characters
			continue;
		}

		int nRepeats = keypadRepeats[nChar];
		for (int nRepeater=0; nRepeater<nRepeats; nRepeater++)
		{
			cout << keypadDigits[nChar];
		}
		cout << ' ';
	}
	cout << endl;
	return 0;
}
//----------------------------------------------------------------------------

/**
 * Init keypad data structures
 *
 * @param keypadDigits 
 * @param keypadRepeats
 *
 * @return nothing
 * @throws nothing
 */
void init(keypad& keypadDigits, keypad& keypadRepeats)
{
	//init keypad
	keypadDigits[' '] = 0;
	keypadRepeats[' '] = 1;

	keypadDigits['a'] = 2;
	keypadRepeats['a'] = 1;
	keypadDigits['b'] = 2;
	keypadRepeats['b'] = 2;
	keypadDigits['c'] = 2;
	keypadRepeats['c'] = 3;

	keypadDigits['d'] = 3;
	keypadRepeats['d'] = 1;
	keypadDigits['e'] = 3;
	keypadRepeats['e'] = 2;
	keypadDigits['f'] = 2;
	keypadRepeats['f'] = 3;

	keypadDigits['g'] = 4;
	keypadRepeats['g'] = 1;
	keypadDigits['h'] = 4;
	keypadRepeats['h'] = 2;
	keypadDigits['i'] = 4;
	keypadRepeats['i'] = 3;

	keypadDigits['j'] = 5;
	keypadRepeats['j'] = 1;
	keypadDigits['k'] = 5;
	keypadRepeats['k'] = 2;
	keypadDigits['l'] = 5;
	keypadRepeats['l'] = 3;

	keypadDigits['m'] = 6;
	keypadRepeats['m'] = 1;
	keypadDigits['n'] = 6;
	keypadRepeats['n'] = 2;
	keypadDigits['o'] = 6;
	keypadRepeats['o'] = 3;

	keypadDigits['p'] = 7;
	keypadRepeats['p'] = 1;
	keypadDigits['q'] = 7;
	keypadRepeats['q'] = 2;
	keypadDigits['r'] = 7;
	keypadRepeats['r'] = 3;
	keypadDigits['s'] = 7;
	keypadRepeats['s'] = 4;

	keypadDigits['t'] = 8;
	keypadRepeats['t'] = 1;
	keypadDigits['u'] = 8;
	keypadRepeats['u'] = 2;
	keypadDigits['v'] = 8;
	keypadRepeats['v'] = 3;

	keypadDigits['w'] = 9;
	keypadRepeats['w'] = 1;
	keypadDigits['x'] = 9;
	keypadRepeats['x'] = 2;
	keypadDigits['y'] = 9;
	keypadRepeats['y'] = 3;
	keypadDigits['z'] = 9;
	keypadRepeats['z'] = 4;
}
//----------------------------------------------------------------------------
