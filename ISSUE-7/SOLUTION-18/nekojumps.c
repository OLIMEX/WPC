#include <stdio.h>

int nekojumps(int n)
{
  if (n<=0) /* invalid step */
    return (0); 

  /*
   Short jump means jump by one step for one stair.
   Long jump means jump by two steps for two stairs.
  */

  if (n==1) /* One stair. Cat has only one option - short jump */
    return (1);

  if (n==2) /* Two stairs. Cat has two options. Two short jumps or One long jump */
    return (2);

  /* 
   For other stairs (more than two stairs). 
   Cat may do short jump then do the rest n-1 stairs
   or do long jump then do the rest n-2 stairs 
  */ 

  return (nekojumps(n-1) + nekojumps(n-2));
}

int main()
{
  int i;
  printf ("Please enter steps for cat: ");
  scanf ("%d" , &i);
  printf("%d step(s), cat has %d way(s) to jump\n", i, nekojumps(i));
}

