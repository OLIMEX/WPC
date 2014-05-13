// for compile & link : g++ -o fft  fft.cpp
// for run :./fft


#include <complex>
#include <cmath>
#include <iostream>
using namespace std;
typedef double num;
typedef complex<double> cnum;
const double PI = 3.141592654;

void FFT(cnum* a, int n){
    int i;
    cnum *a0, * a1, u(1,0), un = exp(cnum(0,2.0*PI)/cnum(n));
    if (n == 1)
        return;
    a0 = new cnum[n/2];
    a1 = new cnum[n/2];
    for (i = 0; i < n/2; i++){
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    FFT(a0, n/2);
    FFT(a1, n/2);
    for (i = 0; i < n/2; i++){
        a[i] = a0[i] + u*a1[i];
        a[i+n/2] = a0[i] - u*a1[i];
        u*=un;
    }
}

int main()  {
    int i;
    double step = 0.0 ,  delta = 0.01;
    cnum a[1024];

    for ( i=0 ; i <= 628 ; i++) {
        a[i] = cnum ( cos(step), sin(step)) ;
        step+=delta ;
    }
    FFT(a, 629);
    for (i = 0; i < 629 ; i++) cout << a[i] << ' ' ;

    return 0;
}
