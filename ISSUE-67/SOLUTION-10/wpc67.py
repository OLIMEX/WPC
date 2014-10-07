N = 9808.0
for s in xrange(2, 70, 2):
    m = N / (2*s)
    l = m - s + 0.5
    h = m + s - 0.5
    if l == round(l):
        print int(l), int(h)