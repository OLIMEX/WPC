#include <stdio.h>

int main()
{
    float Ax, Ay, Bx, By, Cx, Cy;

    printf("Coordinates of point A: ");
    scanf("%f %f", &Ax, &Ay);
    printf("Coordinates of point B: ");
    scanf("%f %f", &Bx, &By);
    printf("Coordinates of point C: ");
    scanf("%f %f", &Cx, &Cy);

    float surf = Ax*By - Bx*Ay + Bx*Cy - Cx*By + Cx*Ay - Ax*Cy;

    if (surf == 0)
        printf("In line\n");
    else if (surf > 0)
        printf("Counterclockwise\n");
    else
        printf("Clockwise\n");

    return 0;
}
