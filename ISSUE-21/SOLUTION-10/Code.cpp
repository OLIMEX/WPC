/*
  Name: Weekend Programming Challenge – Issue #21 Words Puzzle
  Author: Sinan Zikri 
  Date: 24.08.13 18:59
  Description: Write code which takes as input normal text and shuffles the letters inside the words
*/

#include<iostream>
#include<time.h>
using namespace std;
char text[1000] = "Hello, ladies and gentlemen! Here is example of my solution.";

bool isLetter(char a)
	{
		return (a >= 'A' && a <= 'Z') || (a >= 'a' && a <= 'z');
	}

void Change(int i, int j)
	{
		if(i == j) return;
		int p = i;
		srand(time(NULL));
		while(i < j)
			{
				int n, m;
				n = p + rand() % (j-p);
				m = p + rand() % (j-p);
				if(n == m)
					{
						if(n+1 > j) m = n-1;
						else m = n+1;
					}

				char help = text[n];
				text[n] = text[m];
				text[m] = help;
				i++;
			}
	}

int main()
	{
		//cin.getline(text, 1000);
		for(int i = 0; i < strlen(text) - 1; i++)
			{
				if(isLetter(text[i]))
					{
						for(int j = i+1; j < strlen(text); j++)
							{
								if(!isLetter(text[j]) || j == strlen(text)-1)
									{
										Change(i+1, j-2);
										i = j;
										break;
									}
							}
					}
			}

		cout << text << endl;

		system("pause");
		return 0;
	}