from math import sqrt, pi, sin, cos, hypot
from random import uniform, randint, shuffle

eps = 1e-6
inf = 1e6

def line(A, B):
    (Ax, Ay), (Bx, By) = A, B
    if abs(Bx - Ax) < eps:
        return (Ax, inf)
    else:
        m = (By - Ay) / (Bx - Ax)
        c = Ay - m * Ax
        return (m, c)

def midpoint(A, B):
    (Ax, Ay), (Bx, By) = A, B
    return ((Ax+Bx)/2, (Ay+By)/2)

# http://www.regentsprep.org/Regents/math/geometry/GCG6/RCir.htm

def circle(A, B, C):
    (mAB, cAB) = line(A, B)
    (mBC, cBC) = line(B, C)
    
    if abs(mAB - mBC) < eps:
        return ((inf, inf), inf)
    else:
        x = (mAB*mBC*(C[1]-A[1])+mAB*(B[0]+C[0])-mBC*(A[0]+B[0]))/(2*(mAB-mBC))
        (Px, Py) = midpoint(A, B)
        mP = -1/mAB
        y = mP * (x - Px) + Py
        r = sqrt((x-B[0])**2 + (y-B[1])**2)
        return ((x, y), r)

def makecircle(x, y, r):
    A = [uniform(0, 2*pi) for _ in xrange(r)]
    return [(x + r * cos(a), y + r * sin(a)) for a in A]

circle8 = (makecircle(150, 150, 150) +
           makecircle(150, 100, 100) +
           makecircle(150, 200, 100) +
           makecircle(150,  50,  50) +
           makecircle(150, 150,  50) +
           makecircle(150, 250,  50) +
           makecircle( 30, 150,  30) +
           makecircle(270, 150,  30))

def findcircle():
    l = len(circle8)
    while True:
        A = circle8[randint(0, l-1)]
        B = circle8[randint(0, l-1)]
        C = circle8[randint(0, l-1)]
        ((cX, cY), cR) = circle(A, B, C)
        count = 0
        for (Px, Py) in circle8:
            d = hypot(Px - cX, Py - cY)
            if abs(d - cR) < eps:
                count = count + 1
        if count > 10:
            return ((cX, cY), cR, count)

least = 1000
while True:
    ((cX, cY), cR, count)= findcircle()
    if least > count:
        least = count
        print ((cX, cY), cR, count)
    if count == len(circle8):
        print "A circle passes through all the points"

# sample output
##((-0.0, 0.0), 5.0)
##((150.00000000000006, 150.0000000000001), 149.99999999999991, 150)
##((150.0, 100.00000000000001), 100.0, 101)
##((150.0, 199.9999999999999), 99.99999999999991, 100)
##((150.00000000000557, 249.99999999994424), 50.000000000055685, 50)
##((270.00000000000006, 149.99999999999997), 30.000000000000018, 30)
##((150.00023562895996, 150.0000823265659), 149.99975042060626, 11)
    
    
