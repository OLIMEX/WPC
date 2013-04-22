# ---buffon.py --- Sebastian Plamauer ---
# This program calculates Pi using the solution of Buffons needle problem.

import random
import math

#Output Info
print 'This program calculates Pi using the solution of Buffons needle problem. You will have to enter the length of the needle, the width of the stripes and the number of throws. The length unit of the given values is not relevant, you just have to use the same unit for both. The result gets more accurate if enter a higher number of throws, but the time the program takes increases accordingly. 1.000.000 throws will get you a good result in short time.'

#Input
l = float(raw_input('Enter the needles lenght:'))
t = float(raw_input('Enter the stripes width:'))
n = int(raw_input('Enter the number of needles to be thrown:'))

#Generate random results of throws
i=0
angle = [0]
x = [0]
while i < n:
    angle.append(random.uniform(0, 359))
    x.append(random.uniform(0, t/2))
    i = i+1
del angle[0]
del x[0]

#Calculates y-value for comparison
y = [0]
for value in angle:
    y.append(l/2 * math.sin(value))
del y[0]

#Compares x and y to count how often the needle crossed a line
i = 0
h = 0
while i < n:
    if x[i] <= abs(y[i]):
            h = h + 1
    i = i + 1

#Calculate Pi
if l <= t:
    Pi = (2*l*n) / (t*h)
else:
    par = math.sqrt(l**2 - t**2) + t*math.asin(t/l)
    Pi = (2*n)/(t*(h-n)) * (l-par)

#Output
print 'Pi =', Pi
