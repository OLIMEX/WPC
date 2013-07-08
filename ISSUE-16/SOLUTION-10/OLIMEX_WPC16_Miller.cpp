// OLIMEX Weekend Programming Challenge Issue-16  WPC16

// Problem:
//          Input string which is mathematical statement written in normal
//          Infix Notation and convert it to Postfix Notation. Infix notation
//          is the normal way we write mathematical statements like:
//          (10 + 20) / (30 - 40)
//          Postfix notation (also known as Reverse Polish notation) is where
//          every operator follows all of its operands and is parenthesis-free,
//          the above statement written in Postfix notation is:
//          10 20 + 30 40 - /
// Language: C++
// Date: 07/07/2013
// Miller Wang
//

// Test:
// 1. Input:(10+20)/(30-40)
//    Result: 10 20+ 30 40-/
// 2. Input: (a/b-3)*(42+e/f-5%3)-6+g*((3-8*(h-i))-9)*80.0
//    Result: a b/ 3- 42 e f/+ 5 3%-* 6- g   3 8  h i-*- 9-* 80.0*+

#include <iostream>
#include <string>
#include <stack>
#include <stdlib.h>

using namespace std;

// '+'  '-'  '*'  '/'  '%'  '('  ')' as operators.
int Operators(char ch)
{
    if(ch=='+') return 1;
    if(ch=='-') return 1;
    if(ch=='*') return 1;
    if(ch=='/') return 1;
    if(ch=='%') return 1;
    if(ch=='(') return 1;
    if(ch==')') return 1;
    return 0;     // Not an operator.
}

// Definition pirority of each opeartor.
int OperatorPriority(char ch)
{
    if(ch=='(') return 1;
    if(ch=='*' || ch=='/' || ch=='%') return 2;
    if(ch=='+' || ch=='-') return 3;
}

// Convert to postfix notation statement.
void Convert(string str)
{
    // Create stack to store character elements(Infix notation statement).
    stack<char> CharStack;
    char ch;
    int i;
    for(i = 0; i<str.length(); i++)
    {
        if(!Operators(str[i]))     // Character is not an operator, print it.
            cout<<str[i];
        else
        {
            if(CharStack.empty())     // Stack is empty, push the character into stack.
                CharStack.push(str[i]);
            else     // Not empty.
            {
                ch=CharStack.top();     // Get top element.
                if(str[i]==')')     // If it is right bracket.
                {
                    while(ch!='(')     // Output all elements before left bracket.
                    {
                        cout<<ch;
                        CharStack.pop();     //Take out top element.
                        ch=CharStack.top();     // Get new top element.
                    }
                    CharStack.pop();     // Take out left bracket.
                }
                else    // If it is not right bracket.
                {
                    // Compare priority and output all elements which are with same or higher priority.
                    while(OperatorPriority(ch) <= OperatorPriority(str[i]))
                    {
                        if(ch=='(')     // If it is left bracket, end while.
                            break;
                        else     // Same process as above.
                        {
                            cout<<ch;
                            CharStack.pop();
                            if(CharStack.empty())
                                break;
                            ch=CharStack.top();
                        }
                    }
                    cout<<" ";     // Print space to improve readability of output results.
                    CharStack.push(str[i]);     // Push new element into stack.
                }
            }
        }
    }
    while(!CharStack.empty())     // Output all other characters untill stack is empty.
    {
        ch=CharStack.top();
        cout<<ch;
        CharStack.pop();
    }
}

int main()
{
    string str;
    cout<<"Input infix notation statement:"<<endl;
    cin>>str;
    //Covert infix notation statement to postfix.
    Convert(str);
    cout<<endl;
    system("pause");
    return 0;
}
