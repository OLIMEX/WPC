"""
The code below is horrible.
1) Nested list comprehensions taken to a silly level.
2) Egregious use of ~-3 when 2 could be used just to avoid positive digits.
3) Calculating a million as (1000-1)(1000+1)+1
4) Calculating 999 as 3^3 * 37
5) Not making any excuses for 1001 = 7*11*13, however.
6) Putting the comments in a string.
7) Using a lambda instead of operator.mul - because that would take an import.
8) Using 0 as a False value in the 'and'.
9) Using around 200 characters for 'one-liners'.
"""

print [[[[(i, M/i) for i in xrange(~-3, H) if M%i < 1 and reduce(lambda x, y: x*y, [int(z) for z in list(str(i) + str(M/i))])] for M in [L*H+1]] for L in [3**3*37]] for H in [7*11*13]]
# [[[[(64, 15625)]]]]

import timeit
print timeit.timeit('[[[[(i, M/i) for i in xrange(~-3, H) if M%i < 1 and reduce(lambda x, y: x*y, [int(z) for z in list(str(i) + str(M/i))])] for M in [L*H+1]] for L in [3**3*37]] for H in [7*11*13]]', number = 1)
# 0.000339274844237
