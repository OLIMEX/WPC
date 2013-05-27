#include <iostream>
#include <vector>
using namespace std;


int main()
{
    vector<int> out;
    int a,b,i=1;
    double sum=0,c=0,temp=0,temp_sum=0;
    cin>>a>>b;
    c = (double)a/b;
    //cout<<c<<endl;
 while(true)
 {
        i++;
        temp = (double)1/i;
        temp_sum = sum+temp;
        //cout<<i<<" : "<<temp_sum<<" : "<<temp<<endl;
        if(temp_sum<c)
        {
            sum+=temp;
            out.push_back(i);
            continue;
        }
        else if(temp_sum == c)
        {
            sum+=temp;
            out.push_back(i);
            break;
        }
 }
 for(int k=0;k<out.size();k++)
        cout<<out[k]<<" ";
    cout<<endl;
 //
 return 0;
}