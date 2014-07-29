//
//  Created by Michael Dreher on 26.07.14.
//  Copyright (c) 2014 Michael Dreher. All rights reserved.
// License: public domain

#include <iostream>
#include <math.h>

inline void CheckAndPrintSolution(long fact1, const long& result)
{
	long fact2 = result / fact1;
	long remain2 = result % fact1;
	
	if(remain2 == 0)
	{
		char strFact1[32] = "";
		char strFact2[32] = "";
		
		sprintf(strFact1, "%ld", fact1);
		sprintf(strFact2, "%ld", fact2);
		if(!strchr(strFact1, '0') && !strchr(strFact2, '0'))
		{
			printf("%s * %s = %ld\n", strFact1, strFact2, result);
			
			// there is a second solution when the two factors are interchanged and are not equal
			if(fact2 != fact1)
				printf("%s * %s = %ld\n", strFact2, strFact1, result);
		}
	}
}

// fastest solution, needs one try
void FindMillionFactors1()
{
	// prime factorisation: 1000000 = 10^6 = (2*5)^6 = 2^6 * 5^6
	// any solution whose factors contains the prime factor 2 and prime factor 5 has a 0 at the end
	// so the allowed solutions (which don't contain a 0) have either
	// only 2^x or 5^y in it, but not both, so there is exactly one solutions left:
	// 2^6 * 5^6 (and its symetrical pair 5^6 * 2^6)
	static const long result = 1000000;
	static const long factor1 = 2*2*2*2*2*2;
	CheckAndPrintSolution(factor1, result);
}

// needs 28 tries
void FindMillionFactors2()
{
	// prime factorisation: 1000000 = 10^6 = (2*5)^6 = 2^6 * 5^6
	// check any combinations of these prime factors (stop in the middle (i<=3) because the solution space
	// is symetrical and only the first half is searched)
	static const long result = 1000000;
	for(long i = 0, pow2 = 1; i <= 3; i++, (pow2 *= 2)) // i is the number of '2's in factor1
	{
		for(long k = 0, pow5 = 1; k <= 6; k++, (pow5 *= 5)) // k is the number of '5's in factor1
		{
			// quick check if either the factor1 or factor2 contains both, '2' and '5' as prime factors
			// and will therefore end with a not allowed '0'
			if(! (((i != 0) && (k != 0)) // factor1 contains '2' and '5' as prime factors
			   || (k != 6))) // factor2 contains '5' as prime factors (factor2 always contains at least 2^3 as prime factors, so it's not necessary to check it)
			{
				CheckAndPrintSolution(pow2 * pow5, result);
			}
		}
	}
}

// slowest solution, needs 1000 tries
void FindMillionFactors3()
{
	static const long result = 1000000;
	static const long sqrtResult = sqrt(result) + 0.5;
	for(long i = 1; i <= sqrtResult; i++)
	{
		CheckAndPrintSolution(i, result);
	}
}


int main(int argc, const char * argv[])
{
	printf("=== FindMillionFactors1 ===\n");
	FindMillionFactors1();
	
	printf("\n=== FindMillionFactors2 ===\n");
	FindMillionFactors2();
	
	printf("\n=== FindMillionFactors3 ===\n");
	FindMillionFactors3();
	
	return 0;
}

