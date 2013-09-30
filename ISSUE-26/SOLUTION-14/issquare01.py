class coor(object):
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __str__(self):
        return "(%s, %s)" % (self.x, self.y)
    
    def __eq__(self, othr):
        return (self.x == othr.x) and (self.y == othr.y)

    def __sub__(self, othr):
        return coor(self.x - othr.x, self.y - othr.y)

#http://nrich.maths.org/2667/solution
#http://nrich.maths.org/2667
def remakedist(s1):
    return list([s1[1] - s1[0], s1[2] - s1[1], s1[3] - s1[2], s1[0] - s1[3]])

def checkifsquare(L1):
    return (L1[0].x == L1[1].y == (-L1[2].x) == (-L1[3].y) \
        and L1[0].y == (-L1[1].x) == (-L1[2].y) == L1[3].x) \
        or (L1[0].x == (-L1[1].y) == (-L1[2].x) == L1[3].y \
        and L1[0].y == L1[1].x == (-L1[2].y) == (-L1[3].x)) 

def havesamepoint(s1):
    return s1[0] == s1[1] or s1[1] == s1[2] or s1[2] == s1[3] \
     or s1[3] == s1[0] or s1[0] == s1[2] or s1[1] == s1[3]

#input four points
a = coor(4, 20)    
b = coor(21, 19)    
c = coor(20, 2)
d = coor(3, 3)

#main function
s1 = [a, b, c, d]
if havesamepoint(s1):
    print "Two or more coordinates are the same position"
    exit()
    
#create all possible (cyclic) sequences of those four points  
lsq1 = [s1 , [a, b, d, c], [a, d, b, c], [a, d, c, b]]
issquare = False
for sq1 in lsq1:
    issquare = checkifsquare(remakedist(sq1))
    if issquare:
        break
#print result about square of those four points. It is true or false.
print issquare
    