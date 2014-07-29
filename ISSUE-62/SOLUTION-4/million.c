#include <stdio.h>


int main(void) {

   int x,y,w,z=1000000;
      
       for(y = 1; y <= z; y++)
       { 
          x=z/y;
          w=z%y;
           if(w==0)
            if(x%10 && y%10)
              printf("%d %d\n",x,y);
       }
   return 0;
}

