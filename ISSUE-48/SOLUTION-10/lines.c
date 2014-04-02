#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
int readdouble(double *result)
{
   char *end, buff [ 32 ];
   return fgets(buff, sizeof buff, stdin) && !isspace(*buff) &&
          (*result = strtod(buff, &end)), ( *end == '\n' || *end == '\0' );
}
int delivervalue (double *value)
{
   do
   {
      fputs("Please enter a valid floating-point number: ", stdout);
      fflush(stdout);
   } while (!readdouble(value));
   return 0;
}

int readpoint (const char* name,double *X,double *Y)
{
   double value = -66.9;
   printf("Please enter the X coordinate of point %s\n",name);
   delivervalue(&value);
   *X=value;
   value = -66.9;
   printf("Please enter the Y coordinate of point %s\n",name);
   delivervalue(&value);
   *Y=value;
   return 0;
}
int checkdistance (double *zX,double *zY,double *vX,double *vY)
{
   double deltaX,deltaY;
   deltaX=*zX-*vX;
   deltaY=*zY-*vY;
   if((deltaX+deltaY)==0)
   {
      printf("Error, coordinates for two points are the same.\n");
      fputs("Press enter to exit\n", stdout);
      fflush(stdout); 
      while(getchar()!='\n');   
      return 1;
   }
   if((sqrt(pow(deltaX,2)+pow(deltaY,2)))<0.001)
   {
      printf("Points are very close,errors in rounding of floating point values can affect the calculations!\n");
   }
   return 0;
}

int main(void)
{
   double value;
   double deltaX, deltaY;
   double AX,AY,BX,BY,CX,CY;
   double A,B;	
   fputs("This program calculates if tree points make a clock-wise or a conterclock-wise turn\n", stdout);
   
   readpoint ("A",&AX,&AY);
   readpoint ("B",&BX,&BY);
   deltaX=BX-AX;
   deltaY=BY-AY;

   if(checkdistance(&AX,&AY,&BX,&BY)==1)
	return 0;
   readpoint ("C",&CX,&CY);
   if(checkdistance(&BX,&BY,&CX,&CY)==1)
	return 0;
   printf("Points: A=(%g, %g) B=(%g, %g) C=(%g, %g)\n", AX,AY,BX,BY,CX,CY);
   if(deltaX>0.001)
   {
      A=deltaY/deltaX;
      B=AY-(A*AX);
      printf("Line connecting A and B: y=%g*x+(%g)\n", A,B);
      value=A*CX+B;
      value-=CY;
   }else{
      printf("Line connecting A and B: x=%g\n", AX);
      value=B-CY;
   }
   if(abs(value)<0.001)
   { 
      fputs("C lies on the AB line\n", stdout);
   }else if(value>0)
      fputs("C lies clock-wise to AB line\n", stdout);
   else
      fputs("C lies counterclock-wise to AB line\n", stdout);

 fputs("Press enter to exit\n", stdout);
 fflush(stdout); 
 while(getchar()!='\n');   
 return 0;
 }

