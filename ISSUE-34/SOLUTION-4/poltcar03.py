#!/usr/bin/python
import numpy as np
from math import ceil, floor 

deg = np.arange(-180.0, 185.0, 5)
theta = (np.pi/180.0) * deg # in radian

#declare and initialize grid
gridxy = [[0 for i in range(141)] for j in range(141)]
for i in range(70, 100): 
    gridxy[80][i] = 6
    gridxy[81][i] = 7
    gridxy[82][i] = 6

#converts to cartesian (x, y)
def xygrid(x, y):
    if -70 <= x and x <= 70 and -70 <= y and y <= 70:
        return gridxy[x + 70][y + 70]
    else:
        return 0
   
def toradial(th, rpov):
    for r in range(rpov):
        x1 = int(ceil(r * np.cos(th)))
        x2 = int(floor(r * np.cos(th)))
        y1 = int(ceil(r * np.sin(th)))
        y2 = int(floor(r * np.sin(th)))
        xy = (xygrid(x1, y1) + xygrid(x1, y2) + xygrid(x2, y1) + xygrid(x2, y2))/4
        yield xygrid(int(round(r * np.cos(th))), int(round(r * np.sin(th))))

#rotating
for thpov in theta:
    povline = toradial(thpov, 100)
    b = []
    #b.append(thpov) #add radian if need
    for a in povline:
        b.append(a)
    print b    
