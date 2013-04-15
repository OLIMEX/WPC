#include <stdio.h>
#include <ctype.h>
#include <string.h>

/**
 * @brief getWord - read word from file
 * @param file - intput file
 * @param word - pointer where save word
 * @return 1 - succesfull
 */
int getWord(FILE *file, char *word){

    char ch;
    size_t size = 0;

    while ( (ch = fgetc(file)) != EOF )
    {
        if ( isalpha(ch)){
            word[size]=ch;
            size++;
        } else {
            if (size > 0)
                return 1;
        }
    }

    if (size > 0)
        return 1;

    return 0;
}

/**
 * @brief isIsogram - check if word is isogram
 * @param word - input word
 * @return 1 - yes, 0 - no
 */
int isIsogram(char *word){

    unsigned int i,j;

    for (i=0;i<strlen(word);i++){
        for (j=i+1;j<strlen(word);j++){
            if (tolower(word[i])==tolower(word[j]))
                return 0;
        }
    }

    return 1;
}

int main (void)
{
    const char filename[] = "file.txt";

    char word[40960],isogram[40960];
    size_t isogramLen = 0;

    //open file
    FILE *file = fopen(filename, "r");
    if ( file != NULL )
    {
        //clear memory
        memset(isogram,0,sizeof(isogram));
        memset(word,0,sizeof(word));

        while (getWord(file,word))
        {
            if (isIsogram(word)){

                size_t len = strlen(word);
                //if is longer than remember word
                if (len > isogramLen){
                    memcpy(isogram,word,len);
                    isogramLen = len;
                }
            }
            //clear memory
            memset(word,0,sizeof(word));
        }

        //print answer
        if (isogramLen > 0){
            printf("Longest (%d leters) isogram: %s\n",isogramLen,isogram);
        } else {
            printf("No isograms in input file\n");
        }

        //close file
        fclose(file);
    }
    return 0;
}
