#! /usr/bin/env python
# -*- coding: utf-8 -*-

'''
 2013-05-03 by kantal59
 License: LGPL
 OLIMEX WPC#7:
    Cat can jump one or two steps on stairs, make code which calculate how many different ways the cat 
    can climb from bottom to top of N-size stairs.
    
 If the number of steps greater than 1, the last step could be reached by a 1-step jump or 2-steps jump from below.
 Let the number of different ways to reach the top of the n-size stairs is Fn. 
 It consists of two parts, F_n= S1_n + S2_n, where
    S1_n is the number of the ways with 1-step jump at the top, and 
    S2_n is the number of the ways with 2-steps jump at the top.
 Adding one more step, you can calculate the number of ways for (n+1)-size stairs from F_n:
    Each of the previous ways can be lengthened by a 1-step jump, name them S1_n+1= F_n,           (***)
    and in each of the previous S1_n ways, the last 1-step jump can be changed for a 2-steps jump, S2_n+1= S1_n.
 So, F_n+1 = S1_n+1 + S2_n+1 = F_n + S1_n
 and similarly:
     F_n+2 = F_n+1 + S1_n+1, where the last term is F_n after (***), 
     that is F_n+2 = F_n+1 + F_n .    
'''

from os import sys
from math import sqrt, pow

    
'''
 Fibonacci number calculation with iteration.
''' 
def value( N):
    if N<=0:
        return(0)
    a=1; b=2        
    while N>1:
        t=a; a=b; b=a+t; N-=1
    return( a)                        
  
'''
 Fibonacci number calculation with closed form.
 For large N, it gives wrong value because of the rounding errors.
'''
def value2( N):  
    if N<=0:
        return(0)
    s5=sqrt(5)
    return( int( (pow( 0.5+s5/2, N+1) - pow( 0.5-s5/2, N+1))/s5 ) )            


'''
 It constructs the ways.
'''
def construct( N):
    if N<=0:
        return([])
    S1=[[1]]; S2=[]
    while N>1:
        t1=S1[:]
        del S1[:]        
        for w in t1:
            S1.append( w[:]+[1] )
        for w in S2:
            S1.append( w[:]+[1] )
        del S2[:]
        for w in t1:
            w[-1]= 2
            S2.append( w)
        N-=1
        
    return( S1+S2)
    
    
'''
 Testing 
'''    
def main():   
    if len(sys.argv)!=2 :
        print( "Usage: $> catstairs.py size_of_steps")
    else:
        n= int(sys.argv[1])
        print( " Stairs size: {0}\n Different ways: {1}".format( n, value( n)) )
        
        if n<=10: # constructing the ways for small numbers
            for w in construct( n):
                print(w)


main()        


