def productcalcdigits(*args, **kwds):
    pools = map(tuple, args) * kwds.get('repeat', 8)
    result = [[]]
    for pool in pools:
        result = [x+[y] for x in result for y in pool]
    for prod in result:
        d = 1
        outop = "1"
        for s in prod:
            d += 1
            if s == "_":
                outop = outop + str(d)
            else:
                outop = outop + s + str(d)
        yield outop

#faster than eval() (time user = 4s for Raspberry Pi, myeval() = 2.8s)
def myeval(st):
    result = 0
    lastsumdigit = 0
    sign = 1 #means +1
    for s in st:
       if s in ("+", "-"):
           if sign == 1:
               result += lastsumdigit
           else:
               result -= lastsumdigit
           lastsumdigit = 0
           if s == "+":
               sign = 1
           else:
               sign = -1
       else: #digit
           lastsumdigit = lastsumdigit*10 + int(s)
    return result + sign*lastsumdigit

ans = productcalcdigits("+-_", repeat=8)
for i in ans:
    if myeval(i) == 100:
        print i

