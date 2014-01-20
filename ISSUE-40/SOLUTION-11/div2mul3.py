def plusone(n):
    for d in [5, 7, 11]:
        if n % d == 0:
            return False
    return True

def mul3div2(n):
    s = ""
    while n > 1:
        if (n % 3) == 0:
            s = "*3" + s
            n /= 3
        else:
            s = "/2" + s
            n *= 2
            #want formula for this decision
            if ((n + 1) % 3 ) == 0 and plusone(n + 1):
                n += 1
    return "1" + s

for n in range(2, 100):
    if (n % 11) != 0 and n not in [41, 49, 50, 53, 59, 61, 67, 68, 71, 73, 79, 80, 82, (41*2), 91, 92, 95, 97, 98, (49*2)]:
        print n, mul3div2(n)

# 45 = 1*3*3*3*3/2/2/2/2*3*3
# 50 = 1*3*3*3*3/2/2/2/2*3*3*3/2*3/2/2
# 67 = 1*3*3*3*3/2/2/2/2*3*3*3/2
# 7 = 1*3*3*3/2*3/2*3/2/2/2
# 7 = 1*3*3*3*3/2/2/2/2*3/2
# 7 = 1*3*3*3*3*3/2/2/2/2/2
# 6 = 1*3*3*3*3/2/2/2/2/2*3

# http://mathworld.wolfram.com/CollatzProblem.html
# http://codegolf.stackexchange.com/questions/13127/convert-1-into-any-positive-integer-using-only-the-operations-3-and-2
