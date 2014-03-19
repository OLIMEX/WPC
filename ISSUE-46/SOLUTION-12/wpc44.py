#!/usr/bin/env python

__author__ = 'Adib with usefull input and review from Andre'
__copyright__ = 'Copyright (c) 2014 Adib'
__license__ = 'New-style BSD'
__version__ = '0.1'

print "calculation of matching arrow positions in a 12 hours interval"

'''
the output should look like this:
calculation of matching arrow positions in a 12 hours interval
1. match after 66 min, at  1:06
2. match after 131 min, at  2:11
3. match after 197 min, at  3:17
4. match after 262 min, at  4:22
5. match after 328 min, at  5:28
6. match after 393 min, at  6:33
7. match after 459 min, at  7:39
8. match after 524 min, at  8:44
9. match after 590 min, at  9:50
10. match after 655 min, at 10:55
11. match after 720 min, at  0:00
'''

lastminpos = 0.0
lasthourpos = 0.0
matches = 0

for i in range(1, 12 * 60 + 1):
    newminpos = (i * 1.0) % 60
    newhourpos = (i / 12.0) % 60

    if (lastminpos < lasthourpos) and (newminpos >= newhourpos):
        matches += 1
        print "{3}. match after {0} min, at {1:2d}:{2:02d}".format(i, int(newhourpos / 5), int(newminpos), matches)

    lastminpos = newminpos
    lasthourpos = newhourpos
