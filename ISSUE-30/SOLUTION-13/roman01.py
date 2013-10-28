def print_roman(n):
    r = ""
    lt = [("I", 1), ("IV", 4), ("V", 5), ("IX", 9), ("X", 10), \
    ("XL", 40), ("L", 50) , ("XC", 90), ("C", 100), \
    ("CD", 400), ("D", 500) , ("CM", 900), ("M", 1000)]
    while n > 0:
        a = lt.pop()
        m = a[1] 
        d = a[0]
        r += d * (n // m)
        n %= m
    return r

for n in range(1, 31):
    print "%d=%s" % (n, print_roman(n))
    print "%d=%s" % (n*10, print_roman(n*10))
    print "%d=%s" % (n*100, print_roman(n*100))
