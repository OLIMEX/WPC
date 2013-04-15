#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 50

int main(void)
{
    int i=0, length=0, count=0;
    char str[MAX]={'\0'};
    char result[MAX];
    char c;

    FILE *fp;

    fp=fopen("D:\\Program Files\\C-Free 3.5\\temp\\test.txt","r"); /* text file path */
    
    while((c=fgetc(fp))!=EOF)
    {
        if((c>='a' && c<='z') || (c>='A' && c<='Z'))
        str[count++]=c;
        else
        {
            count=0;
            for(i=0; i<strlen(str); i++)
            str[0]='\0';
        }
        
        if((strlen(str)>length) && (isogram(str)))
            {
                length=strlen(str);
                strcpy(result, str);
            }
    }
    fclose(fp);
    printf("\nLength of longest isogram word is: %d\n", length);
    printf("The longest isogram word is:\n%s\n", result);
    system("pause");
}
    
    int isogram(char string[MAX])
    {
     int i=0, j=0;
     for(i=0; i<strlen(string)-1; i++)
                for(j=i+1; j<strlen(string); j++)
                    if((string[i]==string[j]) || ((string[i]+32)==string[j]) || ((string[i]-32)==string[j]))
                        return 0;
     return 1;
    }

