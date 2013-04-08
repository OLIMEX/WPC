#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 4          /* N as how many(N) strings */
#define M 100      /* M is used to limits maximum number of characters in each string. */

int main(void)
{
    int i=0, j=0, count=0;       /* i, j as loop variant, count to record the number of elements in array string2. */
    char string[N][M];     /* string to store each string*/
    char string2[N][M];    /* store each string which includes search character. */
    int stringlength[N]={0};    /* save character length of each string */
    char s;    /* get a character from keyboard */
    
   printf("Input %d strings and make sure each string is less than %d characters:\n\n", N, M);
    for(i=0; i<N; i++)
    {
        scanf("%s", string[i]); /* input and store all strings(if the string includes space, change this line to gets(string[i]);) */
        stringlength[i]=strlen(string[i]); /* caculate number of characters in each string */
    }
    printf("\nInput one character to search from above %d strings, press space key to end the process:\n\n", N);
    while ((s=getchar())!=' ') /* input character !=' ' */
    {
        count=0;
        for(i=0; i<N; i++)
            for(j=0; j<stringlength[i]; j++)
            {
                if(s==string[i][j]||tolower(s)==string[i][j]||toupper(s)==string[i][j]) /* judge every character in string string */
                {
                    strcpy(string2[count],string[i]);  /* copy string[i] that contains search character to string2*/
                    count++;  /* record one more string  to string2 */
                    break;   /* judge next string */
                }
            }
        if(count>0) /* in case there are strings contain the search character */
        {
            for(i=0; i<count; i++) /* Estimate each string of string2 */
            {
                if(strlen(string2[0])>strlen(string2[i]))   /* string length string2[0]> string2[i] */
                    strcpy(string2[0], string2[i]);         /* copy string2[i] to string2[0] */
                if(strlen(string2[0])==strlen(string2[i]))  /* string length string2[0]=string2[i] */
                        {
                            if(strcmp(string2[0],string2[i])<0) /* compare ASCII code of string2[0] and string2[i] to make sure output is unique. */
                            strcpy(string2[0], string2[i]);     /* return bigger string */
                        }
            }
            printf("%s\n", string2[0]);   /* output unique result that meets the requirement with shortest length. */
            for(i=0; i<count; i++)
            strcpy(string2[i],"\0");    /* empty each string of string2 and be ready for next search character. */
            printf("\nInput one character to search, press space key to end the process:\n\n");
        }
    }
}
