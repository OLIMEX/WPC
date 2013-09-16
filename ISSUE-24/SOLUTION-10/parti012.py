import sys # for read arguments
from collections import defaultdict

ptab = defaultdict(int)

itert = 0
hitp = 0

#algorithm from http://en.wikipedia.org/wiki/Partition_%28number_theory%29
def parti(n):
    global ptab
    global itert
    global hitp

    if n < 0:
        return 0
    elif n < 2:
        return 1
    elif n < 4:
        return n
    elif ptab[n] > 0: #cache hit
        hitp += 1
        return ptab[n]

    p = 0
    kk = 1
    while True:
        for k in (kk, -kk):
            itert += 1
            kin = n - (k*(k*3 - 1)/2)
            if kin < 0:
                ptab[n] = p
                return p

            pp = parti(kin)
            if pp < 0:
                ptab[n] = p
                return p

            if k % 2 == 0:
                p -= pp
            else:
                p += pp

        kk += 1

    ptab[n] = p
    return p


if len(sys.argv) < 2:
    print 'Usage: %s integer' % sys.argv[0]
    print 'Example: %s %d returns %d' % (sys.argv[0], 6, parti(6))
else:
    n = int(sys.argv[1])
    print parti(n)
    print 'iterates=%d' % itert
    print 'cache hit=%d' % hitp
    print 'cache size %d' % len(ptab) 
    
    #for calculate array size as in http://theory.cs.uvic.ca/inf/nump/NumPartition.html
    #unfortunately, it always bigger than iteration of this algorithm
    print '((n+1)*n/2)=%d' %  ((n+1)*n/2)

#dead at n=1001 exceed recusive