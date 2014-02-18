/*
 2014-02-15 by kantal59
 License: LGPL
 Compile: gcc -o bcard  bcard.c
 
 OLIMEX WPC#43: Bank Card validation
             Bank card numbers are not random, they carry information for the card processor (Visa/Mastercard etc), 
            bank which issued the card, the account and checksum. More on the subject is available 
            at http://en.wikipedia.org/wiki/Bank_card_number .
            Make code which enters card number and validate it i.e. writes VALID or INVALID number has been entered.

            It uses the Luhn-algorithm.
            You can prepend 0s to have the min. requested length:  79927398713   --->  0079927398713
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define MAXLENGTH       16
#define MINREQLENGTH    12
char *invmsg="INVALID";

int main( int argc, char *argv[])
{

 char buff[MAXLENGTH+1];
 int len,i, cks, even, tmp;
 char ch, *pw, *ptr;
 
 if( argc<2 ){  puts("Usage: $ bcard  bank_card_number\nor  $ bcard  part1 part2 ...\n");    return(-1); }
 
 //---- get the input ----
 for( pw=buff, i=1;      i<argc;     i++){
    if( (len=strlen(argv[i])) > (MAXLENGTH-(pw-buff)) ){     printf("%s: %s\n",invmsg,"too many digits");    return(1);  }   
    memcpy( pw, argv[i],len);
    pw+=len;
 }
 *pw=0;
 
 //----  check and convert the digits ---- 
 if( (len= pw-buff) < MINREQLENGTH ){   printf("%s: %s\n",invmsg,"too few digits");   return(2);  }   
 
 for( i=0;  i<len;  i++){
    if( (ch=buff[i]-0x30) < 0       ||       ch > 9 ){   printf("%s: %s\n",invmsg,"invalid char in input");  return(3);  }   
    buff[i]= ch;
 }
 
 
//----  Luhn-algorithm ---- 
 for( ptr=buff+len-2, even=1, cks=0;    ptr>=buff;      ptr--, even^=1 ){
    tmp= *ptr;
    if(even){   tmp*=2;     cks+= tmp/10 + tmp%10;  }
    else{ cks+= tmp; }
 }

 if( (cks%10+buff[len-1])% 10  == 0){ puts("It could be VALID, checksumm is ok.");    return(0); }
 printf("%s: %s\n",invmsg,"invalid checksumm");   
 return(4);
 

}


