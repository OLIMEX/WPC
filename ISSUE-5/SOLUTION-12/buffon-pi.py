# -*- coding: utf-8 -*-
"""
Created on Sun Apr 21 23:02:13 2013

@author: damu
"""
import random
import math

def simulate_one_throw(l,d):
    # Choose a random point between 2 lines separated by distance d
    # This will be the mid point of the needle
    pos = random.uniform(0, d) 
    # choose a angle of inclination of the needle
    theta = random.uniform(0, math.pi/2)
    # calculate the distance of needle's midpoint from the closest line
    x = min(pos, d-pos)
    #print pos, theta, x, ((l/2) * math.sin(theta))
    # return 1 if the needle crosses the line else 0
    return 1 if x <= (l/2) * math.sin(theta) else 0
    
random.seed(1)
l = 2
d = 3
N = 100000
total_crossings = 0
for i in range(0,N):
    total_crossings += simulate_one_throw(l,d)
    
P = (1.0 * total_crossings)/N
print "Probability : %f" %(P)
if l <= d:
    pi_approx = (2.0*l)/(P*d)
else:
    pi_approx = (2.0/P) * math.acos(d/l) + ((2.0 * l)/(P * d)) * (1 - math.sqrt(1 - (d/l)*(d/l)))
    
print "Approximation of PI: %s" % (pi_approx)