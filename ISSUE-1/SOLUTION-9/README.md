Hello,

I am sending a code that is a solution to the weekend challenge :]
However my code works on float numbers, as using ints for this purpose would be mathematically incorrect.
Because even if coordinates are integers, distance or sqrt could be a real number. Of course it is simple to change 
coordinates to ints, and to cast them to floats.

Function finds so called normal equation of the line - which is also a special form of general line equation.
pA, pB and pC are arrays containing x and y coordinates of A,B, and C points.
pA[]={xA,yA} and so on.
d is distance. ABC is an array containing general coefficients of the line.
Language solution is C++, but it is in written somewhat C style.

Best regards,
Misery
  

#include <iostream>
#include <cmath>
void distance(const float pA[],const float pB[],const float pC[],float ABC[],float &d)
{
  //function finds general line equation: Ax+By+C==0
  //and the distance between this line and point pC
  const float dx=pB[0]-pA[0],
	          dy=pB[1]-pA[1];
  if (abs(dx)<0.000001)
  {
   d=std::abs(pA[0]-pC[0]);
   ABC[0]=1;
   ABC[1]=0;
   ABC[2]=-pA[0];
  }
  else if(abs(dy)<0.000001)
  {
   d=std::abs(pA[1]-pC[1]);
   ABC[0]=0;
   ABC[1]=1;
   ABC[2]=-pA[1];  
  }
  else
  {
    ABC[0]=dy/std::sqrt((float)dx*dx+dy*dy);
    ABC[1]=std::sqrt(1.f-ABC[0]*ABC[0]);
    ABC[2]=-(ABC[0]*pA[0]+pA[1]*ABC[1]);
    if (std::abs(ABC[0]*pB[0]+pB[1]*ABC[1]+ABC[2])>0.00001f) 
    {
	  ABC[0]=-ABC[0];
	  ABC[2]=-(ABC[0]*pA[0]+pA[1]*ABC[1]);
    }
    d=std::abs(pC[0]*ABC[0]+pC[1]*ABC[1]+ABC[2]);
  }  
}

int _tmain(int argc, _TCHAR* argv[])
{
	float pA[]={72,10},pB[]={-45,10},pC[]={-38,58},
		ABC[]={0,0,0},d=0;
	distance(pA,pB,pC,ABC,d);
	std::cout<<d<<std::endl;
	std::cout<<"A="<<ABC[0]<<" B="<<ABC[1]<<" C="<<ABC[2]<<std::endl;
	getchar();
	return 0;
}