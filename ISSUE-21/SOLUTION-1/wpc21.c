#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

void shuffleWord(char *word,size_t len){

    size_t i,n;
    if (len <= 0){
        return;
    }
    char *newword = malloc(len);

    newword[0] = word[0];
    newword[len-1] = word[len-1];

    for (i=1;i<len-1;){
        n = 1 + rand()%(len-2);
        if (word[n]!=0){
            newword[i] = word[n];
            word[n] = 0;
            i++;
        }
    }
    memcpy(word,newword,len);

    free(newword);
}

int main(void)
{
    char text[] = "According to a researcher at Cambridge University, it doesn't matter in what order the letters in a word are, the only important thing is that the first and last letter be at the right place. The rest can be a total mess and you can still read it without problem. This is because the human mind does not read every letter by itself but the word as a whole.";
    srand(time(NULL));

    size_t i,len=0;
    for (i=0;i<sizeof(text);i++){
        if (isalpha(text[i])){
            len++;
        } else {
            shuffleWord(text + i - len, len);
            len = 0;
        }
    }

    printf("%s\n",text);

    return 0;
}

