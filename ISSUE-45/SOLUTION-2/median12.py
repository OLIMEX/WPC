from collections import deque
from bisect import bisect_left, insort
from blist import blist
# git clone https://github.com/DanielStutzbach/blist
# python setup.py install

# Thanks http://code.activestate.com/recipes/576930-efficient-running-median-using-an-indexable-skipli/#c3
# Unfortunately http://legacy.python.org/dev/peps/pep-3128/
class RunningMedian:

    def __init__(self, iterable):
        self.q = q = deque(iterable)
        self.l = l = blist(q)
        l.sort() 
        self.mididx = (len(q) - 1) // 2

    def update(self, new_elem, check_invariants=False):
        q, l = self.q, self.l
        old_elem = q.popleft()
        q.append(new_elem)
        del l[bisect_left(l, old_elem)] 
        insort(l, new_elem)

        if check_invariants:
            assert l == sorted(q)

        return l[self.mididx]
    
    def __str__(self):
        return str(self.l[self.mididx])

    def __int__(self):
        return self.l[self.mididx]

testcode1 = """
a = [1, 4, 3, 7, 5]
median2 = RunningMedian(a)
print median2
print median2.l
median2.update(6)
print median2.l
median2.update(2)
print median2.l
print median2
"""

import struct

filerecordformat = ">BBBBHHHHHHB"
recsize = struct.calcsize(filerecordformat)
windowsize = 11 #you can change this windowsize for calculation median
fp = open("eegbin.dat", "r")
chunk = fp.read(recsize)
#ch1 in (...)[4], ch2 in [5] ... ch6
ch = 4
medianwindow = [(struct.unpack(filerecordformat, chunk)[ch]) for i in range((windowsize%2) + windowsize//2)]
for i in range(windowsize // 2):
    chunk = fp.read(recsize)
    medianwindow.append(struct.unpack(filerecordformat, chunk)[ch])
    
medianch = RunningMedian(medianwindow)
medianfiltered = [int(medianch)]
for chunk in iter(lambda: fp.read(recsize), ''):
    #print hex(ord(chunk[1]))
    #print struct.unpack(filerecordformat, chunk)[4]
    chread = struct.unpack(filerecordformat, chunk)[ch]
    medianch.update(chread)
    medianfiltered.append(int(medianch))
fp.close()
for i in range(windowsize // 2):
    medianch.update(chread)
    #print medianch.l
    medianfiltered.append(int(medianch))
print medianfiltered