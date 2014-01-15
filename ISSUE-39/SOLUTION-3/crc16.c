/* 
 2014-01-12 by kantal59
 License: LGPL
 Compile: gcc -o crc16  crc16.c
 OLIMEX WPC#39: CRCR-16
                Cyclic Redundancy Check is error detecting code used in serial devices to detect accidental errors in the input data.
                Make code which calculates CRC-16.  
                
                It tests the CRC calculation. See the crc16.h!
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "crc16.h"

#define Check   1
#define Debug   1


int check( packet_t* ppack)
{
 int rtcd;
 if( (rtcd= make_crc( ppack, Check, !Debug)) ) puts( "CRC is OK" );
    else puts( "CRC error" );
 return(rtcd);
}
 
 
//--------------------------------------------- 
        int main( int argc, char *argv[])
//---------------------------------------------         
{
 int i; char ch; uint16_t crc;

// initialization examples:
 packet_t pack1= { .msg.m32={0x00000001, 0x00000008} }; 
 
 packet_t pack2= { .msg.m8={"12345678"} };
  
 packet_t pack3= { .msg.m16={0} };
 
 packet_t pack4;
 for(i=0, ch='a'; i< M8SIZE; i++, ch++)     pack4.msg.m8[i]= ch;
 
 packet_t pack5;
 for(i=0; i< M16SIZE; i++)     pack5.msg.m16[i]= i;
 
 
 //-------- calculations:
 
 make_crc( &pack1, !Check, Debug);  printf("pack1: 0x%X ", pack1.crc);
 check( &pack1);
 
 //------------------ 
 
 make_crc( &pack2, !Check, !Debug); printf("pack2: 0x%X ", pack2.crc);
 check( &pack2);
 
 //------------------ 
 
 make_crc( &pack3, !Check, !Debug); printf("pack3: 0x%X ", pack3.crc);
 check( &pack3);
 
 //------------------ 
 
 make_crc( &pack5, !Check, !Debug); printf("pack5: 0x%X ", pack5.crc);
 check( &pack5);
 
 // mess up:
 pack5.msg.m16[0]=100;
 pack5.msg.m16[M16SIZE-1]=500;
 check( &pack5);
 
 // correct it
 pack5.msg.m16[0]=0;
 pack5.msg.m16[M16SIZE-1]= M16SIZE-1 ;
 check( &pack5);
 
 // mess up again:
 pack5.msg.m16[M16SIZE-1]^= 1;
 check( &pack5);
 
 return(0); 
}

