#define LITTLE_ENDIAN 0
#define BIG_ENDIAN 1
#define NO_ENDIAN 2

#include <stdio.h>

int getEndian( void )
{
    union 
    {
      char  c[ sizeof( int ) ];
      int i;
    } testint;

    testint.i = 0x01;

    if (0x01 == testint.c[sizeof(int)])
    {
      return LITTLE_ENDIAN;
    }
    else if (0x01 == testint.c[0])
    {
      return BIG_ENDIAN;
    }
    else
    {
	return NO_ENDIAN;
    }
}

int main (void)
{
  int result = NO_ENDIAN;

  result = getEndian();
  if (LITTLE_ENDIAN == result)
printf("Little endian detected");
  if (BIG_ENDIAN == result)
printf("Big endian detected");
  if (NO_ENDIAN == result)
printf("No endian detected");

  return 0;
}
