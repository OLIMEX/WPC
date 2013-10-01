#include <stdio.h>
int checkSquare(int points[][2])
{
    static int ps[3][4] = {{0,1,2,3},{0,1,3,2},{0,2,1,3}};
    int sl[4],sd;
    int p,i,tmp;
    for (p=0;p<3;p++)
    {
        for (i=0;i<4;i++)
        {
            tmp=(points[ps[p][(i+1)&3]][0]-points[ps[p][i]][0]);
            sl[i] = (tmp*tmp);
            tmp=(points[ps[p][(i+1)&3]][1]-points[ps[p][i]][1]);
            sl[i] += (tmp*tmp);
            if (sl[i]==0) return 0;
        }
        tmp=(points[ps[p][2]][0]-points[0][0]);
        sd = (tmp*tmp);
        tmp=(points[ps[p][2]][1]-points[0][1]);
        sd += (tmp*tmp);
        if (sd==0) return 0;
        if (!((sl[0]^sl[1])|(sl[2]^sl[3])|(sl[0]^sl[3])|(sd^(sl[0]+sl[1])))) return 1;
    }
    return 0;
}
int main(int argc, char** argv)
{
    // the four points given
    int points[4][2] = {{0,0},{0,1},{1,0},{1,1}};
    if (checkSquare((points))) printf("(%i,%i),(%i,%i),(%i,%i),(%i,%i) form a square!\n",
                points[0][0],points[0][1],points[1][0],points[1][1],points[2][0],points[2][1],points[3][0],points[3][1]);
    else printf("(%i,%i),(%i,%i),(%i,%i),(%i,%i) do not form a square!\n",
                points[0][0],points[0][1],points[1][0],points[1][1],points[2][0],points[2][1],points[3][0],points[3][1]);
}
