import string

d = 2
p = 'dgjmptw'

n = string.digits[d]
c = 0
t = {}

for i in xrange(26):
    if p.find(string.lowercase[i]) > -1:
        d = d + 1
        n = string.digits[d]
        c = 1
    else:
        c = c + 1
    s = n * c
    t[string.lowercase[i]] = s
    t[string.uppercase[i]] = s

m = 'Hello'

for l in m:
    if l in t:
        print t[l],

    
