#!/usr/bin/env python

__author__ = 'theAdib'
__copyright__ = 'Copyright (c) 2014 Adib'
__license__ = 'New-style BSD'
__version__ = '0.1'

'''
Make Braille encoder which takes string and prints Braille equivalent 
on 3 lines with "*" for convex and "." for concave dots.
How do you print "helloworld"?

the current program outputs
*. *. *. *. *. .* *. *. *. ** 
** .* *. *. .* ** .* ** *. .* 
.. .. *. *. *. .* *. *. *. .. 
'''

'''
the braille map converts ascii characters into binary representation of braille dots
(tl)1-1, 2-2, (bl)3-4, (tr)4-8, 5-10h, (br)6-20h
see http://de.wikipedia.org/wiki/Brailleschrift
'''
brailledict = {}

def braille(c):
  if c in brailledict:
    return brailledict[c]
  return 0
  
def init_braille():
  global brailledict
  brailledict['h'] = 0x13
  brailledict['e'] = 0x11
  brailledict['l'] = 0x07
  brailledict['o'] = 0x15
  brailledict['w'] = 0x3a
  brailledict['r'] = 0x17
  brailledict['d'] = 0x19

def print_braille(str):
  '''
  print a ascii string in braille dots
  '''
  for [d1, d2] in [[1, 8], [2, 0x10],[4, 0x20]]:
    # print d1, d2
    line = ''
    
    for c in str:
      b = braille(c)
      # print c, ord(c), braille(c)
      if b & d1:
        line = line  + '*'
      else:
        line = line + '.'

      if b & d2:
        line = line  + '*'
      else:
        line = line + '.'
      line = line + ' '
    
    print line

init_braille()
print_braille('helloworld')

  

