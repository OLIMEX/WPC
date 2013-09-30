#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int X;
    int Y;
}Point;

int main()
{
    Point A, B, C, D;
    int AB, BC, CD, AD, AC, BD;
    char P[4]={'A', 'B', 'C', 'D'};
    int i, countOne=0, countTwo=0, countThree=0, flag=0;
    int length[6];
    int side, diagonal;
    
    for(i=0; i<4; i++)
    {
        printf("Input X and Y coordinates of Point %c:  ", P[i]);
        switch(i)
        {
            case 0: scanf("%d, %d", &A.X, &A.Y);
                break;
            case 1: scanf("%d, %d", &B.X, &B.Y);
                break;
            case 2: scanf("%d, %d", &C.X, &C.Y);
                break;
            case 3: scanf("%d, %d", &D.X, &D.Y);
                break;
        }
    }

    AB = (A.X-B.X)*(A.X-B.X) + (A.Y-B.Y)*(A.Y-B.Y);
    BC = (B.X-C.X)*(B.X-C.X) + (B.Y-C.Y)*(B.Y-C.Y);
    CD = (C.X-D.X)*(C.X-D.X) + (C.Y-D.Y)*(C.Y-D.Y);
    AD = (A.X-D.X)*(A.X-D.X) + (A.Y-D.Y)*(A.Y-D.Y);
    AC = (A.X-C.X)*(A.X-C.X) + (A.Y-C.Y)*(A.Y-C.Y);
    BD = (B.X-D.X)*(B.X-D.X) + (B.Y-D.Y)*(B.Y-D.Y);

    for(i=0; i<6; i++)
    {
        switch(i)
        {
            case 0: length[i]=AB;
                break;
            case 1: length[i]=BC;
                break;
            case 2: length[i]=CD;
                break;
            case 3: length[i]=AD;
                break;
            case 4: length[i]=AC;
                break;
            case 5: length[i]=BD;
                break;
        }
    }

    for(i=1; i<6; i++)
    {
        if(length[0]<length[i])
        {
            side=length[0];
            diagonal=length[i];
            break;
        }
        if(length[0]>length[i])
        {
            side=length[i];
            diagonal=length[0];
            break;
        }
    }
    
    for(i=0; i<6; i++)
    {
        if(length[i]==side)
            countOne++;
        if(length[i]==diagonal)
            countTwo++;
    }

    if(countOne==4 && countTwo==2 && diagonal*diagonal==4*side*side)
        flag=1;
    else
        flag=0;
        
    if(flag)
        printf("It's a square.\n");
    else
        printf("It's not a square.\n");
    system("pause");
    return 0;
}
