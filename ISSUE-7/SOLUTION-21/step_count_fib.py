#Problem
#Cat can jump one or two steps on stairs, make code which calculate how many 
#different ways the cat can climb from bottom to top of N-size stairs.

#!/usr/bin/evn python
import os
os.system('clear')

fib = []
i, a , b = 0, 0, 1

n = input("How namy steps are there? ")


while i < n:
    a , b = b , a+b
    i += 1
    fib = fib + [b]    

print "In a stair with "+str(n)+" steps the cat has "+str(fib[-1])+" different ways of going up."
