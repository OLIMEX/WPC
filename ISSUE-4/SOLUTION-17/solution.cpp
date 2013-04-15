    #include <iostream>
    #include<windows.h>
    #include<string>
    #include<time.h>
    using namespace std;
    
    int main() 
    {     
        string word[100];
        int dumi = -1;
        char ch[100];
        string longest = "";
        bool yes = true;
        ch[0] = 'a'; 
        int max = 0;
        
       while(ch[0] != '*')
          {
            cin >> ch;
            yes = true;  
            for(int i = 0; i <= strlen(ch)-1; i++)
              {
                 for(int j = i+1; j < strlen(ch) && yes; j++)
                   {
                      if(ch[j] <= 'Z')
                        {
                          char b = 'Z' + 'z';
                          if(ch[i] == ch[j] || ch[i] == ch[j] + b) yes = false;
                        } 
                      if(ch[j] >= 'a')
                        {
                          char c = 'a' - 'A'; 
                          if(ch[i] == ch[j] || ch[j] == ch[j] - c) yes = false;     
                        }    
                   }
              } 
              
            if(yes) 
              {
                dumi++; 
                word[dumi] = ch; 
                if(strlen(ch) > max) 
                  {
                    max = strlen(ch);
                    longest = ch;
                  }
              }
            yes = true; 
            
          }
          
        cout << longest << endl;
        
        cout << endl;  
        system("pause");
        return main();
    }







