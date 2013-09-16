#include <stdio.h>

#define MAXNUMBER 501


int num [ MAXNUMBER ];
void dump ( int ) ;
void devide_num( int , int ) ;


int main(void) {
  int number ;

  printf ( "input number (1 - 500) :  ") ;
  scanf ( "%d" , &number ) ;
  num [ 0 ] = number + 1;

  if ( number < 1 || number > 500) {
    printf ( "input number between  1 and  500 \n") ;
    return 1 ;
  }

  devide_num ( number , 1);
  return  0 ;
}


void dump (int  len)
{
 int  i;
 for (i = 1; i <= len; i++)
    if ( i < len )
       printf("%d + ", num[i] );
    else
       printf("%d\n", num[i]  );
 return ;
}

void devide_num(int n, int position)
{
  int i ;
  if (0 == n ) {
    dump(position - 1 );
    return ;
  }
  else {
    for (i = n; i >= 1; i--) {
      num[position] = i;
      if (num [ position ] <= num [ position - 1 ] )
         devide_num (n - i, position + 1 );
    }
    return ;
  }
  return ;
}

