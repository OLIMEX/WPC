#!/usr/bin/env python

__author__ = 'theAdib'
__copyright__ = 'Copyright (c) 2014 Adib'
__license__ = 'New-style BSD'
__version__ = '0.1'

import math

motordiameter = 2.0

def phi(s):
	"""calculate the phi related to arcdistance"""
	return (s * 360.0) / (2.0 * math.pi * motordiameter)

def phifrompos(delta):
	"""calculate the stepper movement from given position delta
	and return the change to the stepper angle"""
	return [-phi(delta[0]) + phi(delta[1]) , -phi(delta[0]) - phi(delta[1])]

def rotate(phi):
	"""rotate the stepper motors by given angles"""
	print(U"rotate motor 1 by {0}deg and motor 2 by {1}deg".format(phi[0], phi[1]))

positions = [[0.0, 0.0] ,[0.0, 10.0], [10.0, 0.0] , [10.0, 10.0] ]

print positions
for pos in positions:
	print("move carrige to next position: X:{0} and Y:{1}".format(pos[0], pos[1]))
	rotate(phifrompos(pos))
