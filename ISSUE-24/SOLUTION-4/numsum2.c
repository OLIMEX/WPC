#include <stdio.h>
#include <stdint.h>

int64_t table[1000][1000];

int64_t solve(int64_t a,int64_t prev)
{
	int64_t count;
	int64_t tmp=1;
	
	if(a==1)
		return 1;
	
	if(table[a][prev]!=0)
		return table[a][prev];
	
	for(count=prev;count<=a/2;count++)
		tmp+=solve(a-count,count);

	table[a][prev]=tmp;
	return tmp;
}

int main(void)
{
	int64_t num;
	scanf("%lld",&num);
	printf("%lld\n",solve(num,1));
	return 0;
}
