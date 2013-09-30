#include <stdio.h>
#include <conio.h>
#include <math.h>

#define	EQUAL_POINTS	-2
#define	POINTS_IN_LINE	-1
#define	QUADRANGLE		0
#define	RECTANGLE		1
#define	RHOMBUS			2
#define	SQUARE			3

struct s_Point
{
	double X, Y;
};
typedef	struct s_Point Point;

void Swap (Point *A, Point *B)
{
	Point Temp;
	Temp = *A;
	*A = *B;
	*B = Temp;
	return;
}

double Distance (Point A, Point B)
{
	return sqrt ((A.X - B.X) * (A.X - B.X) + (A.Y - B.Y)*(A.Y - B.Y));
}

int Check_Equal_Points (Point P[])
{
	int i, j;
	for (i=0; i<4; i++)
		for (j=i+1; j<4; j++)
			if ((P[i].X == P[j].X) && (P[i].Y == P[j].Y))
				return 1;
	return 0;
}

int Check_Line (Point A, Point B, Point C)
{
	double D0, D1, D2;
	D0 = Distance (A, B);
	D1 = Distance (B, C);
	D2 = Distance (C, A);
	if ((D0+D1==D2) || (D1+D2==D0) || (D2+D0==D1))
		return 1;
	else
		return 0;
}

int Check_Points_in_Line (Point P[])
{
	if (Check_Line (P[0], P[1], P[2]) ||
		Check_Line (P[0], P[1], P[3]) ||
		Check_Line (P[0], P[2], P[3]))
		return 1;
	else
		return 0;
}

int Check_Rhombus (Point P[])
{
	double S[4];
	S[0] = Distance(P[0], P[1]);
	S[1] = Distance(P[1], P[2]);
	S[2] = Distance(P[2], P[3]);
	S[3] = Distance(P[3], P[0]);
	return ((S[0] == S[1]) && (S[0] == S[2]) && (S[0] == S[3]));	// if all sides are equal ==> rhombus
}

int Check_Rectangle (Point P[])
{
	double D02, D13;
	D02 = Distance (P[0], P[2]);
	D13 = Distance (P[1], P[3]);
	return ((D02 == D13) &&	// if diagonals are equal ==> rectangle... or maybe not
			// if the diagonals are equal BUT smaller than any of sides it links ==> it is self-crossing ==> fake rectangle
			(D02 > Distance (P[0], P[1])) && (D02 > Distance (P[1], P[2])) &&
			(D13 > Distance (P[2], P[3])) && (D13 > Distance (P[3], P[0]))
			);
}

int Check_Figure (Point P[])
{
	int Res = 0;

	if (Check_Equal_Points (P))
		return EQUAL_POINTS;	// two or more points are same

	if (Check_Points_in_Line (P))
		return POINTS_IN_LINE;	// three or more points are in line and quadrangle is impossible to be built

	// 0 1 2 3 order of points describe the same figure as:
	// 1 2 3 0; 2 3 0 1; 3 0 1 2; 3 2 1 0; 0 3 2 1; 1 0 3 2; 2 1 0 3;
	if (Check_Rectangle (P))
		Res = Res | RECTANGLE;
	if (Check_Rhombus(P))
		Res = Res | RHOMBUS;
	if (Res)
		return Res;

	Swap (P+1, P+2);
	// 0 2 1 3 order of points describe the same figure as:
	// 2 1 3 0; 1 3 0 2; 3 0 2 1; 3 1 2 0; 0 3 1 2; 2 0 3 1; 1 2 0 3;
	if (Check_Rectangle (P))
		Res = Res | RECTANGLE;
	if (Check_Rhombus(P))
		Res = Res | RHOMBUS;
	if (Res)
		return Res;

	Swap (P+2, P+3);
	// 0 2 3 1 order of points describe the same figure as:
	// 2 3 1 0; 3 1 0 2; 1 0 2 3; 1 3 2 0; 0 1 3 2; 3 1 0 2; 3 2 0 1
	if (Check_Rectangle (P))
		Res = Res | RECTANGLE;
	if (Check_Rhombus(P))
		Res = Res | RHOMBUS;
	if (Res)
		return Res;
	return QUADRANGLE;
}

int main ()
{
	Point Edge[4];
	int i;
	for (i=0; i<4; i++)
	{
		printf ("Input Edge[%d]: ", i);
		scanf ("%lf %lf", &Edge[i].X, &Edge[i].Y);
	}

	switch (Check_Figure (Edge))
	{
	case EQUAL_POINTS:
		printf ("Two or more points are same!\n");
		break;
	case POINTS_IN_LINE:
		printf ("Three or more points are in line!\n");
		break;
	case QUADRANGLE:
		printf ("Figure is Quadrangle!\n");
		break;
	case RECTANGLE:
		printf ("Figure is Rectangle!\n");
		break;
	case RHOMBUS:
		printf ("Figure is Rhombus!\n");
		break;
	case SQUARE:
		printf ("Figure is Square!\n");
		break;
	}
	getch ();
	return 0;
}
