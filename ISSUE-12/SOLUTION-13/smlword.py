import string

def letteronly(w):
    s = ""
    for i in range(0, len(w)):
        if w[i] in string.lowercase:
            s += w[i]
        else:
            s +=' '
    
    return s
        
# #alica.txt obtained from http://fiction.eserver.org/novels/alice_in_wonderland.html
alice = (letteronly(open('alica.txt', 'r').read().lower())).split()

def findworddif(a, b): # # len(a) must be = len(b)
    differ = 0
    for i in range(0, len(a)):
        if a[i] != b[i]:
            differ += 1

    return differ

def findworddif2(a, b): # #len(a)>len(b)
    bi = 0
    ai = 0
    differ = 0
    while ai < len(a):
        if a[ai] == b[bi]:
            if bi < (len(b)-1):
                bi += 1
        
        else:
            differ += 1
            
        ai += 1
       
    return differ
        
        
# # main()

#print alice
# #suggest words ee, put, word, ever, aa
w = raw_input('Enter similar word to find ').lower()
smlw = []
print "finding '" + w + "'"
for l in alice:
    if (len(l) == len(w) and findworddif(l, w) == 1) or ((len(l) + 1) == len(w) and findworddif2(w, l) == 1) or (len(l) == (len(w) + 1) and findworddif2(l, w) == 1):
        #print l
        if l not in smlw: # #uniq words
            smlw.append(l)
            
print smlw            


