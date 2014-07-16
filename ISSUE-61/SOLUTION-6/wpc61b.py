from itertools import product
print [x for x in ['{}'.join(str(d) for d in xrange(1, 10)).format(*p) for p in product(['+', '-', ''], repeat=8)] if (eval(x) == 100)]
