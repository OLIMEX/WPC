/* 
 2013-11-03 by kantal59
 License: LGPL
 Compile: gcc -o rle  rle.c

 OLIMEX WPC#31: Run Length Encoding/Decoding
    RLE/D is the simplest way to compress data http://en.wikipedia.org/wiki/Run-length_encoding
    Implement RLE/D in shortest/simplest way possible using your favourite language.
    
    The solution encoded/decoded byte sequences.
   
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


unsigned char MARKER= '#';
char description[]="WPC31 RLE\n";

//-----------------------------------------------------------
        int encode( FILE* istream, FILE* ostream )
//-----------------------------------------------------------
{
 unsigned char count=0;
 unsigned char prevch;  // prevchar must be uchar!
 int ch;                // ch must be integer!
 int i;
 
 fputs( description, ostream);
 
 while( (ch=getc(istream)) != EOF   ||  count ){    
    
    if( !count){    prevch= ch;     count= 1;    continue;   }
    
    if( ch == prevch )  count++;    // EOF (0xffff/-1) will not be equal to 0xff
    
    if( ch != prevch    ||   count==255 ){
    
        if( prevch == MARKER ){  
         
                             putc(MARKER, ostream);     putc(count,ostream);    putc(MARKER, ostream);
        }
        else{
            if( count<3 ){
                        for( i=0;   i<count;    i++)    putc( prevch, ostream);
            }
            else{
                        putc(MARKER, ostream);      putc(count,ostream);    putc( prevch,ostream);
            }
        }
        
        if( count==255  ||  ch==EOF ) count=0; 
        else{
            prevch= ch;    count=1;
        }    
                
    }
                    
 } // while


 return(0);
}


//-----------------------------------------------------------
        int decode( FILE* istream, FILE* ostream )
//-----------------------------------------------------------
{
 unsigned char count=0;
 int ch;                // ch must be integer!
 int i, mark=0;
 char desc[ sizeof(description)];
 
 i= fread( desc, 1, sizeof( desc)-1, istream);      
 desc[ sizeof( desc)-1]= 0;
 if( strcmp( description, desc) != 0 ) return(-1);
 
 
 while( (ch=getc(istream)) != EOF ){
       
    if( mark ){
        
        if( !count ){   count= ch;      continue;   }  
        
        for( i=0;   i< count;   i++)    putc( ch, ostream);
        
        mark=0; count=0;
        continue;
    }    
    
    if( ch==MARKER){    mark=1;     continue; }
    putc( ch, ostream);
    
 }
 
 
 if( mark || count) return(-2); // error
 return(0);

}



/**************************************************************
       T E S T   T E S T   T E S T   T E S T   T E S T
**************************************************************/
typedef struct {
    FILE *istream;
    FILE *ostream;
} handles_t;   
 
//--------------------------------------------------------------
        void escape( handles_t *hnd, int rtcd, char *msg)
//--------------------------------------------------------------
{
    if( hnd->istream )  fclose( hnd->istream);
    if( hnd->ostream )  fclose( hnd->ostream);
    if( !rtcd) return;
    perror( msg);
    exit( rtcd);
}


//--------------------------------------------------------------
        int main( int argc, char *argv[])
//--------------------------------------------------------------
{
 int rtcd;
 char *finput, *foutput;
 char *msg= "\n Usage: $ rle  [-d]  input_file  output_file\n -d : decompress\n";

 handles_t hnd;         hnd.istream=NULL,       hnd.ostream= NULL;
 
 if( argc==3    &&  argv[1][0]!='-'   ){    finput= argv[1];    foutput= argv[2];   }    
 else{
         if( argc==4  &&    argv[1][0]=='-'    &&   argv[1][1]=='d' ){  finput= argv[2];    foutput= argv[3];   }
         else{ 
                puts(msg);
                return(1);
         }       
 }         
         
 
 if( ( hnd.istream= fopen( finput,"r")) ==NULL )  escape( &hnd, 1, "Input file error");  
 if( ( hnd.ostream= fopen( foutput,"w")) ==NULL )  escape( &hnd, 2, "Output file error"); 
      
 if( argc!=4){  puts("\n...encoding");      encode( hnd.istream, hnd.ostream );     }
 else{
        puts("\n...decoding");
        rtcd= decode( hnd.istream, hnd.ostream );
        if( rtcd==-1 ) puts("Invalid input file format\n");
        if( rtcd==-2) puts("Wrong input byte stream\n");
 }   

 
 escape( &hnd,0,"");

 return(0);
}


