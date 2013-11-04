
#include <stdio.h>
#include <string.h>

#define ERR_CHK
#define MAX 1000
void main (void)
{
  char *sentence = "3a3b3a13li";
  char ch;
  int numb;
  char out[MAX] ="";

  //scan for doubles int char
  while( 2==sscanf(sentence,"%d%c",&numb,&ch) )
  {
	  char temp[MAX];
	  sentence+=sprintf(temp,"%d%c",numb, ch);
	  strncat(out,memset(temp,ch,numb),numb);
  }

#ifdef ERR_CHK
  if (*sentence)
	  printf("ERROR");
  return;
#endif

  printf("%s",out);

}

