#
# Issue-11 Python solution to find longest connected 
# objects in ASCII text Maze. It is not clear if dialgonals 
# should be consider connected, but this code connects
# on diagonals.  -- EMarch May 31, 2013 -- 
# mazeinput W=Walls, @=Objects, else open air, LF=Next Line 
# Upper left corner of maze is X,y = 0,0.
#
# Sample run output: 
# ---------------------------------------------------
# ~>python issue11.py
# Objects=3 at x=4 y=1
# Objects=1 at x=8 y=1
# Objects=3 at x=6 y=2
# Objects=3 at x=7 y=3
# WWWWWWWWWW
# W   @W  @W
# W  @W @W W
# W @ W@ @ W
# W   @ @@ W
# WWWWWWWWWW
#
# Answer: Longest=3 at x=4, y=1
# ---------------------------------------------------
import string

mazeinput = """\
WWWWWWWWWW
W   @W  @W
W  @W @W W
W @ W@ @ W
W   @ @@ W
WWWWWWWWWW
"""

#
# Recursively visit neighbors and count longest 
# connected AT SIGNS and added x,y to Visited 
# list to prevent recursion overflow.  
#
def neighbors(x,y):
  global ObjCount, Maze, Visited
  if(x < 0 or x > xmax or y < 0 or y > ymax): 
      return 
  if((x,y) not in Visited and Maze[y][x] == '@'):
    Visited.append( (x,y) )
    ObjCount = ObjCount + 1
    # Each side 
    neighbors(x-1,y)
    neighbors(x+1,y)
    # Top three above 
    neighbors(x-1,y-1) # Diagonals
    neighbors(x,  y-1)
    neighbors(x+1,y-1) # Diagonals
    # Bottom three below
    neighbors(x-1,y+1) # Diagonals
    neighbors(x,  y+1)
    neighbors(x-1,y+1) # Diagonals
  return


Maze = mazeinput.split('\n')

ObjLongest = 0     # Longest found so far 
ObjX = ObjY = 0    # At this location
ObjCount = 0       # Runnig count of neighbors
Visited = []       # (x,y) visited list 

xmax = len(Maze[0])-1 
ymax = len(Maze)-1

for y in range(ymax):
  for x in range(xmax):
    ObjCount = 0
    neighbors(x,y)
    if(ObjCount > 0):
        print "Objects=%d at x=%d y=%d" % (ObjCount,x,y)
    if(ObjCount > ObjLongest):
      ObjLongest = ObjCount
      ObjX = x
      ObjY = y        
#
print mazeinput
if(ObjLongest > 0):
    print "Answer: Longest=%d at x=%d, y=%d" % (ObjLongest,ObjX,ObjY)





