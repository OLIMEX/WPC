#include "subtractive.h"
#include <limits.h>
#include <iostream>

Subtractive::Subtractive(unsigned int seed)
{
    Generate(seed);
}

void Subtractive::Generate(unsigned int seed)
{
    signed int temp = 1;
	state[0] = seed % 1000000000;
	state[1] = 1;

	for (int i = 1, j = 21; i < 55; i++, j += 21)
    {
		if (j >= 55)
		  j = j - 55;

		state[j] = temp;
		temp = seed - temp;

		if (temp < 0)
            temp += 1000000000;

		seed = state[j];
	}

	alpha = 0;
	beta = 24;

	for (int i = 0; i < 165; i++)
        Next();
}

unsigned int Subtractive::Next()
{
	if (alpha == beta)
        Generate(0);

	if (alpha == 0)
        alpha = 54;
    else
        alpha--;

	if (beta == 0)
        beta = 54;
    else
        beta--;

    signed int temp = state[alpha] - state[beta];

	if (temp < 0)
        temp += 1000000000;

    state[alpha] = temp;

	return state[alpha];
}

