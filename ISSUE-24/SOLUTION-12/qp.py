#!/usr/bin/python

import math


def main():
   N=-1
   while N<0:
     try:
       N=int(raw_input('Enter positive natural number N:'))
     except ValueError:
       print "Not a required number!"
       N=-1
   print "There is",p(N)," ways to express positive natural number",N,"as sum of positive natural numbers."


def p(n):
    if n==0: return 1   # p(0)=1
    factor=0
    k=1
    pn=0
    while (n-factor)>=0:
        factor=(3*k*k-k)/2
        sign=(-1)**(k-1)
        if k>0 : k=k*(-1)
        else: k=k*(-1)+1
        pn=pn+sign*p(n-factor)
    return pn

if __name__ == '__main__':
  main()

