#include <iostream>
#include <string>

using namespace std;

void Compress(string str1)
{
    int i=0, count=0, j, len;
    cout<<"The result is: ";
    len=str1.length();
    while(i<len)
    {
        if(str1[i]=='W')
        {
            count=0;
            count++;
            if(i+1<len && str1[i+1]=='W')
                for(j=i+1; j<len; i++, j++)
                {
                    if(str1[j]=='W')
                    {
                        count++;
                        if(j==len-1 && str1[j]=='W')
                            cout<<count<<"W";
                    }
                    else
                    {
                        cout<<count<<"W";
                        break;
                    }
                }
            else
                cout<<count<<"W";
        }
        
        if(str1[i]=='B')
        {
            count=0;
            count++;
            if(i+1<len && str1[i+1]=='B')
                for(j=i+1; j<len; i++, j++)
                {
                    if(str1[j]=='B')
                    {
                        count++;
                        if(j==len-1 && str1[j]=='W')
                            cout<<count<<"W";
                    }
                    else
                    {
                        cout<<count<<"B";

                        break;
                    }
                }
            else
                cout<<count<<"B";
        }

        i++;
    }
    cout<<endl;
}

int main()
{
    //string str="WWWWWWWWWWBWWWWWWWWWBBBBBBBWWWWWWWWBBWWWWWWWBBBBWWBBBBBBW";
    string str="WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWBWWWWWWWWWWWWWW";
    cout<<"The string is:"<<endl<<str<<endl;
    Compress(str);
    cin.get();
    return 0;
}
