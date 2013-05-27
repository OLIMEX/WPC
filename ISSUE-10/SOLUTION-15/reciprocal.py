#! /usr/bin/env python3
# -*- coding: utf-8 -*-

''' 
 2013-05-26 by kantal59
 License: LGPL

 OLIMEX WPC#10:
    Let 0 < (a/b) < 1 where a and b are positive integers. Make program which enters the numbers a and b
    then represent a/b with as sum of numbers 1/n + 1/n2 + 1/n3… and prints the n numbers.
    
 Python3 required!
 The 'fractions' module is used. The result is more precise than one calculated by the reciprocal.c (see the testcase 5/7 ). 
'''

from math import ceil
from os import sys
from fractions import Fraction



def reciprocal( a,b, eps=1e-18):
    eps=abs(eps)
    v= Fraction(a,b)
    while v > eps :
        n= ceil(1/v)
        yield n
        v-= Fraction(1,n)



def main():

 if len(sys.argv)==3:
    a= int(sys.argv[1])
    b= int(sys.argv[2])
    
 if len(sys.argv)!=3 or a<=0 or b<=0 or a>= b :

    print("\nWrong input\nUsage: $> reciprocal.py a b\n- where a,b are positive integers and a<b\n")
    for t in [ (6,7), (3,4), (5,19), (8,11), (5,7), (3,5000) ] :
        print("- using test data a={0}, b={1} --> {2}".format(t[0],t[1], [ n for n in reciprocal(t[0],t[1])]) )
 else:        
    print(  [ n for n in reciprocal( a,b) ] )
    


main()
 


