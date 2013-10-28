 #include <iostream>
 #include <string>
 using namespace std;
 
 int main()
 {
    int dn[13]={1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    string rn[13]={"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int i=0, number;
    string result="";
    cout<<"Input a positive integer: ";
    cin>>number;

    while(number>0)
    {
        while(number>=dn[i])
        {
            number=number-dn[i];
            result=result+rn[i];
        }
        i++;
    }
    
    cout<<"Roman number is: "<<result<<endl;
    return 0;
 }
