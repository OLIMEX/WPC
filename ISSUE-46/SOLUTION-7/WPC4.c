#include <stdio.h>
/********  mathematical explanation
  Minutes(t)=Hours(t)+360x
  (x is an integer that represent the number of complete turns of the minutes arrow)
  360t=30t+360x  (360 is a complete turn in degrees, 30 degrees is 1/12 turn)
  330t=360x
  t=(360/330)x=(12/11)x
  we are considering 12 hours, so:
  12=(12/11)x ==> x=11 ==> clock arrows will cross 11 times!
********/
int main()
{
  int times=0;
  float hours, minutes, seconds, millis;
  // **** The first cross occurs at 0:00:00.000 = the start of the first hour!
  while((hours=(float)12/11*times++)<12)
  {
    minutes=(hours-(int)hours)*60;
    seconds=(minutes-(int)minutes)*60;
    millis=(seconds-(int)seconds)*1000;
    printf("%2d) %02d:%02d:%02d.%03d\n",times,(int)hours,(int)minutes,(int)seconds,(int)millis);
  }
  printf("In 12 hours, clock arrows cross %d times !\n",times-1);     
}



