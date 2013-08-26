/*
 * Domenico Luciani
 * domenicoleoneluciani@gmail.com
 * Olimex Weekend Challenge #21 Words Puzzle
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* shuffle(char*);

int main(void)
{
    char old[300],
         *new, *c;
    
    printf("Insert text here: ");
    fgets(old, 300, stdin);
    
    // Simple hack to remove return character
    if(c = strrchr( old, '\n' ))
        *c='\0';
    //Split string in token and shuffle words
    for(new = strtok(old," .,;:!-"); new != NULL; new = strtok(NULL, " .,;:!-"))
        printf("%s ",shuffle(new));
    putchar('\n');

    return 0;
}

char* shuffle(char *word)
{
    char temp;
    int len = strlen(word),
        i, r;

    if(len-2 >= 2)
    {
        srand(time(NULL));
        for(i=1; i <= len-2; i++)
        {
            r = (rand() % (len-1-i)) + i;
            temp = word[r];
            word[r] = word[i];
            word[i] = temp;
        }
    }
    
    return word;
}
