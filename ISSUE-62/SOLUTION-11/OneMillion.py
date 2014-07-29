#!/usr/bin/python
from math import sqrt
k=1000000
for x in range(1,int(sqrt(k))):
  if k/float(x)==k/x:
      if (str(x)+str(k/x)).find('0')==-1:
         print 'The numbers are '+str(x)+' , '+str(k/x)
