//============================================================================
// Name        : Olimex20140711.cpp
// Author      : Nicolas Gay
// Version     :
// Copyright   : 
// Description : Hi Olimex guys, here is my solution.
// of course not the cleanest one, but it works!
// it takes into account the special case of "-" as first sign before "1" number
// 1) generate an array were each line contains a sub array; each entry of
// the sub-array indicates a number of digits; sum of elements in a line is equal to 9 as there are 9 digits which can be used
// 2) use the first array to generate another array uidentical in term of size; but "number of digits" values are
// here changed into the corresponding values, depending on their position in the entry
// for example, if a line provided by step 1 was "3;4;1;1", array provided by step 2 will be "123;4567;8;9"
// 3) for each line of array provided by step, apply all possible combination of "+/-" before each number to find a unique equation result
// 4) keep only equations where result is 100
//============================================================================



#include <iostream>
#include <cassert>
#include <cmath>
#include <cstdio>

using namespace std;

// number of values to play with (between 1 and 9 => 9)
#define NB_VALUES 9


#define NB_LINES 512

#define REQUIRED_RESULT 100

// how many solutions??
unsigned int weekEndProgLanguageSolution = 0;

// array with all combination of digits
// one line (first dimension) = 1 combination
// one entry (second dimension) = number of digits for the nth number
// a zero value entry indicates that all digits were used
unsigned int NbDigitsCombiTab[NB_LINES][NB_VALUES] = {0};

// array with all combination VALUES, based on al combination of digits contained in NbDigitsCombiTab
// one line (first dimension) = 1 combination
// one entry (second dimension) = number of digits for the nth number
// a zero value entry indicates that all digits were used
unsigned int ValuesCombiTab[NB_LINES][NB_VALUES] = {0};


// provides the positive integer number made of nbDigits, where first digit is firstVal
// so positive number made of (firstVal), (firstVal+1), (firstVal+2), ... (firstVal+nbDigits-1)
unsigned int GetNumber(unsigned int firstVal, unsigned int nbDigits)
{
	unsigned int returnValue = 0;

	unsigned int lastVal = firstVal + nbDigits - 1;

	for (unsigned int i=0; i<nbDigits; i++)
	{
		returnValue += (lastVal-i)*std::pow(10,i);
	}

	return returnValue;
}


// Recursive function
// provides all combinations of number of digits whose sum provides N
// N: result of sum of groups of digits
// lineId: id of the next line to be fulfilled with results in Tab (first dimension)
// internalIndex: id inside a tab line, to identify the next location of the result sub number
void FournirCombi(int N, int& lineId, int internalIndex)
{
	int oldLineId = lineId;

	if (N==0 || internalIndex>=NB_VALUES)
	{
		lineId++;
		return;
	}

	// for each first number possible
	for (int i=1; i<=N; i++)
	{
		if (oldLineId != lineId)
		{
			for (int j=0; j<internalIndex; j++)
			{
				assert(lineId<NB_LINES);
				NbDigitsCombiTab[lineId][j] = NbDigitsCombiTab[lineId-1][j];
			}
		}

		NbDigitsCombiTab[lineId][internalIndex] = i;
		FournirCombi(N-i, lineId, internalIndex+1);
	}
}


// fullfills ValuesCombiTab array (see declaration above)
void GenerateAllCombinationOfNumbers()
{
	for (unsigned int lineNumber = 0 ; lineNumber < NB_LINES; lineNumber++)
	{
		unsigned int currentVal = 1;
		for (unsigned int identifier = 0 ; identifier < NB_VALUES; identifier++)
		{
			if (NbDigitsCombiTab[lineNumber][identifier]==0)
			{
				break;
			}
			else
			{
				ValuesCombiTab[lineNumber][identifier] = GetNumber(currentVal, NbDigitsCombiTab[lineNumber][identifier]);
				currentVal += NbDigitsCombiTab[lineNumber][identifier];
			}
		}
	}
}



// uses the binary format of numbers to evaluate all combinations of +/- for the required number of elements in the equation!
// for example if vals contains 3 values : "123", "4567", "89", there are different 2^3 combinations of +/- to play with:
// --- (000 in binary)
// --+ (001)
// -+- (010)
// -++ (011)
// +-- (100)
// +-+ (101)
// ++- (110)
// +++ (111)
// so using binary format of values between 0 and ((2^3)-1) is adapted!; just need then to use SHL to identify + or -
void DoCalculation(unsigned int* vals)
{
	unsigned int nbVals = 0;
	for (unsigned int i=0; i<NB_VALUES; i++)
	{
		if (vals[i]==0)
		{
			nbVals = i;
			break;
		}
	}
	if (nbVals==0)
	{
		nbVals=9;
	}

	unsigned int nbCombinationOfSigns = std::pow(2, nbVals);

	// for each combination of + and -
	for (unsigned int suiteDeSignes = 0; suiteDeSignes<nbCombinationOfSigns; suiteDeSignes++)
	{

		int value = 0;
		std::string formulae("");
		char tempString[50];
		// the nbVals LSbits of suiteDeSigned indicate the signs
		for (unsigned int i=0; i<nbVals; i++)
		{
			unsigned int indicateurSigne = (suiteDeSignes & (1 << (nbVals-i-1)));
			if (indicateurSigne>0)		// this is + !!
			{
				value += vals[i];
				sprintf(tempString, "+%i", vals[i]);
				formulae += tempString;
			}
			else		// this is - !!
			{
				value -= vals[i];
				sprintf(tempString, "-%i", vals[i]);
				formulae += tempString;
			}
		}

		if (value==REQUIRED_RESULT)
		{
			cout << formulae << "=" << REQUIRED_RESULT << endl;
			weekEndProgLanguageSolution++;
		}
	}

}

int main() {

	int linenumber = 0;
	FournirCombi(NB_VALUES, linenumber, 0);

	GenerateAllCombinationOfNumbers();

	for (int i=0; i<linenumber; i++)
	{
		DoCalculation(ValuesCombiTab[i]);
	}

	cout << "Number of Equations with the result: " << weekEndProgLanguageSolution << endl;

	return 0;
}
