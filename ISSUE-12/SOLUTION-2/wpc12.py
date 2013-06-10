def change(a, b):
    changes = 0
    for x in xrange(len(a)):

        if a[x] <> b[x]:
            changes = changes + 1
    return changes

def inside(s, l):
    for x in xrange(len(s)):
        if s[:x] == l[:x] and s[x:] == l[x+1:]:
            return True
    return False

f = open('alice.txt')
a = f.read()

a = a.replace('\n', ' ')

L = a.split(' ')
while True:
    O = []
    w = raw_input('Word? ')
    lw = len(w)

    for l in L:
        ll = len(l)
        if ll == lw:
            if change(l, w) == 1 and l not in O:
                O.append(l)
        if ll + 1== lw:
            if inside(l, w) and l not in O:
                O.append(l)
        elif ll == lw + 1:
            if inside(w, l) and l not in O:
                O.append(l)

    print 'Similar words are:',
    for o in O:
        print o,
    print
    if w == 'qq':
        quit
            
        
