#include <stdio.h>
#include <assert.h>

int main ()
{
    float Ax, Ay, Bx, By, Cx, Cy;
    float surf;

    Ax = 0; Ay = 0; Bx = 1; By = 1; Cx = 2; Cy = 2;
    surf = Ax*By - Bx*Ay + Bx*Cy - Cx*By + Cx*Ay - Ax*Cy;
    assert(surf == 0);

    Ax = 0; Ay = 0; Bx = 1; By = 1; Cx = -1; Cy = -1;
    surf = Ax*By - Bx*Ay + Bx*Cy - Cx*By + Cx*Ay - Ax*Cy;
    assert(surf == 0);

    Ax = 0.0001; Ay = 0.0001; Bx = 444444.0001; By = 444444.0001; Cx = 888888.0001; Cy = 888888.0001;
    surf = Ax*By - Bx*Ay + Bx*Cy - Cx*By + Cx*Ay - Ax*Cy;
    assert(surf == 0);

    Ax = 123; Ay = 456; Bx = 456; By = 789; Cx = -123; Cy = 789;
    surf = Ax*By - Bx*Ay + Bx*Cy - Cx*By + Cx*Ay - Ax*Cy;
    assert(surf > 0);

    Ax = 0.0001; Ay = 0.0001; Bx = 0.0002; By = 0.0002; Cx = -0.0002; Cy = 0.0002;
    surf = Ax*By - Bx*Ay + Bx*Cy - Cx*By + Cx*Ay - Ax*Cy;
    assert(surf > 0);

    Ax = 123.456; Ay = 789.012; Bx = 123.456; By = 0; Cx = 0; Cy = 1;
    surf = Ax*By - Bx*Ay + Bx*Cy - Cx*By + Cx*Ay - Ax*Cy;
    assert(surf < 0);

    Ax = 1; Ay = 1; Bx = 0; By = -1; Cx = -1; Cy = 1;
    surf = Ax*By - Bx*Ay + Bx*Cy - Cx*By + Cx*Ay - Ax*Cy;
    assert(surf < 0);

    printf("All tests ok\n");

    return 0;
}
