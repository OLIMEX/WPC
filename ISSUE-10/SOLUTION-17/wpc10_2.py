from fractions import Fraction
from math import ceil

def frac(a, b):
    f = Fraction(a, b)
    l = []
    while f > 0:
        n = int(ceil(1/f))
        i = Fraction(1, n)
        f = f - i
        l.append(n)
    return l

a = 5
b = 121
print frac(a, b), "is almost right!"

def frac2(b):
    f = Fraction(2, b)
    x = b - 1
    while x > 0:
        x1 = Fraction(1, x)
        d = f - x1
        s = str(d)
        if s[0:2] == '1/':
            y = int(s[2:])
#            print b, x, y
            return (x1, Fraction(1, y))
        x = x - 1

print "Rhind?"
for b in xrange(3, 100):
    if b%2 == 1:
        print Fraction(2, b), '=', frac2(b)

print "E12, series and parallel"
for x in xrange(1, 13):
    r = 10**(1 + (x/12.0))
    s = 10 + r
    p = 1/(0.1 + 1/r)
    print x, r, s, p

print "E12, from E3, using two resistors in series or parallel"
print 10, 10+2.2, 10+4.7, 1/(1.0/22 + 1.0/100)
print 22, 22+4.7, 22+10,  1/(1.0/47 + 1.0/220)
print 47, 47+10,  47+22,  1/(1.0/100 + 1.0/470)
    

