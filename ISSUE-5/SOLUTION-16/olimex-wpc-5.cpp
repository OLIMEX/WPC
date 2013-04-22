#include <iostream>
#include <tr1/random>
#include <sstream>
#include <cmath>
#include <cfloat>
#define NDEBUG
#include <cassert>

using namespace std::tr1;

const int ARRAY_SIZE = 4096*32;

double xArray[ARRAY_SIZE];
double yArray[ARRAY_SIZE];

// see: http://www.efg2.com/Lab/Mathematics/Buffon.htm
// for random direction algoritm
// Division of Semicircle into 2N Intervals 
// Using Half-Angle Formula and Rotation Formula
void prepare_array()
{
 double cosAngle = 0.0;
 double sinAngle = 1.0;
 
 for (int i = 0; i < log2(ARRAY_SIZE)-1; i++)
 {
   double lastCos = cosAngle;
   sinAngle = sqrt(0.5 * (1.0 - lastCos));
   cosAngle = sqrt(0.5 * (1.0 + lastCos));
 }
 xArray[0] = 1.0;
 yArray[0] = 0.0;
 for (int i = 1; i < ARRAY_SIZE; i++)
 {
   xArray[i] = cosAngle*xArray[i-1] - sinAngle*yArray[i-1];
   yArray[i] = sinAngle*xArray[i-1] + cosAngle*yArray[i-1];
 } 
}
int main(int argc, char *argv[])
{
  prepare_array();
   
  if (argc < 4)
  {
    std::cout << "usage:" <<  std::endl
           << argv[0] << "needleCount needleLengt distanceBetweenLines"  << std::endl
           << "example:" <<  std::endl
           << argv[0] << " 10000 50 60" << std::endl;
    return -1;         
  }
  int count = 0;
  std::istringstream(argv[1]) >> count;
  double l = strtod(argv[2], NULL);
  double d = strtod(argv[3], NULL);

  // distance() generates the random number in the 
  // [0, d/2+DBL_MIN) it is the distance between the needle and 
  // the closest line
  variate_generator<mt19937, uniform_real<> 
    > distance(mt19937(time(NULL)), uniform_real<>(0, d/2+DBL_MIN));       

  // direction() generate random interger [0, ARRAY_SIZE-1],
  // basicaly this is the offset in the sin and cos arrays 
  variate_generator<mt19937, uniform_int<> 
    > direction(mt19937(time(NULL)), uniform_int<>(0, ARRAY_SIZE-1));       

  int cross = 0;
  for (int i = 0 ; i < count ; i ++)
  {
        double y = yArray[direction()] * l/2;       
        assert(distance() <= d/2);
        
        if (distance()<= y)
        {
          cross++;
        }
  }
  double P = cross * 1.0 / count;
     
  if (l < d)
  {
    double pi = 2 * l/d / P;
    std::cout << pi << std::endl;
  }
  else
  { 
    //see: 
    // Note on Buffon's Problem
    // with a Long Needle
    // Yulong Xu and Yongliang Shi
    // Applied Mathematical Sciences, Vol. 3, 2009, no. 24, 1189 - 1192
    // http://www.m-hikari.com/ams/ams-password-2009/ams-password21-24-2009/xuAMS21-24-2009.pdf
    double X = 2 * (l - sqrt(l*l - d*d));
    double pi = (X - 2*d*asin(d/l))/(d*(P-1));
    std::cout << pi << std::endl;
  }
  return 0;
}

