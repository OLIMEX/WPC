#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Sun May  5 11:13:03 2013

@author: damu
"""

# http://olimex.wordpress.com/2013/05/03/weekend-programming-challenge-issue-7/
# Cat can jump one or two steps on stairs, make code which calculate how 
# many different ways the cat can climb from bottom to top of N-size stairs.

import sys

cache = {}

def cat_walk(n):
    if cache.has_key(n):
        return cache[n]
    if n < 0:
        return 0
    if n == 0 or n == 1:
        return 1
    
    cache[n] = cat_walk(n-1) + cat_walk(n-2)
    return cache[n]

# Usage: cat_walk.py n1 n2 n3 n4

for arg in sys.argv:
    if arg.isdigit():
        n=int(arg)
        print "Total ways for %d steps: %d" % (n, cat_walk(n))