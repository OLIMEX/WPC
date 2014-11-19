
def levenshteind(s, t):
    m = len(s) + 1
    n = len(t) + 1
    d = [[x if y == 0 else y if x == 0 else 0 for x in xrange(m)] for y in xrange(n)]
    # parallel (SIMD, GPGPU)?
    for j in xrange(1, n):
        for i in xrange(1, m):
            d[j][i] = d[j-1][i-1] if s[i-1] == t[j-1] else min(d[j-1][i]+1, d[j][i-1]+1, d[j-1][i-1]+1)
    return d[n-1][m-1]

print levenshteind("saturday", "sunday")
print levenshteind("kitten", "sitting")

