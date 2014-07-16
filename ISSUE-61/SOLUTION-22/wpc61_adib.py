#!/usr/bin/env python

__author__ = 'theAdib'
__copyright__ = 'Copyright (c) 2014 Adib'
__license__ = 'New-style BSD'
__version__ = '0.1'

'''
Problem:
insert + and - in the equation below to make it right
1 2 3 4 5 6 7 8 9 = 100
like
1 + 2 + 3 - 4 + 5 + 6 + 7 8 + 9 = 100
make code which  finds all solutions.
'''

'''
the current program creates following output:
+1+2+3-4+5+6+78+9  =  100
+1+2+34-5+67-8+9  =  100
+1+23-4+5+6+78-9  =  100
+1+23-4+56+7+8+9  =  100
+12+3+4+5-6-7+89  =  100
+12+3-4+5+67+8+9  =  100
+12-3-4+5-6+7+89  =  100
+123+4-5+67-89  =  100
+123+45-67+8-9  =  100
+123-4-5-6-7+8-9  =  100
+123-45-67+89  =  100
-1+2-3+4+5+6+78+9  =  100
number of tested variations 13122

'''

def vectors(level, base):
  '''
  create the vector of all possible variants
  '''
  if level >= 8:
    return base
  
  ext = []  
  for v in base:
    # if level > 0:
    ext.append(v + '+')
      
    ext.append(v + '-')
    ext.append(v + ' ')
  
  return vectors(level + 1, ext)

def merge(vec):
  '''
  merge the calculation to the numbers
  '''
  zipped = zip(vec, ['1', '2', '3', '4','5', '6', '7', '8', '9'])
  res = ''
  for z in zipped:
    res += z[0] + z[1]
  res = res.replace(' ', '')
    
  return res

def evaluate(str):
  tok = []
  # print "evaluate"
  while str[1:].find('+') >= 0 or str[1:].find('-') >= 0:
    p = str[1:].find('+')
    m = str[1:].find('-')
    # print str, p, m
    if (p < m or m < 0) and (p >= 0):
      tok.append(str[:p+1])
      str = str[p+1:]
    else:
      tok.append(str[:m+1])
      str = str[m+1:]
  tok.append(str)
  # print tok
  val = 0
  for t in tok:
    # print t
    val += int(t)
  
  return val
  
  
sol = vectors(0, ['+', '-'])


for s in sol:
  line = merge(s)
  # print line
  if evaluate(line) == 100:
    print line, ' = ', evaluate(line)
  
  
print 'number of tested variations ' + str(len(sol))

