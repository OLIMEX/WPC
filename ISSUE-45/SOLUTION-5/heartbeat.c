// I don't understand from heartbeat . This solution may use as hypothesis. For additional
// information I use  http://openeeg.sourceforge.net/doc/modeeg/firmware/modeeg-p2.c
// this program is running under A20 Debian distribution
// compile & linking : gcc -o heartbeat heartbeat.c
// for run: ./heartbeat
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>

#define  INTERVAL   4
#define  AMPL       700
#define  DIST       10
#define  LIMIT      10000

int file_open ( void ) ;
int read_data ( void ) ;

struct modeeg_packet
{
	uint8_t		sync0;		// = 0xA5
	uint8_t		sync1;		// = 0x5A
	uint8_t		version;	// = 2
	uint8_t		count;		// packet counter. Increases by 1 each packet.
	uint8_t	    data[12];	// 10-bit sample (= 0 - 1023) in big endian (Motorola) format.
	uint8_t		switches;	// State of PD5 to PD2, in bits 3 to 0.
};

int fd ;
struct modeeg_packet p ;

int main()
{
    int i , k , n ,nmin , nmax  ;
    int pic[LIMIT/10] ,  lastpic , min , max , npic ;
    int data[LIMIT] ;

    if ( file_open()) return 1 ;
    n = 0 ;
    while ( !read_data() ) {
/*
        printf ( "sync0    : %x\t%d\n" , p.sync0 , p.sync0 ) ;
        printf ( "sync1    : %x\t%d\n" , p.sync1 , p.sync1 ) ;
        printf ( "version  : %x\t%d\n" , p.version , p.version ) ;
        printf ( "count    : %x\t%d\n" , p.count , p.count ) ;
        printf ( "switches : %x\t%d\n" , p.switches , p.switches ) ;
*/
        data[n] = p.data[0] * 256 + ((p.data[1] >> 6) & 0x3) ;
        ++n ;
        if ( n >= LIMIT  ) break ;
    }

    close ( fd ) ;
    lastpic = 0 ; npic = 0 ;
    for ( i=0 ; i < n - DIST ; ++i ) {
        // find  heartbeat pic
        min = 2048 ; max = 0 ; nmin=0 ; nmax=0;
        for (k=i ; k < i + DIST; k++ ) {
            if ( data[k] > max ) max = data[k] ;
            if ( data[k] < min ) min = data[k] ;
            if ( data[k] > 700 ) ++nmax  ;
            if ( data[k] < 10  ) ++nmin  ;
        }
        if ( (max - min) > AMPL && nmax > 3 && nmin > 3  ) {
                if ( lastpic + DIST < i ) {
                    lastpic =  i ;
                    pic[npic] = i ;
                    npic++ ;

                }
        }
    }
    // printf ( "npic %d\n" , npic ) ;
    --npic ;
    n = 0 ;
    for ( i=1 ; i <= npic ; i++)  {
        n = n + 60000 / ( (pic[i] - pic[i-1]) * INTERVAL );
    }
    printf ( "heartbeat = %d \n " , n / npic) ;
    return 0;
}


int file_open() {
    fd = open ( "in.txt", O_RDONLY) ;
    if ( fd < 0  ) return 1 ;
    return 0 ;
}

int read_data ( ) {
    char buf[16] ;
    int ret , i ;

    ret = read ( fd , buf , 2 );
    if ( ret != 2 ) return 1 ;
    buf[2] = 0 ;
    sscanf( buf  , "%X" ,(unsigned int*)&p.sync0 ) ;
    ret = read ( fd , buf , 2 );
    if ( ret != 2 ) return 1 ;
    buf[2] = 0 ;
    sscanf( buf  , "%X" ,(unsigned int*)&p.sync1 ) ;
    ret = read ( fd , buf , 2 );
    if ( ret != 2 ) return 1 ;
    buf[2] = 0 ;
    sscanf( buf  , "%X" ,(unsigned int*)&p.version ) ;
    ret = read ( fd , buf , 2 );
    if ( ret != 2 ) return 1 ;
    buf[2] = 0 ;
    sscanf( buf  , "%X" ,(unsigned int*)&p.count ) ;
    for ( i = 0 ; i < 6 ; i++ ) {
        ret = read ( fd , buf , 2 );
        if ( ret != 2 ) return 1 ;
        buf[2] = 0 ;
        sscanf( buf  , "%X" ,(unsigned int*)&p.data[i*2] ) ;
        ret = read ( fd , buf , 2 );
        if ( ret != 2 ) return 1 ;
        buf[2] = 0 ;
        sscanf( buf  , "%X" ,(unsigned int*)&p.data[i*2+1] ) ;
    }
    ret = read ( fd , buf , 2 );
    if ( ret != 2 ) return 1 ;
    buf[2] = 0 ;
    sscanf( buf  , "%X" ,(unsigned int*)&p.switches ) ;
    return 0 ;
}
