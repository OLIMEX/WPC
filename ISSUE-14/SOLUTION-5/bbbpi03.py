import sys
#http://en.wikipedia.org/wiki/Bailey%E2%80%93Borwein%E2%80%93Plouffe_formula

#interesting algorithm for continued fraction
#needs 20 loops for 314159265358979
#http://www.cs.utsa.edu/~wagner/pi/pi_cont.html
#http://en.wikipedia.org/wiki/Generalized_continued_fraction
#http://www.cs.utsa.edu/~wagner/pi/ruby/pi_works.html
#http://www.cs.utsa.edu/~wagner/pi/pi.html

def mygcd(a, b):
    while b != 0:
        t = b
        b = a % t
        a = t

    return a

def mylcm(a, b):
    return (a * b) / mygcd(a, b)

def mydigitcount(n):
    r = 0
    #should I use log10()?
    while n>0:
        n = n / 10
        r += 1
    return r

def bbb_a(i):
    return(120*i**2 + 151*i + 47)

def bbb_b(i):
    return(512*i**4 + 1024*i**3 + 712*i**2 + 194*i + 15)

k = 10000 #k loops as many loops as you can
aa = bbb_a(0)
bb = bbb_b(0)
h = 1
for i in range(1, k):
    # to compute aa/bb += ah/bh*16**i
    h = h * 16
    ah = bbb_a(i)
    bh = bbb_b(i)*h
    lcmab = mylcm(bb, bh)
    aa = (aa * lcmab / bb) + (ah * lcmab / bh)
    bb = lcmab

# ah / bh from previous loop means digit accuracy
# bh / ah - 1 for digits that we should consider
l = mydigitcount(bh/ah) - 1
while aa>0 and l>0:
    d = aa / bb
    sys.stdout.write(str(d))
    sys.stdout.flush()
    aa = 10 * (aa % bb)
    l -= 1

#just print new line
print
