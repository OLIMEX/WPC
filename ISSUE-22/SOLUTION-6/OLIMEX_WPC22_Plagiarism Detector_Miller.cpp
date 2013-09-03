// OLIMEX Weekend Programming Challenge Issue-22  WPC22

// Problem:
//          Make code which compare two texts and output the % of similarities
//          between the two texts i.e. if they have same words even if the words
//          are in different order.
//          More advanced version may take care for synonyms.
// Language: C++
// Date: 01/09/2013
// Miller Wang

// Result:
//          Result.jpg

#include <iostream>
#include <string>

using namespace std;

#define MAX 50

int main()
{
    string temp1[MAX];
    string temp2[MAX];
    string str1="You wrote a programme named Hello World.";
    string str2="I wrote a programme named Hello World too.";
    string word;
    //flag=0 no same word.
    int i=0, j=0, CountOne=0, CountTwo=0, SameWords=0, flag=0;
    while(i<str1.length())
    {
        if((str1[i]>='A' && str1[i]<='Z') || (str1[i]>='a' && str1[i]<='z'))
            word=word+str1[i];
        else
        {
            //Separate all words of str1 and store them.
            temp1[CountOne]=word;
            CountOne++;
            word="";
        }
        i++;
    }
    i=0;
    while(i<str2.length())
    {
        if((str2[i]>='A' && str2[i]<='Z') || (str2[i]>='a' && str2[i]<='z'))
            word=word+str2[i];
        else
        {
            //Separate all words of str2 and store them.
            temp2[CountTwo]=word;
            CountTwo++;
            word="";
        }
        i++;
    }

    if(CountOne<=CountTwo)
    {
        for(i=0; i<CountOne; i++)
            for(j=0; j<CountTwo; j++)
            {
                // Compare two strings if there are same words.
                if(temp1[i]==temp2[j])
                {
                    // Found same word.
                    flag=1;
                    SameWords++;
                    temp2[j]="";
                }
            }
    }
    else
    {
        for(i=0; i<CountTwo; i++)
            for(j=0; j<CountOne; j++)
            {
                if(temp2[i]==temp1[j])
                {
                    flag=1;
                    SameWords++;
                    temp1[j]="";
                }
            }
    }
    
    if(flag)
    {
        cout<<"There are same words in the two texts, ";
        if(CountOne<=CountTwo)
            // Output % of same words.
            cout<<(double)SameWords/CountOne*100<<"% are same words."<<endl;
        else
            cout<<(double)SameWords/CountTwo*100<<"% are same words."<<endl;
    }
    else
       cout<<"None words are the same in the two texts."<<endl;
       
    cin.get();
    return 0;
}
