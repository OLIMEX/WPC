#!/usr/bin/env python
# Iterative search for valid integer arguments of the range built-in.
start, stop = 0, 1
while sum(range(start, stop)) != 9808:
    while sum(range(start, stop)) < 9808:
        stop += 1
    while sum(range(start, stop)) > 9808:
        start += 1
print("%i = sum(%s)" % (sum(range(start, stop)), range(start, stop)))
