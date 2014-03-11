// I don't understand from heartbeat . This solution may use as hypothesis. For additional
// information I use  http://openeeg.sourceforge.net/doc/modeeg/firmware/modeeg-p2.c
// this program is running under A20 Debian distribution
// compile & linking : gcc -o median_filter median_filter.c
// for run: ./median_filter

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
    int i ,  k , n  , lastpic ;
    int pic[LIMIT/10] ,   npic ;
    int save[LIMIT] ;
    int data[LIMIT] ;
    int wrk[5] , j , a , b , tmp;


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
        save[n] = p.data[0] * 256 + ((p.data[1] >> 6) & 0x3) ;
        ++n ;
        if ( n >= LIMIT  ) break ;
    }
    close ( fd ) ;
    k = 0 ;

    // insert median filter ( 5 numbers )
    for ( i = 4 ; i < n ; i++ ) {
       for ( j = 0  ; j <=4 ; j++  ) wrk[j] = save[i-4+j] ;
       for ( a = 0 ; a < 4 ; a++ )
            for ( b = a + 1; b < 5 ; b++ )
            if ( wrk[a] < wrk[b]) {
                tmp = wrk[a] ;
                wrk[a] = wrk[b] ;
                wrk[b] = tmp ;

            }

       data[k] = wrk[2] ; // median
//     printf ( "%d\t%d\n" , data[k], k ) ;
       k++;
    }
    npic = 0 ;  lastpic =  0 ;
    for ( i=2 ; i < k  ; ++i ) {
        // find  heartbeat pic , use result median  filter
        if ( abs (data[i] - data[i-2]) > 700 || abs (data[i] - data[i-1]) > 700 ) {
            if ( lastpic + DIST < i  ) {
                pic[npic] = i ;
                npic++ ;
                lastpic = i ;
            }
        }
    }

    //printf ( "npic %d\n" , npic ) ;
    --npic ;
    n = 0 ;
    for ( i=1 ; i <= npic ; i++)  {
        n = n + 60000 / ( (pic[i] - pic[i-1]) * INTERVAL );
    }

    printf ( "heartbeat  rate = %d \n " , n / npic) ;

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
