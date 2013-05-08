def cat(N):
    L = [[], [[1]], [[1, 1], [2]]]
    while len(L) <= N:
        L.append([[1] + x for y in L[-1:] for x in y] +
                 [[2] + x for y in L[-2:-1] for x in y])
    return L[N]

# http://stackoverflow.com/questions/8049798/understanding-nested-list-comprehension

for x in xrange(5):
    print x, len(cat(x)), cat(x)
for x in xrange(5, 21):
    print x, len(cat(x))
    
