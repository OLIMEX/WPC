#include <stdio.h>
#include <stdlib.h>
#include <string.h>


long powtbl[7];


int main(int argc, char *argv[])
{
	long l,m;
	int i;
	char strbuff[32],strbuff2[8];
	char *ptr;
	int bad;


	powtbl[4]=1;
	for(i=3;i>=0;i--)
		powtbl[i]=powtbl[i+1]*10;


	strcpy(strbuff,"00001");

	l=1;
	while(l<1000)
	{

		l++;
		strbuff[4]++;
		for(i=4;i>0;i--)
		{
			if(strbuff[i]==('9'+1))
			{
				strbuff[i]='1';
				l+=powtbl[i];
				strbuff[i-1]++;
			}
		}

		if((1000000 % l)==0)
		{
			m=1000000/l;

			memset(strbuff2,0,8);
			sprintf(strbuff2,"%ld",m);
			bad=0;
			for(i=0;i<8;i++)
			{
				if(strbuff2[i]=='0')
				{
					bad=1;
					break;
				}
			}

			if(bad)continue;


			printf("FOUND %ld * %ld = %ld\n",l,m,l*m);
			printf("FOUND %ld * %ld = %ld\n",m,l,l*m);
		}
	}



	return 0;
}
