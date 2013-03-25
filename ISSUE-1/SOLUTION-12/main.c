
/* Dimityr Tomow - dimityrtomow@mail.bg
   00:40 GMT+2 24.03.2013 */

#include <stdio.h>
#include <math.h>

/* finds the distance between two points described with coordinates
 ( same as finding a magnitude of a signal
   represented by its imaginary and real part after fft :D )
   */
double mag(int x1, int y1, int x2, int y2);
/* finds the area of a triangle described by points with distance a, b and c */
double area(double a, double b, double c);
/* finds the distance between point c(cX,cY) and endless line described by
   points a(aX,aY) and b(bX,bY) */
double findch(int defPoints[3][2]);

int main(void)
{
  int points[3][2];
  double cH; // cH - altitude from point C toward line A-B
            // which is the distance between point C and line described by A,B
  
  while(1)
  {
          //Gather data
          printf("Give coordinate X of point A:");
          scanf("%d", &points[0][0]);
          printf("Give coordinate Y of point A:");
          scanf("%d", &points[0][1]);
          printf("Give coordinate X of point B:");
          scanf("%d", &points[1][0]);
          printf("Give coordinate Y of point B:");
          scanf("%d", &points[1][1]);
          printf("Give coordinate X of point C:");
          scanf("%d", &points[2][0]);
          printf("Give coordinate Y of point C:");
          scanf("%d", &points[2][1]);
          //Calculate
          cH = findch(points);
          //Info
          printf("\nDistance between point C and line described by points A and B is: %f.\n\n", cH); 
  };
          
  return 0;
}

double findch(int defPoints[3][2])
{
      double aD, bD, cD; //distances between points B-C, A-C, A-B
      double areaT; //area of the triangle of points A,B,C
      
      cD = mag(defPoints[0][0], defPoints[0][1], defPoints[1][0], defPoints[1][1]);
      bD = mag(defPoints[0][0], defPoints[0][1], defPoints[2][0], defPoints[2][1]);
      aD = mag(defPoints[1][0], defPoints[1][1], defPoints[2][0], defPoints[2][1]);
      
      areaT = area(aD, bD, cD);
      
      return (2*areaT/cD);
}

double mag(int x1, int y1, int x2, int y2)
{
      int point1, point2;
      point1 = abs(x1-x2);
      point2 = abs(y1-y2);
      return sqrt(point1*point1+point2*point2);
}

double area(double a, double b, double c)
{
      double p;
      
      p = (a + b + c) / 2;
      
      return sqrt(p*(p-a)*(p-b)*(p-c));
}