def factorial(n):
    if n == 0:
        return 1
    else:
        return n * factorial(n-1)

# http://en.wikipedia.org/wiki/Chudnovsky_algorithm    
def term(k):
    p = 1 - 2 * (k%2)
    f = factorial(6*k)
    g = 13591409 + 545140134*k
    t = factorial(3*k)
    c = factorial(k)**3
    s = 640320.0**(3*k + 1.5)
    print p, f, g, t, c, s
    return 12 * (p*f*g) / (t*c*s)

# 1 1 13591409 1 1 512384047.996
print 1.0/term(0) # 3.14159265359
# -1 720 558731543 6 1 1.34519982239e+26
print 1.0/term(1) # -1.6719416597e+14
