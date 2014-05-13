#include "lc.h"

unsigned int Congruential::Next()
{
    seed = (seed * 1103515245 + 12345) % 2147483648U;
    return seed;
}
