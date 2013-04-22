/*
 * OLIMEX WEEKEND PROGRAMMING CHALLENGE ISSUE #5
 * author: Hanspeter Portner
 * language: C
 *
 * h: needle length
 * w: strip width
 * n: # of needles to throw
 * h: # of needles crossing a line
 * i: counter
 * x: distance of needle center to nearest line (random)
 * e: distance of needle ending from needle center measured perpendicular to the strips (random)
 *
 * (X,Y): random point in a normalized circle around needle center (that's where the needle points to)
 * L2: square of the distance L of the random point (X,Y) from the needle center
 * Pi: approximated Pi
 *
 * When e >= x, then we have a crossing, so we just need to get to e...
 * The simplest approach would be e=l*sin(theta), where theta is the random angle [0:Pi]
 * the needle is pointing to, but as we want to approximate Pi, we cannot use it in the calculation...
 * Apart from that, sine is slow...
 * Instead of a random angle giving us the direction of the needle, we use a random point (X,Y)
 * in a normalized circle around the needle center.
 * With two similar triangles, we have y/(0.5l) = Y/L = Y/sqrt(XX+YY), and we get e = 0.5l*Y/sqrt(X*X+YY)
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int
main (int argc, char **argv)
{
	double l, w;
	size_t i, n, h = 0;
	double x, e, X, Y, L2, theta, Pi;

	srand48 (time (NULL));
	fscanf (stdin, "%lf%lf%li", &l, &w, &n);

	for (i=0; i<n; i++)
	{
		x = w * drand48 (); // actually 0.5*w...
		do
		{
			X = drand48 ();
			Y = drand48 ();
			L2 = X*X + Y*Y;
		} while (L2 > 1.0);
		e = l * Y / sqrt (L2); // actually 0.5*l...
		h += e >= x;
	}

	if (l <= w)
		Pi = 2.0*l*n / (w*h);
	else
		Pi = 2.0*(l - sqrt(l*l-w*w) - w*asin(w/l)) / (w*((double)h/n-1)); // we can't probably use asin here, as Pi=2*asin(1)

	printf ("π is approx. %lf\n", Pi);
	printf ("we're off by %lf%\n", 100*(Pi/M_PI - 1));

	return 0;
}
