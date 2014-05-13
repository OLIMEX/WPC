#ifndef LC_H
#define LC_H

/*
 * Lineair congruential generator
 */

class Congruential
{
  public:
        unsigned int Next();
  private:
        unsigned int seed;
};

#endif // LC_H
