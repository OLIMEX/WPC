
#include <stdio.h>
#include <string.h>

void main (void)
{
  char *sentence = "3a3b3a13l";
  char ch;
  int numb;

  while( 2==sscanf(sentence,"%d%c",&numb,&ch) )
  {
	  char temp[100];
	  sentence+=sprintf(temp,"%d%c",numb, ch);
	  printf("%.*s",numb,memset(temp,ch,numb));
  }

}
