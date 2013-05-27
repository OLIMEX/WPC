def reciprocate(a,b):    from math import ceil    while a > 0:        k = ceil(b/a)        a = a*k-b        b = b*k                print(k)
