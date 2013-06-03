from collections import defaultdict

# #http://stackoverflow.com/questions/9884057/two-dimensional-list-in-python
with open('./mazefile2.txt') as file:
     mazetab = [[item for item in line.strip()] for line in file]

# #making solution table
soltab = [[0 for i in j] for j in mazetab]

def listneighbour(j, i, t):
    r = []
    if t[j-1][i] > 0:
        r.append(t[j-1][i])
        
    #if t[j+1][i] > 0:
    #    r.append(t[j+1][i])

    if t[j][i-1] > 0:
        r.append(t[j][i-1])

    #if t[j][i+1] > 0:
    #    r.append(t[j][i+1])
    
    return r

def uniqll(ll):
    usedll = []
    rll =[]
    for li in ll:
        if li not in usedll:
            rll.append(li)
            usedll.append(li)
            
    return rll    
    
def intersecll(l2, l3): #union list of lists
    rll = [val for val in l2 if val in l3]
    return rll

def unionll(l2, l3):
    return uniqll(l2 + l3)
    
def addlonb(ll, l):
    il = l
    rll = [l]
    for lj in ll:
        if intersecll(il, lj):
            il = unionll(il, lj)
            rll.append(il)

        else:
            rll.append(lj)
            
    return rll

prevchar = 'W' # #previous reading item, assume W
obstracle = '@' # # @ = obstracle
groupid = 1 # #group id of contigous obstracle
d = defaultdict(int)
lonb = [] #list of neighborhood
# #main
for j in range(len(mazetab)):
    for i in range(len(mazetab[j])):
        charread = mazetab[j][i]
        if charread == obstracle: # #obstracle found
            l = listneighbour(j, i, soltab)
            if l:
                choosedgroupid = min(l)
                soltab[j][i] = choosedgroupid
                d[choosedgroupid] += 1
                #print lonb
                #print l
                lonb = addlonb(lonb, l)
                #print lonb
                #print "----"
                
            else:
                soltab[j][i] = groupid
                d[groupid] += 1
                
        else:
            if prevchar == obstracle:
                groupid += 1
            
        prevchar = charread        


#debug 
invd = [(value, key) for key, value in d.items()]
maxobs = max(invd)[0]

lonb = uniqll(lonb)

for li in lonb:
    dd = 0
    li2 = uniqll(li)
    for i in li2:
        dd += d[i]
        
    if dd > maxobs:
        maxobs = dd    

print maxobs
#debug 
#print lonb
#print d
#for j in range(len(mazetab)):
#    print mazetab[j]
#for j in range(len(soltab)):
#    print soltab[j]
#
#lll2 = [[1,3], [2,4]]
#lll3 = [6,3]
#print addlonb(lll2, lll3)
