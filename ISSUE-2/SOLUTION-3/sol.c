//=================================================
// START
//=================================================
#define N 10

signed int A[N];

void SortNeighboursAscending(void)
{
unsigned char c;
signed int temp;
 if(N<3) return;
 for(c=0; c<=(N-2); c++)
{
if( (A[c]-A[c+1]) > (A[c+1]-A[c+2]) )
{
temp = A[c];
A[c] = A[c+1];
A[c+1] = temp;
if(c != 0) c -= 2; // compensate postincrement
else c -= 1; //
}
}
}
//=================================================
// END
//=================================================
