#include <stdio.h>
int main(void)
{
	unsigned long long int a,b,c,size;
	
	scanf("%lld",&size);
	
	for(a=0,b=1,c=0;size>0;size--){
		a=b+c;
		c=b;
		b=a;
	}
	printf("%lld\n",a);
	return 0; 
} 
