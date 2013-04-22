#!/usr/bin/python
"""
Calculates pi using the "buffon's needle problem" method
http://en.wikipedia.org/wiki/Buffon's_needle#Estimating_.CF.80

By Grillo
"""

import random
import sys
import math

def needle_sym(n_size, l_dist):
    theta = random.random()*math.pi/2
    x = random.random() * l_dist/2
    return x < (n_size/2) * math.sin(theta)

try:
    [n,l,t] = [ x for x in sys.stdin.readline().split()]
    n = int(n)
    l = float(l)
    t = float(t)
except:
    print "Wrong input"
    print "Use the STDIN to enter \"the number of iterations\", "
    print "\"the length of the needle\" and \"the separation between "
    print "the lines\" separated by spaces"
    
    exit(0)

h = 0
for i in range(n):
    if needle_sym(l,t):
        h = h+1

if(l<t):        
    pi = 2*l*n/float(h*t)
else:
    pi = 2*(n/float(h))*(math.acos(t/float(l)) + 
           (l/float(t))*(1-math.sqrt(1-(t/float(l))**2)))

print pi
