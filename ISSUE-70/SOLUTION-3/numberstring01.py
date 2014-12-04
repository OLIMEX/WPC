
words = {"zero":0, "one":1, "two":2, "three":3, "four":4, "five":5, "six":6, "seven":7, "eight":8, "nine":9, \
  "ten":10, "eleven":11, "twelve":12, "thirteen":13, "fourteen":14, "fifteen":15, "sixteen":16, "seventeen":17, "eighteen":18, "nineteen":19, \
  "twenty":20, "thirty":30, "forty":40, "fifty":50, "sixty":60, "seventy":70, "eighty":80, "ninety":90, \
  "hundred":100, "hundreds":100, "thousand":1000, "thousands":1000, "million":1000000 }

def stringtonum(engnumlst):
    a = 0
    a2 = 0
    prevn = 0
    for w in engnumlst:
        n = words[w]
        if n in [100, 1000, 1000000] and prevn < n:
	    a = (1 if a == 0 else a) * n
        elif prevn in [100, 1000, 1000000] and prevn > n:
            a2 = a2 + a
            a = n
        else:
            a = a + n
        prevn = n
    a2 = a2 + a
    return a2

#testengnums = ["two hundred thousand three hundred sixty", \
#  "one", "two", "five", "seventeen", "twenty one", "sixty six", "hundred two", "two hundred ten", "three hundred forty nine", \
#  "thousand seven", "ten thousand five hundred eighteen", "million", "hundred", "thousand", "ten thousand", "hundred thousand" \
#  ]
#for engnum in testengnums:
#    print stringtonum(engnum.split()), engnum

expstr = "thousand seven add ten thousand five hundred eighteen"
b = []
for w in expstr.split():
    if w in ["add", "plus"]:
        a = b
        b = []
        op = w
    elif w in ["minus"]:
        a = b
        b = []
        op = w
    elif w in ["multiple"]:
        a = b
        b = []
        op = w
    elif w in ["divide"]:
        a = b
        b = []
        op = w
    else:
        b.append(w)

print expstr
print stringtonum(a), stringtonum(b)
if op in ["add", "plus"]:
    print stringtonum(a) + stringtonum(b)
elif w in ["minus"]:
    print stringtonum(a) - stringtonum(b)
elif w in ["multiple"]:
    print stringtonum(a) * stringtonum(b)
elif w in ["divide"]:
    print stringtonum(a) / stringtonum(b)
