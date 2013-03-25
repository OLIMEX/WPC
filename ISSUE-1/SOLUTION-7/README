/*
    This function calculates the distance between an infinite line given by
two points (AP,BP) and a point(CP).
    Created by: Krisztian Nemet      nemetzk@gmail.com       2013.03.23.
    Written for gcc

###########################################################################################################

    The comprehensive equation of line is: A*x+B*y+C=0, where A,B and C are
parameters.
    Defining the A,B,C parameters of the equation, from the two given
points can be done with the following determinant:
    Where the two points are: AP(ax,ay) BP(bx,by)

    |x  y   1|
    |ax ay  1|  =   0
    |bx by  1|

    x*|ay    1|  -y*|ax    1|   +   |ax     ay| = 0
       |by    1|      |bx    1|        |bx     by|

    x*(ay-by)+y*(bx-ax)+(ax*by-ay*bx)=0

    Now we can define the parameters.
    A=ay-by
    B=bx-ax
    C=ax*by-ay*bx

    Distance between point CP(cx,cy) and line is:

    if C<=0
          A*cx+B*cy+C
        d=-------------
          sqrt(A^2+B^2)
    if C>0
          A*cx+B*cy+C
        d=-------------
          -sqrt(A^2+B^2)

 */
    int A=ay-by;
    int B=bx-ax;
    int C=(ax*by)-(ay*bx);
    int numerator = A*cx+B*cy+C;
    double denominator =1;
    if (C<=0)
        denominator=sqrt(pow(A,2) + pow(B,2));
    else
        denominator=-sqrt(pow(A,2) + pow(B,2));
    return numerator/denominator;
}
