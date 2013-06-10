#include <stdio.h>
#include <ctype.h>
#include <string.h>

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

int levenshtein(const char *s, const char *t)
{
    int ls = strlen(s), lt = strlen(t);
    int d[ls + 1][lt + 1];

    int i,j;
    for (i = 0; i <= ls; i++)
        for (j = 0; j <= lt; j++)
            d[i][j] = -1;

    int dist(int i, int j) {
        if (d[i][j] >= 0) return d[i][j];

        int x;
        if (i == ls)
            x = lt - j;
        else if (j == lt)
            x = ls - i;
        else if (s[i] == t[j])
            x = dist(i + 1, j + 1);
        else {
            x = dist(i + 1, j + 1);

            int y;
            if ((y = dist(i, j + 1)) < x) x = y;
            if ((y = dist(i + 1, j)) < x) x = y;
            x++;
        }
        return d[i][j] = x;
    }

    return dist(0, 0);
}

int main()
{
    const char filename[] = "c:/file.txt";
    FILE *file = fopen(filename, "r");

    const char *word1 = "cats";
    char word2[128];

    if ( file != NULL ) {

        printf("Word similar to '%s':\n",word1);

        while (getWord(file,word2)){

            if (levenshtein(word1, word2) == 1)
                printf("%s\n",word2);

            //clear memory
            memset(word2,0,sizeof(word2));
        }

        printf("\n-== END ==-\n");

        //close file
        fclose(file);
    }

        return 0;
}
