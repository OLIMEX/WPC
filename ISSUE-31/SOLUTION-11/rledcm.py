#!/bin/python
# don't forget to chmod +x
# cat banana.rle | ./rledcm.py 
# cat banana.txt | ./rlecmp.py | ./rledcm.py | hexdump -C
import sys

while True:
    n = sys.stdin.read(1)
    c = sys.stdin.read(1)
    if n and c:
        sys.stdout.write(c * ord(n))
    else:
        break