// OLIMEX Weekend Programming Challenge Issue-24  WPC24

// Problem:
//          Write code which calculate the number of ways you can express
//          positive natural number N as sum of positive natural numbers.
// Date: 15/09/2013
// Miller Wang
// Result:
//          N=1     Sum=1
//          N=2     Sum=2
//          N=3     Sum=3
//          N=4     Sum=5
//          N=5     Sum=7
//          N=7     Sum=15
//          N=9     Sum=30
//          N=18    Sum=385
//          N=25    Sum=1958
//          N=60    Sum=966467
//          N=100   Sum=190569292   (It runs about 220 seconds, not effcient.)

#include<stdio.h>
#include<stdlib.h>

int count[3000]={0};
/* Array count to save backtracking result. */
long Sum=0;
/* Sum to store (results) how many ways. */

void separate(unsigned int N, int progress)
/* progress to store separate progress. */
{
    int i;
    int restnumber;
    /* rest to record unseparated number. */
    for(i=1; i<N+1; i++)
    /* separate from positive natural number 1. */
    {
        if(count[progress-1] <= i)
        /* Make sure the number which is being separated is larger or equal to the previous number. */
        /* It avoids repeats. */
        {
            count[progress]=i;
            /* Store result. */
            restnumber=N-i;
            if((restnumber==0) && (progress>1))
            {
                Sum++;
                /* Get one way, add to result. */
            }
            else
            {
                separate(restnumber, progress+1);
                /* The rest number starts separate. */
            }
            count[progress]=0;
            /* Recover and backtracking. */
        }
    }
}

int main()
{
    unsigned int N ;
    printf("Input one positive natural number: N = ");
    scanf("%d", &N);
    if(N>=1)
    {
        separate(N, 1);
        printf("There are %ld way(s).\n", Sum+1);
        /* Add N itself to Sum. */
    }
    else
    {
        printf("Input data error!\n");
    }
    system("pause");
    return 0;
}
