#ifndef SUBTRACTIVE_H
#define SUBTRACTIVE_H


class Subtractive
{
     public:
        Subtractive(unsigned int seed);
        unsigned int Next();
    private:
        unsigned int alpha;
        unsigned int beta;
        unsigned int state[55];
        void Generate(unsigned int seed);
};

#endif // SUBTRACTIVE_H
