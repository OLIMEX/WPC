/*=============================================================================\
| BIG/little endian byte order tester                                          |
|______________________________________________________________________________|
|                                                                              |
| Author: Yordan Naydenov                                                      |
|                                                                              |
| Language: C++ (International Standard ISO/IEC 14882:2011)                    |
|                                                                              |
| Description: The templatized code detects the byte order of the machine      |
|               it is executed on.                                             |
|                                                                              |
| Created for Olimex Weekend Programming Challenge #59: "Big – Little Endians" |
|                                                                              |
| License: WTFPL (http://www.wtfpl.net/txt/copying)                            |
|                                                                              |
| Date: June 29, 2014                                                          |
|                                                                              |
\=============================================================================*/


#include <cstdint>
#include <iostream>
#include <cstdlib>


// Class template to encapsulate rather than generalize the byte order test code.
template<typename byte,
         typename word>
class endianness
{
  public:
    static bool isBIG()
    {
      return !(*((byte*)(&_1)));
    }

  private:
    static constexpr word _1 = 1U;
};


// Definition of the static data member so that its address can be referenced.
// Once defined, it exists even if no objects of its class have been created.
template<typename byte,
         typename word> constexpr word endianness<byte, word>::_1;


// Objects of type 'endianness' are not intended to be created.
typedef endianness<std::uint8_t,
                   std::uintmax_t> endian;



int main()
{
  if(endian::isBIG())
    std::cout << "Big endian order.\n";
  else
    std::cout << "Little endian order.\n";

  return EXIT_SUCCESS;
}
