Hi,

here is my solution:

<code>

  1 #! /usr/bin/env python3.2
  2 # challenge20120324.py
  3 
  4 import math
  5 
  6 def calculate_distance(a, b, c):
  7     '''
  8         calculates the distance x between
  9         the line defined by a[x, y] and b[x, y] 
 10         and the point c[x, y]
 11     '''
 12     for n, m in enumerate(a):
 13         b[n] = b[n] - m
 14         c[n] = c[n] - m
 15     x = (c[0]*b[1]-b[0]*c[1])/math.hypot(b[0], b[1])
 16     return abs(x)                                           

</code>

Just moving A into the origin and then rotate B to the y-axis, so the
distance is the x value of C.

Best wishes,
Johannes