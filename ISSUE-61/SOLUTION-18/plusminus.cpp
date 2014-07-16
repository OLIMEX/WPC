// compile & link : g++ -o plusminus plusminus.cpp
//run : ./plusminus

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;


long test ( char* expresion ) ;


int main()
{

   int i[9] , j ;
   char buf[128] , wrk [8] , save[128];
   char oper[3][2] = {{'+',0},{'-',0},{' ',0}} ;

    for ( i[1]=0;i[1]<3;i[1]++)
    for ( i[2]=0;i[2]<3;i[2]++)
    for ( i[3]=0;i[3]<3;i[3]++)
    for ( i[4]=0;i[4]<3;i[4]++)
    for ( i[5]=0;i[5]<3;i[5]++)
    for ( i[6]=0;i[6]<3;i[6]++)
    for ( i[7]=0;i[7]<3;i[7]++)
    for ( i[8]=0;i[8]<3;i[8]++)
    {
        buf[0] = '1' ;  buf[1] = 0 ;
        for ( j=1;j<=8;j++) {
            if ( i[j] != 2 )
              strcat ( buf , oper[i[j]]  ) ;
            wrk[0] = '0' + j + 1 ;
            wrk[1] = 0 ;
            strcat ( buf , wrk ) ;
        }
        long s ;
        strcpy ( save , buf ) ;
        s = test ( buf ) ;
        if ( s == 100 )
            cout << save << endl ;

    }

    return 0;
}


long test ( char* expresion ) {
  char  oper[16] ,*pc;
  int n , i , j ,operand[16];

  pc = expresion ;
  for ( n=0 , pc = expresion ; *pc != 0 ; ++pc  )
    if ( *pc == '+' || *pc == '-')
        oper[n++] = *pc ;
  i = 0 ;
  pc = strtok ( expresion , "+- " );
  while ( pc != NULL ) {
    operand[i++] = atoi ( pc ) ;
    pc = strtok ( NULL , "+- " );
  }

   if ( (n+1) != i  ) {
        cout << "error " << endl ;
        return -1 ;
   }

   long s=operand[0] ;

   for ( j=1; j<i;j++)
     if ( oper[j-1]=='+')
        s += operand[j] ;
     else
        s -= operand[j] ;


return s ;
}
