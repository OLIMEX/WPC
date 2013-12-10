/* 
 2013-12-06 by kantal59
 License: LGPL
 Compile: gcc -o str2nokia  str2nokia.c
 OLIMEX WPC#36: NOKIA text message converter
         Make code which takes string and convert it to button push sequence on NOKIA1100 phone keypad 
         which will print same string. For instance: HELLO -> 44 33 555 555 666
         
         The code uses english letters only.
*/

#include <stdlib.h>
#include <stdio.h>
#include "str2nokia.h"

#define BSIZE   1024

int main( int argc, char *argv[])
{

 char buffer[BSIZE];
 
 if( argc!=2 ){
    puts( "\nUsage: $ str2nokia \"message\" \n");
    return(1);
 }
 
 str2nokia( argv[1], buffer, BSIZE);

 puts( buffer);

 return(0);
}


