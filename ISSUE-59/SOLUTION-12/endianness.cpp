/*=============================================================================\
| BIG/little endian byte order tester                                          |
|______________________________________________________________________________|
|                                                                              |
| Author: Yordan Naydenov                                                      |
|                                                                              |
| Language: C++ (International Standard ISO/IEC 14882:2011)                    |
|                                                                              |
| Description: The code detects the byte order of the machine (endianness)     |
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


bool isBIGendian()
{
  constexpr std::uintmax_t _1 { 1U };

  return !(*((std::uint8_t*)(&_1)));
}


int main()
{
  if(isBIGendian())
    std::cout << "Big endian order.\n";
  else
    std::cout << "Little endian order.\n";

  return EXIT_SUCCESS;
}
