#include <stdio.h>
int main(void)
{
    unsigned long N, JumpStairs();
    printf("Input total stair numbers to jump:\n");
    scanf("%ul", &N);
    printf("\nThere are %u different ways.\n\n", JumpStairs(N));
    system("pause");
}

unsigned long JumpStairs(unsigned long temp)
{
   if(temp==1) return 1;
   if(temp==2) return 2;
   if(temp>=3) return JumpStairs(temp-1)+JumpStairs(temp-2);
}
