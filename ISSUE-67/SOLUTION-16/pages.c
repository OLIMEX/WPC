//Example code - sum of pages 9808

#include <stdio.h>
#include <stdint.h>

typedef uint8_t UInt8;
typedef uint16_t UInt16;
typedef uint32_t UInt32;


const UInt16 cu16_Sum = 9808u;


int main()
{
    UInt16 u16_start = 1;
    UInt16 u16_cntr = u16_start;
    UInt16 u16_endpg = u16_start;
    
    
    printf("Start calculation...\n\r");
    
    while (1)
    {
	while (u16_cntr < cu16_Sum)
	{
	    u16_cntr += ++u16_endpg;
	}
	
	if ( (u16_cntr-cu16_Sum) == 0)
	    break;
	else
	{
	    u16_start++;
	    u16_cntr = u16_start;
	    u16_endpg = u16_start;
	}
    }
    
    printf("Result is page '%d' to page '%d'.\n\r", u16_start, u16_endpg);
    
    return 0;
}
