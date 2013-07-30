#include <stdio.h>

#define FALSE 0 
/**
to use recursive instead of using stack
http://www.c-sharpcorner.com/uploadfile/b81385/efficient-string-matching-algorithm-with-use-of-wildcard-characters/
**/
int ismatch(char * str, char * pat)
{
  int strpos;
  int patpos;
  int matchresult;

  strpos = 0;
  patpos = 0;

  while (*str != 0 && *pat != 0 && *pat != '*' && ((*str == *pat)||(*pat == '?')))
  {
    str++;
    pat++;
  }

  if (*str == 0 && *pat == 0)
  {
    return (!FALSE);
  }
  else if (*pat == '*')
  {
    while (*pat == '*' && *pat != 0) /* ignor concat * */ 
      pat++;

    if (*pat == 0)
      return (!FALSE); /* we found * in last char in pattern */

/*printf ("pat=%s\n", pat);
printf ("str=%s\n", str);
*/
    matchresult = FALSE;
    while (*str != 0)
    {
      matchresult = ismatch(str, pat);
 /*       printf ("check str=%s\n", str); */
      str++;
      if (matchresult != FALSE)
        break;
    }

  }
  else
  {
    return FALSE;
  }
}

void match (char * input_string, char * pattern_string)
{
  char onestr[1024];
  int onestrpos;
  char readch;

  onestrpos=0;
  for(;;)
  { /* ‘ ” . , : ; */
    readch = *input_string++;
    if ((readch=='\'')||(readch=='"')||(readch=='.')||(readch==',')||(readch==':')||(readch==':')||(readch==';')||(readch==' ')||(readch==0))
    {
      onestr[onestrpos] = 0;
      onestrpos = 0;

/*printf("split %s\n", onestr);
*/
      if (onestr[0] != 0)
        if (ismatch(onestr, pattern_string))
          printf("%s\n", onestr);

      if (readch == 0)
        break;      
    }
    else
    {
      onestr[onestrpos++] = readch;
    }
  }
  
}

void main ()
{
  char * instr = "babbbfefbcb";
  char * inpat = "b*b**x*";
  /*if (ismatch(instr, inpat) == FALSE)
  {
     printf ("%s not like %s\n", instr, inpat);
  }
  else
  {
     printf ("%s like %s\n", instr, inpat);
  }*/
  match ("The big black cat jump over the window", "?i*");
  
}
