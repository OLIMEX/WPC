#include <iostream>
#include "mersenne.h"
#include "subtractive.h"
#include "lc.h"

using namespace std;

int main()
{

    Congruential c;
    for (int i=0; i<10; i++)
    {
        cout << "Lineair congruential: " << c.Next() << endl;
    }

    Subtractive s(12345);
    for (int i=0; i<10; i++)
    {
        cout << "Subtractive: " << s.Next() << endl;
    }

    Mersenne m(12345);
    for (int i=0; i<10; i++)
    {
        cout << "Mersenne: " << m.Next() << endl;
    }

    return 0;
}
