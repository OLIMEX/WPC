#!/usr/bin/python

# Author: Mati
# Made for Olimex Programming Challange

# Problem description:
# This program reads coordinates of two points
# which define a line in two dimensional space and coordinates
# of the third point and calculates the distance between the line
# and the point

# Solution Description:
# To solve the problem it uses basic geometric properties. We are given points
# A and B which define line and point C whose distance we want to caluclate.
# First we calculate vector parallel to the line and then normalize it (vector n).
# Then we compute vector from the point C to one of the points on the line
# (e.g. A; so A-C) and calculate it's projected length on the line as a dot product
# between the vector and normalized vector n. Calculating product of
# this result and normalized vecor n we get the offset from the closest point
# to the point C which is located on the line to the point A.
# So the vector between point C and the closest point on the line is (A-C)-OFFSET.
# Now we only need to compute its length and we are done!



import re
import numpy as np

#read line from the input
string = raw_input("Enter coordinates of two points which define a line and coordinates of the third point :\n")

floats=re.findall(r'(\d+(\.\d*)?)',string)



if len(floats) !=6:
	print "wrong input. The program requires 6 integer or floating point arguments"
	
else:
	#beginning of vector
	A=np.array([ float( floats[0][0] ), float( floats[1][0] ) ])
	
	#end of vector
	B=np.array([ float( floats[2][0] ), float( floats[3][0] ) ])
	
	#point whose distance we compute
	C=np.array([ float( floats[4][0] ), float( floats[5][0] ) ])
	
	#vector parallel to the line
	l=(B-A)
	
	#normalized vector (unit length) parallel to the line. Can be also achieved using np.linalg.norm()
	n=l/np.sqrt(l.dot(l))
	
	#the shortest vector between the line and the point (perpendicular to the line)
	v=(A-C)-np.dot((A-C),n)*n
	
	#norm (length) of this vector
	distance=np.sqrt(v.dot(v))

	print distance
	
	
