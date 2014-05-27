
# http://en.wikipedia.org/wiki/Lucas%E2%80%93Lehmer_primality_test
# http://en.wikipedia.org/wiki/Mersenne_prime
# http://en.wikipedia.org/wiki/Perfect_number

#detemines m = 2**p - 1 is prime?
def lucaslehmer(p):
    s = 4
    # Perhaps multicore, SIMD, MPI or GPGPU boost "s*s" :)
    for i in range(2, p):
        s = modbase2_1pdigits(s*s - 2, p) 
    return s == 0

# returns s % m when m = (2**p - 1)
# also s % m == (U + (L % m)) % m when s splited bits to U|L
def modbase2_1pdigits(s, p):
    m = int("1"*p, 2) # faster than 2**p - 1
    ubits = 1
    while ubits > 0:
        ubits = s >> p  # upper bits 
        lbits = s & m # lower bits 
        s = ubits + (0 if lbits == m else lbits)
    return s  

# 2 is prime but we skip
# http://mathworld.wolfram.com/EvenPrime.html
for i in range(3, 57885162):
    if lucaslehmer(i):
        # from Euclid we can make perfect number (in base 2) from Mersenne prime
        #print  "0b"+"1"*i + "0"*(i-1) + " is perfect number (base2)."
        print  "int(\"1\"*", i, "+\"0\"*", (i-1), ", 2) is perfect number (base2)."

