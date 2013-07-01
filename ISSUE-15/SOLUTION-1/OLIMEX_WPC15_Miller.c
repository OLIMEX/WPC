/* OLIMEX Weekend Programming Challenge Issue-15  WPC15

// Problem:
//          Make code which reads not formated C language text file and format
//          the brackets i.e. moves the closing bracket as same column as the
//          corresponding opening bracket, ignoring the comments. If the
//          brackets doesn¡¯t match should issue error message.
// Language: C
// Date: 30/06/2013
// Miller Wang
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    /* Count number of opening bracket and closing bracket. */
    int OpeningBracket=0, ClosingBracket=0;
    /* Variable previous records the previous character. */
    char c, previous='\0';
    FILE *fp;
    
    /* Test file doesn't exist. */
    printf("Test file path: C:\\test.txt\n");
    if(fp=fopen("C:\\test.txt", "r")==NULL)
    {
        printf("Error! Test file doesn't exist.\n");
        getchar();
        exit(0);
    }

    fp=fopen("C:\\test.txt", "r");
    while((c=fgetc(fp))!=EOF)
    {
        if(c=='{')  OpeningBracket++;
        if(c=='}')  ClosingBracket++;
        
        /* Case 1: Ignore comments with /* start symbols */
        if(c=='*' && previous=='/')
        {
            while((c=fgetc(fp))!=EOF)
            {
                if(c=='/' && previous=='*')
                {
                    previous='\0';
                    break;
                }
                previous=c;
            }
        }
        
        /* Case 2: ignore comments with // start symbols */
        if(c=='/' && previous=='/')
        {
            while((c=fgetc(fp))!='\n' && c!=EOF){}     /* Do nothing. */
            previous=c;
        }

        /*
            Anytime when counted number of closing bracket "}" is larger than
            opening bracket "{", return result and end the process.
        */
        if(ClosingBracket > OpeningBracket)
        {
            printf("Error! No matches for closing bracket \"}\".\n");
            fclose(fp);
            getchar();
            exit(0);     /* End program. */
        }
        
        previous=c;
    }

    fclose(fp);

    /* Match */
    if(OpeningBracket==ClosingBracket)
        printf("Congratulations! Brackets matches.\n");
    /* Not match, opening brackets > closing brackets. */
    else
        printf("Error! No matches for opening bracket \"{\".\n");
        
    getchar();
    return 0;
}
