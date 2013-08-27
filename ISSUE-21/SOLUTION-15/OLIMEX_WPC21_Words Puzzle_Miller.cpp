// OLIMEX Weekend Programming Challenge Issue-21  WPC21

// Problem:
//          http://www.mrc-cbu.cam.ac.uk/people/matt.davis/Cmabrigde/
//          Write code which takes as input normal text and shuffles the letters
//          inside the words to make text like this one above.
// Language: C++
// Date: 25/08/2013
// Miller Wang

// Result:
//          Result(1).jpg
//          Result(2).jpg
//          Result(3).jpg

#include <iostream>
#include <ctime>
#include <string>

using namespace std;

int main()
{
    string str, word="";
    int i=0, j, random;
    char temp;
    str="According to a researcher (sic) at Cambridge University, it doesn't matter in what order the letters in a word are, the only important thing is that the first and last letter be at the right place. The rest can be a total mess and you can still read it without problem. This is because the human mind does not read every letter by itself but the word as a whole.";
    // Rebuild new random seed.
    srand((unsigned)time(NULL));
    while(i<str.length())
    {
        // 'A' ~ 'Z' or 'a' ~ 'z' letters, add it to word.
        if((str[i]>='A' && str[i]<='Z') || (str[i]>='a' && str[i]<='z') )
        {
            word=word+str[i];
        }

        else
        {
            // There is a symbol or word="".
            if(word.length()==0)
            {
                cout<<str[i];
                i++;
                continue;
            }
            // Less than 4 letters, do not exchange inside letters.
            else if(word.length()<4)
            {
                cout<<word;
                cout<<str[i];
                word="";
                i++;
                continue;
            }
            // Word length >=4 then exchange.
            else
            {
                // From the second letter.
                j=1;
                // Use rand() function to randomly exchange letters in a word.
                // To the last but one.
                while(j<word.length()-1)
                {
                    temp=word[j];
                    random=1+(int)(((word.length()-2))*rand()/(RAND_MAX+1.0));
                    word[j]=word[random];
                    word[random]=temp;
                    j++;
                }
                cout<<word;
                word="";
                cout<<str[i];
            }
        }
        i++;
    }
    cin.get();
    return 0;
}
