#include <stdio.h>

unsigned short crc_table[256];

void make_crc_table(void)
{
  unsigned short c;
  unsigned short n;
  int k; /* each bit */

/***
CRC-16 uses polynomial x**16 + x**15 + x**2 + x**0
represented by binary value 1000 0000 0000 0101 or 0x8005
reverse of binary value is 1010 0000 0000 0001 or 0xA001
***/
  for (n = 0; n < 256; n++) {
    c = (unsigned short) n;
    for (k = 0; k < 8; k++) {
      if (c & 1)
        c = 0xA001 ^ (c >> 1);
      else
        c >>= 1;
    }
    crc_table[n] = c;
  }
}
   
unsigned long find_crc(unsigned char *buf, int len)
{
  /* c is initalized as seed, change to 0xFFFF for "CRC-16 Modbus" */
  unsigned short c = 0x0;

  while (len--)
    c = crc_table[(c ^ *buf++) & 0xff] ^ (c >> 8);
  return c;
}
   
void main()
{
  make_crc_table();
  printf("0x%x\n", find_crc("123456789", 9));
/**
CRC is a linear function
crc(x ^ y) = crc(x) ^ crc(y)

**/
  
}
/** 
ref:
http://en.wikipedia.org/wiki/Cyclic_redundancy_check
http://www.w3.org/TR/PNG/#D-CRCAppendix
http://www.rsdn.ru/forum/alg/4218728.flat
http://automationwiki.com/index.php?title=CRC-16-CCITT
http://www.digi.com/wiki/developer/index.php/Python_CRC16_Modbus_DF1
http://www.lammertbies.nl/comm/info/crc-calculation.html
http://www.modbustools.com/modbus_crc16.htm
http://www.control.com/thread/1381836105
**/

