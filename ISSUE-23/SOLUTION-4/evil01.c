#include <stdio.h>

#define TRUE 1!=2
#define FALSE !TRUE

void main ()
{
  printf("%s\n", TRUE == FALSE ? "This is correct?" : "Ok");
} 

