#include <stdio.h>
#include <stdlib.h>
#include<conio.h>

/*

by Marcelo Campos - Smart Radio - Brasil

for Olimex weekend challenge oct'27 2013

Simple enter a integer number when prompted


You can code the solution in any programming language during the weekend and
 have to submit it to info@olimex.com latest on Sunday October 27th.

http://en.wikipedia.org/wiki/Roman_numerals
Symbol 	Value
I 	1
V 	5
X 	10
L 	50
C 	100
D 	500
M 	1,000

900 CM
800 DCC

    1954 as MCMLIV (Trailer for the movie The Last Time I Saw Paris)[7]
    1990 as MCMXC (The title of musical project Enigma's debut album MCMXC a.D., named after the year of its release.)
    2008 as MMVIII - the year of the games of the XXIX (29th) Olympiad (in Beijing)

*/

// PROTOTYPES
void Calculate ( int number, char Major, char Minor, char Base );


// GLOBALS
  char output [11] = "          ";
  int counter = 0;

int main(int argc, char *argv[])
{  
  int number ;
  int number_in;
  
  int milhar ;
  int centenas ;
  int dezenas ;
  int unidades ;
  char response;

Conversion: 
  number = 0;
  number_in;
  milhar = 0;
  centenas = 0;
  dezenas = 0;
  unidades = 0;
  response = ' ';                         
  output [0] =0x00;
               
      printf("\nEnter Integer : ");
      scanf("%d",&number);

  number_in = number;
   
  if ( number >= 1000)
  {
     milhar = number / 1000;
     
     for (counter=0; counter < milhar; counter++)  
     {
         output[counter] = 'M';
     }
     number -= (milhar * 1000);
  }
  
  if (number < 1000 & number >= 100)
  {
     centenas = number / 100;             
     Calculate( centenas, 'D', 'C', 'M' );         
     number -= ( centenas * 100);
  }
  
  if ( number > 0 & number >= 10 )
  {   
      dezenas = number / 10;         
      Calculate( dezenas, 'L', 'X', 'C' );      
      number -= (dezenas * 10);
  }     

  if ( number > 0 )
  {   
      unidades = number;
         
      Calculate( unidades, 'V', 'I', 'X' );
  }  
     
   
  output[11] = 0x00;
  
  printf ("Decimal Number: %d, Roman: %s \r\n", number_in, output  );
  
  printf("\nWant to make a new conversion? (y,N) ");
  scanf("%s",&response);
  if(response == 'y' | response == 'Y')
     goto Conversion;                           
  
  system("PAUSE");	
  return 0;
}

void Calculate ( int number, char Major, char Minor, char Base)
{
     int i;
     
     if ( number == 9  )
     {
       output[counter++] = Minor;
       output[counter++] = Base;
     }
     else if ( number <= 8 && number >5 )
     {
       output[counter++] = Major;
       for (i=5; i < number; i++ )
       {
           output[counter++] = Minor;
       } 
     }
     else if ( number == 5)
     {
          output[counter++] = Major;
     }
     else if (number == 4)
     {
       output[counter++] = Minor;
       output[counter++] = Major;
     }
     else
     {
         for (i=0; i < number; i++)
         {
             output[counter+i] = Minor;
         }
         counter += i;
     }
          
}






















