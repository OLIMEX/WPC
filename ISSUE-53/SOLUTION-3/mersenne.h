#ifndef MERSENNE_H
#define MERSENNE_H

/*
 * Mersenne twister
 * http://en.wikipedia.org/wiki/Mersenne_twister
 */

class Mersenne
{
    public:
        Mersenne(unsigned int seed);
        unsigned int Next();
    private:
        unsigned int index;
        unsigned int state[624];
        void Generate();
};

#endif // MERSENNE_H
