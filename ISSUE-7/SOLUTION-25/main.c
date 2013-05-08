#include <stdio.h>

int main ()
{
	int N, First=0, Second=1, Third;
	scanf ("%d", &N);
	while (N--)
	{
		Third = First + Second;
		First = Second;
		Second = Third;
	}
	printf ("%d", Third);
	return 0;
}