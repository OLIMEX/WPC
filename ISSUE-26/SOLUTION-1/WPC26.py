#!/usr/bin/env python

testdata = [
	# input data for squares:
	[(0,0),(0,1),(1,1),(1,0)],   # normal square
	[(0,0),(2,1),(3,-1),(1,-2)], # not aligned square
	[(0,0),(1,1),(0,1),(1,0)],   # different order of the points
	# input data for non-squares:
	[(0,0),(0,2),(3,2),(3,0)],   # rectangle
	[(0,0),(3,4),(8,4),(5,0)],   # rhombus
	[(0,0),(0,0),(1,1),(0,0)],   # three points are same
	[(0,0),(0,0),(1,0),(0,1)],   # two points are same
]

# Returns the square of the distance between two points
def distancesq(x, y):
	vector = (x[0]-y[0], x[1]-y[1])
	return vector[0]**2 + vector[1]**2

# Checks if 4 points make a square
# This calculates the distance between all points. There have to be
# two different distances on a square: the diagonal and the side.
# We also check that the points are unique, if points are repeated it's
# not a valid square
def is_square(p):
	distances = [distancesq(x, y) for x in p for y in p if x != y]
	return len(set(distances)) == 2 and len(set(p)) == 4

for i in testdata:
	print("{0} {1} square".format(i, is_square(i) and "is a" or "is not a"))