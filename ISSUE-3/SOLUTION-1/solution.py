#Quick and dirty python:

N = ['A13-OLinuXino', 'iMX233-OLinuXino', 'MOD-PULSE', 'MOD-IO']
M = map(str.lower, N)

def uniq(w):
    for l in xrange(1, 1+len(w)):
        for s in xrange(0, len(w)-l+1):
            t = w[s:s+l]
            c = 0
            for f in M:
                if f.find(t) <> -1:
                    c = c + 1
            if c == 1:
                return t

for (w, l) in zip(N, M):
    print w, uniq(l)
