#!/bin/python
# don't forget to chmod +x
# cat banana.txt | ./rlecmp.py | hexdump -C
# cat banana.txt | ./rlecmp.py > banana.rle
import sys
from itertools import groupby

for k, g in groupby(sys.stdin.read()):
    n = len(list(g))
    # be careful: integer in Python is arbitrary length
    while n > 255:
        sys.stdout.write(chr(255))
        sys.stdout.write(k)
        n -= 255
    if n > 0:
        sys.stdout.write(chr(n))
        sys.stdout.write(k)
    sys.stdout.flush()