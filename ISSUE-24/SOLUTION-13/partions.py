#!/usr/bin/env python3
#-*- coding:utf-8 -*-

'''
 2013-09-15 by kantal59
 License: LGPL
 OLIMEX WPC#24: Combinatorics - Integer Partitioning
            Write code which calculate the number of ways you can express positive natural number N as sum of positive natural numbers.
            For N=1 we have 1 way;
            for N=3 we have 3 ways: 1+1+1, 1+2, 3;
            etc.   
            
  It is a very slow prototype only.                       
'''

import sys

def gpenta( k):
    ''' Generalized the k-th pentagonal number (counting from 0)
        http://en.wikipedia.org/wiki/Pentagonal_number 
        k>=0 integer
    '''
    m= k//2;
    if not k%2: return( m*(3*m+1)//2)   # forcing integer divison for speed
    m+=1; 
    return( m*(3*m-1)//2)             
   
    

def partition( n):
    ''' Integer partitioning
        http://en.wikipedia.org/wiki/Partition_(number_theory)
        n: integer
    '''
    if n==0 or n==1: return(1)
    if n<0: return(0)
    parts= 0
    pentaidx= 1
    m= n-1      # m= n-gpenta(0)
    sign= 1
    while m>=0:
            parts+= sign*partition(m); 
            pentaidx+=1;    
            parts+= sign*partition( n-gpenta( pentaidx) ); 
            
            sign*=-1;   pentaidx+=1;    m= n-gpenta( pentaidx)
            
    return(parts)            
            


if __name__ == "__main__":

    if len(sys.argv)==2:
        N= int(sys.argv[1])
    else:    
        print( "\nUsage: $partions.py  integer")
        N=20
        
# check: http://oeis.org/A000041
print( "\nThe number of partitions of {0}: {1}\n".format( N, partition(N)) )        




    
