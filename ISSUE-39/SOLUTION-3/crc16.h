/* 
 2014-01-12 by kantal59
 License: LGPL
 Compile: gcc -o crc16  crc16.c
 OLIMEX WPC#39: CRCR-16
                Cyclic Redundancy Check is error detecting code used in serial devices to detect accidental errors in the input data.
                Make code which calculates CRC-16.    
                
                In the current implementation, the message size (M32SIZE) is fixed. 
                I hope there is no endianess problem :-). 
*/

#ifndef _CRC16_H
#define _CRC16_H


// x^16 + x^15 + x^2 +1     IBM CRC-16; divisor length: 17 bits; max message length: 2^15-1 bits == 4095 bytes == 1023 uint32_t
uint32_t divisor= 0x018005; 
#define DSIZE     17            // divisor size in bits     
#define DIVMSB    15            // the place of the 1st non zero bit in the divisor counting from left and starting with 0.
#define MSBMASK  0x80000000     // uint32_t


// M32SIZE: message length in uint32_t units
//#define M32SIZE     100         // 400 bytes
#define M32SIZE     2             // it is low for debug purpose only. 

#define M8SIZE      (M32SIZE*sizeof(uint32_t))
#define M16SIZE     (M32SIZE*2)
// The message:
typedef union {
    uint32_t m32[ M32SIZE];    
    uint8_t  m8[ M8SIZE]; 
    int16_t  m16[ M16SIZE];   
} msg_t;


// The packet contains the message and the CRC:
typedef struct {
    msg_t    msg;
    uint16_t crc;
} packet_t;


void pdebug( uint32_t *ppack, size_t wno, int bno); // forward decl.


//--------------------------------------------------------------
    int make_crc( packet_t* ppack, int check, int debug)
/*--------------------------------------------------------------
 It calculates the CRC for the message in the given packet. 
 Input:  ppack: the pointer to the packet; 
         check: 0: no check, the calculated CRC will be stored in the ppack structure.
                1: the ppack->crc and the newly calculated one are to be compared, 
                   but the ppack structure is not to be overwritten.
 Output: if check off: it returns 1;  if check on: returns 1/0 if the CRC is OK/wrong
--------------------------------------------------------------*/    
{
 size_t wno; // word no.
 int bno;    // bit no.
 uint32_t tmp;
 uint16_t *pcrc;
 static uint32_t packet[ M32SIZE+1];  // Work area. For great M32SIZE, it shoud be allocated from the heap.
 
 memcpy( packet, ppack->msg.m8, M8SIZE ); 
 packet[M32SIZE]=0;
 
 for( wno=0, bno=0, tmp= packet[0];   ;  ){
 
    if( tmp & MSBMASK ){ 
    
            if( debug) pdebug( packet, wno,bno);
            
            if( bno<= DIVMSB ){  packet[wno]^= divisor<<(DIVMSB-bno);  }
            else{
                    packet[wno]^= divisor >> (bno-DIVMSB);
                    packet[wno+1]^= divisor << (32-(bno-DIVMSB));
            }
            tmp= packet[wno]<<bno;  // refreshes and reconstructs the shift position
    }
    
    bno++;
    if( bno==32 ){ 
        bno=0;
        if( ++wno == M32SIZE) break;
        tmp= packet[wno];
    }    
    else  tmp<<=1;
 
 } 
 
 if( debug) pdebug( packet, wno,bno);
 
 /* The CRC value must be copied from the work area into the package. 
    packet[ M32SIZE] was initialized to 0 and now contains the CRC value in one of the half part (endianess).
    If the CRC equal to 0, then both part are 0. TODO: to test beetwen different arhitecture.
 */
 pcrc= ( uint16_t *) &(packet[ M32SIZE]); 
 
 if( check){
        return( (pcrc[0] ? pcrc[0] : pcrc[1])  ==  ppack->crc);
 }
 
 ppack->crc= pcrc[0] ? pcrc[0] : pcrc[1];   
 
 return( 1 );
}


//--------------------------------------------------------------
     void pdebug( uint32_t *ppack, size_t wno, int bno)
/*--------------------------------------------------------------
 It prints debug information.
--------------------------------------------------------------*/
{
    size_t w; int b, dlth, shift, flag;
    size_t size= M32SIZE+1;
    
    printf("wno=%zd; bno=%d\n", wno,bno);
    for( w=0; w<size; w++){
        for(b=0; b<32; b++){  
            if( (ppack[w]<<b) & MSBMASK ) printf("1");
            else printf("0");
    
        }
        printf(" ");
    }
    puts(" ");
    
    dlth= DSIZE;
    shift= DIVMSB;
    flag=0;
    for( w=0; w<size; w++){
        for(b=0; b<32; b++){ 
            if( w==wno && b==bno) flag=1;
            if( flag && dlth){
                dlth--;
                if( (divisor << shift) & MSBMASK ) printf("1");
                else printf("0");
                shift++;
            }
            else printf(" ");
    
        }
        printf(" ");
    }
    puts(" ");
}


#endif

