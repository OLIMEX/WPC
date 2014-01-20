#!/usr/bin/env python3
#-*- coding:utf-8 -*-

''' 
 2014-01-19 by kantal59
 License: LGPL
 OLIMEX WPC#40: Number approximation
        Any positive integer number can be presented as 1 and several operations *3 and /2 discarding 
        the result after the decimal point when dividing. For instance:
                         4 = 1 *3 *3 /2
                        12 = 1 *3 *3 /2 *3
        Make code which enters positive integer N then present it with 1 *3 /2 equation.  
        
        Brute force applied. ( https://en.wikipedia.org/wiki/Collatz_conjecture )
'''
import itertools as it
import sys


def approximate( N, maxlength):
    
    for lth in range(1,maxlength):  # the first 1 not counted
            
        tries= it.product( [3,2], repeat= lth)
        for fact in tries:
            if check( fact)== N: return( list(fact) )
            
    return([])
 
 
 
def check( fl): # fl: sequences of 2,3; it must not contain the first 1!
    m=1
    for i in range(len(fl)):
        if fl[i]==3: 
            m*= 3
        else:
            m//=2    
    return(m)
    


#-------------------------
def display(N,L,factors):

    print( "\nN= {0}\nMax number of factors= {1}".format( N,L ) )
    
    if factors:
        ch=1
        if factors[-1]!=1: 
            ch= check( factors)
            factors.insert(0,1)
            
        print( "Factors found= {0}\nResult= {1}\nCheck= {2}".format( len(factors), factors, ch) )
        print( "{0}=1".format(N), end='')
        for  i in range(1, len(factors)):
            op='*' if factors[i]==3 else '//'
            print("{0}{1}".format( op,factors[i]),end='')
        print("\n")    
    else:
        print("Result: not found")   
        

#-------------------------

# INPUT
if len(sys.argv) != 3:
    print("\nUsage: $approximate_3_2   positive_integer  max_number_of_factors")
    print(" e.g.: $approximate_3_2   12 10\n")
else:    
    N= int(sys.argv[1])
    L= int(sys.argv[2])
    if N== 1:
        factors=[1]
    else:    # CALCULATION
        factors= approximate( N, L )
            
    #OUTPUT
    display(N,L,factors)
    
    
