import math
import random
import sys

L=input('Please enter length of needle (less than stripe width please) ')
d=input('Please enter stripe width (more than length of needle please) ')
n=input('Please enter number of needles ')

if (L>d) or (L<=0) or (d<=0) or (n<=0):
    print 'could not calculate'
    sys.exit

k=0
for i in range(0, n):
    x=random.uniform(0.0, d/2.0000)
    y=math.sin(random.uniform(0.0, 3.14)) * (L/2.0000)
    if x<=y:
        k+=1

if k==0:
    print 'too less n'
    sys.exit

print (2.0000 * L * n)/(1.000 * d * k)
