from fractions import Fraction

def frac(a, b):
    f = Fraction(a, b)
    l = []
    n = 2
    while f > 0:
        i = Fraction(1, n)
        if i <= f:
            f = f - i
            l.append(n)
            print f, l
        n = n + 1
    return l

a = 6
b = 7
print frac(a, b)


