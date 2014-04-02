#include "drei.h"

void arePointsCW(point2d_t a, point2d_t b, point2d_t c, char *answer)
{
//A-B tagneng angle
int  a_b = (b.x-a.x)/(b.y-a.y);
int  a_c = (c.x - a.x)/(c.y - a.y);

     sprintf( answer, "a(%d, %d) b(%d, %d) c(%d, %d)\r\n",
	      a.x, a.y,
	      b.x, b.y,
	      c.x, c.y
	      );
 if (a_b < a_c)
   {
     sprintf( answer, "%s --- CW\r\n", answer);
     return;
   }
 if (a_b > a_c)
   {
     sprintf( answer, "%s --- CCW\r\n", answer);
     return;
   }
 else
   {
     sprintf( answer, "%s --- IN-LINE\r\n", answer);
     return;
   }
     sprintf( answer, "Wrong code execution!\r\n" );

return;
}
