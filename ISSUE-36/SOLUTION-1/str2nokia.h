/* 
 2013-12-06 by kantal59
 License: LGPL
 OLIMEX WPC#36: NOKIA text message converter
         Make code which takes string and convert it to button push sequence on NOKIA1100 phone keypad 
         which will print same string. For instance: HELLO -> 44 33 555 555 666
         
         The code uses english letters only.
*/


#ifndef _STR2NOKIA_H
#define _STR2NOKIA_H


#define NBTNS    10
#define NCHARS    7
#define FILLBTN  '0'    // button for wrong char

typedef struct { char id; char ch[NCHARS+1]; } btn_t;


btn_t keypad[NBTNS]={ 
// This table may be wrong, you can correct it :) 
    {'0', ' ', },   // which button results in the '0' char when pressing repeatedly?
    {'1', ".,?!'\"1"    },
    {'2', "abc2"   },
    {'3', "def3"   },
    {'4', "ghi4"   },
    {'5', "jkl5"   },
    {'6', "mno6"   },
    {'7', "pqrs7"  },
    {'8', "tuv8"   },
    {'9', "wxyz9"  },
  };


//---------------------------------------------------------
    void str2nokia( char *istr, char *obuff, size_t size )
//---------------------------------------------------------
/*  istr: input string;  
    ostr: pointer to output buffer; 
    size: size of the output buffer;
    The output will be 0-terminated if size is not zero.
*/
{

 int b,c,rep,found;
 char *rp, *wp;

 if( !size) return; 
 rp= istr;    wp= obuff;     *wp=0;
 
 while( *rp &&  (wp-obuff+1)<size ){
 
    found=0;
    for( b=0; b<NBTNS; b++){
        for( c=0; c<NCHARS; c++){
        
            if( tolower(*rp)==keypad[b].ch[c] ){ 
                for( rep=0; rep<c+1; rep++) *wp++= keypad[b].id;
                if( (wp-obuff+1)<size ) *wp++=' ';  // buttons separated with space
                found=1;
                break;
            }
        }    
        if( found) break;
        
    }
    if(!found) *wp++= FILLBTN;
    rp++;
    
 } 
 
 *wp=0;

}

#endif

