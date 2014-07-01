// compile with something like g++ EndianDetect.cpp
// licensed CC0 as far as I'm concerned.

#include <iostream>

int main()
{
    unsigned int Test1 = 0xBE00001Eu;
    unsigned char Result1 = *reinterpret_cast<unsigned char*>(&Test1);
    if (Result1 == 0xBEu)
    {
        std::cout << "Executing as Big Endian." << std::endl;
    }
    else if (Result1 == 0x1E)
    {
        std::cout << "Executing as Little Endian." << std::endl;
    }
    else
    {
        std::cout << "Executing as something else (PDP Endian?)." << std::endl;
    }
    return 0;
}
