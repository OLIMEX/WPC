/*
 2014-06-27 by kantal59 
 License: LGPL
 OLIMEX WPC#59: Big – Little Endians
 			Make code which detects on what machine is ran – with Big or Little Endian. 
 			Can you do it in other language than C?
 			
 			Compile: gcc -o get_endian  get_endian
*/


#include <stdio.h>
#include <inttypes.h> 

int main(){

   uint16_t i = 0x8000;	
   char *p = (char *) &i;
   if (p[0] == 0) 
       puts( "LITTLE endian"); 	// 00 80 -> lowest address contains the least significant byte
   else
      puts( "BIG endian");	// smallest address contains the most significant byte
 
  return(0);
}

