#include <stdio.h>
#define N 3
/* define how many (N) elements of array A*/
int main(void)
{
    int i=0, j=0, M=1, temp=0, count=0;
    /* i, j as loop variant*/
    /* M to store the number of all possible array A */
    /* temp to store an ingeter*/
    /* A[count] to replace A[i] during the process */
    int A[N]={0}, d[N-1]={0};
    /* A[N]is array A, d[N-1] is array d*/
    int *p=A, *q=d;
    /* pointer p points to A[0], q points to d[0]; */
    printf("Input integer value of each elment in array A:\n" );
    for(i=0; i<N; i++)
    scanf("%d", &A[i]);
    
    for(i=0; i<N-1; i++)
    d[i]=A[i]-A[i+1];
    
    for(i=N; i>0; i--)
    M=M*i;
    
    for(i=0; i<M; i++)
    {
        while((*q <= *(q+1)) && (q != &d[N-1]))
        q=q+1;
        if(q==&d[N-1])
        {
            for(j=0; j<N; j++)
            printf("%6d", A[j]);
            printf("\n");
        }
        
         q=d;
        if(p==(&A[N-1]))
            {
                temp=A[N-1];
                A[N-1]=A[0];
                A[0]=temp;
                p=A;
                for(j=0; j<N-1; j++)
                d[j]=A[j]-A[j+1];
            }
        else if((count<N-1))
            {
                temp=A[count];
                A[count]= A[count+1];
                A[count+1]=temp;
                count++;
                if(count==N-1)
                count=0;
                p++;
                for(j=0; j<N-1; j++)
                d[j]=A[j]-A[j+1];
            }
       }
}
