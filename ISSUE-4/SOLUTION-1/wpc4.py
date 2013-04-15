f = open('alice.txt')
a = f.read()
a = str.lower(a)

s = set()
l = 0

m = 0
b = 0
w = ''
for i, c in enumerate(a):
    if c >= 'a' and c <= 'z':
        s.add(c)
        l = l + 1
    else:
        if m < l and l == len(s):
            m = l
            b = i-l
            w = a[b:i]
            print m, b, i, w
        s = set()
        l = 0
            
        
        


