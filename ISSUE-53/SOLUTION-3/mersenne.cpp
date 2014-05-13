#include "mersenne.h"
#include <limits.h>

Mersenne::Mersenne(unsigned int seed)
{
    index = 0;
    state[0] = seed;
    for (unsigned int i = 1; i <= 623; i++)
    {
        state[i] = 1812433253 * (state[i-1] ^ (state[i-1] >> 30)) + i;
    }
}

void Mersenne::Generate()
{
    for (unsigned int i = 1; i <= 623; i++)
    {
        unsigned int x;
        x = (state[i] & 0x80000000) + (state[(i+1) % 624] & 0x7fffffff);
        state[i] = state[(i + 397) % 624] ^ (x >> 1);
        if ((x % 2) != 0)
        {
            state[i] = state[i] ^ 2567483615U;
        }
     }
}

unsigned int Mersenne::Next()
{
    if (index == 0)
        Generate();

     unsigned int x = state[index];
     x = x ^ (x >> 11);
     x = x ^ ((x << 7) & 2636928640U);
     x = x ^ ((x << 15) & 4022730752U);
     x = x ^ (x >> 18);

     index = (index + 1) % 624;
     return x;
}

