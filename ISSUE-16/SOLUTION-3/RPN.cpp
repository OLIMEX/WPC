    /*
  Name: Reverse Polish Notation
  Author: Snaksa
  Date: 05.07.13 17:45
  Description: A program that converts normal Infix Notation into Postfix Notation
  */
    #include<iostream>
    using namespace std;
    
    bool is_num(char x)
      {
        if(x >= '0' && x <= '9')        
          return true;
        return false;       
      }
    
    bool is_operator(char x)
      {
        if(x == '+' || x == '-' || x == '*' || x == '/' || x == '%') 
          return true;
        return false;                   
      }
      
    int priority(char x)
      {
        if(x == '*' || x == '/' || x == '%') return 2;
        if(x == '+' || x == '-') return 1;
        return 0;                
      }
      
    string RPN(string input)
      {
        string output;
        char stack[100];
        int stackpos = 0;
        int pos = 0; //position of the input[pos];
        int len = input.size();
        char x;   
        while(pos < len)
          {
            x = input[pos];
            if(x == ' ') output += x; 
            else
            if(is_num(x)) output += x;
            else if(is_operator(x))
              {
                char temp = stack[stackpos];
                if(is_operator(temp) && (priority(x) < priority(temp)))
                  {
                    output += temp;
                    stack[stackpos] = x;                  
                  }
                else if(is_operator(temp) && (priority(x) == priority(temp)))
                  {
                    output += temp;
                    stack[stackpos] = x;                       
                  }
                 else
                   {
                     stackpos++; 
                     stack[stackpos] = x;                                   
                   }                     
              }
            else if(x == '(')
              {
                stackpos++;
                stack[stackpos] = x;        
              }     
            else if(x == ')')
              {
                bool check = true;
                while(stackpos != 0)
                  {
                    if(stack[stackpos] == '(')
                      {
                        stackpos--;
                        check = false;
                        break;                 
                      }
                    else
                      {
                        output += stack[stackpos];
                        stackpos--; 
                      }                   
                  }
                if(check) return "Incorrect input!";        
              } 
            pos++;  
          }
        while(stackpos > 0)
          {
            output += stack[stackpos];
            stackpos--;             
          }
        return output;     
      }
      
    int main()
      {
        string input;
        getline(cin, input);
        cout << RPN(input) << endl;      
        system("pause");
        return 0;        
      }