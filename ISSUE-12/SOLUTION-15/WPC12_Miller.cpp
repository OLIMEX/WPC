// OLIMEX Weekend Programming Challenge Issue-12  WPC12

// Problem:  Similar words
//           Similar word are these which differs by one character only i.e. one character changed or inserted or deleted.
//           For example: if useing this concept the word ¡°hello¡± is considered similar to ¡°hella¡± and to ¡°hell¡± or¡°shello¡±.
//           Make code which enters word then scans: http://fiction.eserver.org/novels/alice_in_wonderland.html and prints all similar
//           words to the one which is entered.

// Language: C++
// Date: 09/06/2013
// Miller Wang

#include <iostream>
#include <string>
#include <algorithm>      //import transform function.
#include <stdlib.h>
using namespace std;

#define NUMBER 40    //define max results.

int main()
{	

	//word as search word, str store one word in test.txt, result[NUMBER] record similar words of word.
	string word, str="", result[NUMBER];     
	result[0]="";     //empty result[0].
	char c;     //get one character from test.txt.
	//i as loop variable, flag to mark whether 2 strings are equal to not, count to count total similar words.
	int i=0, flag, sum, count=0;  

	cout<<"Input a word to search from C:\\test.txt:"<<endl;
	cin>>word;     //input search word.
	
	FILE *fp;     
	fp=fopen("C:\\test.txt", "r");    //open and read c:\test.txt.
	
	while((c=fgetc(fp))!=EOF)     //each time get one character till the end of file.
	{
		if((c>='a' && c<='z') || (c>='A' && c<='Z'))
			str=str+c;     //add one character to string.
		else    //found an English word.
		{			
			//Case 1: Two words with the same length.
			//        We just need to compare each letter of the two words to see if there is only one letter is different.
			if(str.length()==word.length())     
			{
				sum=0;      //two words are completely the same.
				for(i=0; i<str.length(); i++)
				{
					if(str.substr(i,1)==word.substr(i,1))     //compare each letter of the two words.
					{
						flag=0;     //two letters are the same.
						sum=sum+flag;     //sum=0 two words are completely the same.
					}
					else     //two words are not the same.
					{
						flag=1;     //two letters are different.
						sum=sum+flag;     //the two words have different letters.
					}
				}
				
				if(sum==1)     //sum=1 only one different letter found of the two words.
					           //that means str is similar word.
				{	
					//change str to lower case.
					transform(str.begin(), str.end(), str.begin(), tolower);
					//delete repetitive results.
					for(i=0; i<count+1; i++)
					{
						//when this similar word had been found and recorded.
						if(str==result[i])						
						{
							flag=0;
							break;     //exit for loop. 
						}
						//similar word had not been found.
						else
						{
							flag=1;							
						}						
					}
					//new similar word been found and it is not equal to the search word.
					if(flag && str!=word)
						//add similar word to result.
						result[count++]=str;					
				}				
			}
			
			//Case 2: Search word is +1 longer than str(the word gets from file)
			//        Then we need to delete each time one letter of word and compare whether two words are the same.
			
			if(str.length() == word.length()-1)
			{
				for(i=0; i<word.length(); i++)
				{
					//delete one letter of temp, don't modify value of the search word. 
					string temp=word;
					//delete one letter of temp and then compare two words.
					//while two words are the same, str is similar word.
					if((temp.erase(i,1)==str))     
					{
						//same process as Case 1. 
						transform(str.begin(), str.end(), str.begin(), tolower);
						for(i=0; i<count+1; i++)
						{
							if(str==result[i])						
							{
								flag=0;
								break;
							}
							else
							{
								flag=1;								
							}						
						}
						if(flag && str!=word)
							result[count++]=str;
						
					}
				}				
			}
			
			//Case 3: str is +1 longer than the search word.
			//        Then delete one word of str and compare two words.

			if(str.length() == word.length()+1)
			{
				//same process as Case 2, delete one letter of str this time.
				for(i=0; i<str.length(); i++)
				{
					string temp=str;
					
					if((temp.erase(i,1)==word))
					{
						//same process as Case 1.
						transform(str.begin(), str.end(), str.begin(), tolower);
						for(i=0; i<count+1; i++)
						{
							if(str==result[i])						
							{
								flag=0;
								break;
							}
							else
							{
								flag=1;								
							}						
						}
						if(flag && str!=word)
							result[count++]=str;
						break;     //exit for loop.
					}
				}					
			}
		
			str="";     //set str empty and ready to get another word from the file.			
		}		
	}	
	fclose(fp);      //close file.

	cout<<"Similar words of "<<word<<" are:"<<endl;
	
	//output all similar words.
	for(i=0; i<count; i++)
	{		
		cout<<result[i]<<endl; 
	}
	system("pause");
	return 0;
}