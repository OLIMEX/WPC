#!/usr/bin/env python3
#-*- coding:utf-8 -*-
''' 
 2014-10-03 by kantal59
 License: GPL
 OLIMEX WPC#67: Missing pages in book
 		There is a book and a number of consecutive pages are missing from this book. All we know is that the sum of the page numbers 
 		of these pages is 9808. Make code which calculates which are the missing pages and displays the result.

 		Let 1,2,3, ... k, k+1, k+2, ... k+t, ... the pages, where k>=0, t>=1 whole numbers and  the missing pages are from (k+1) to (k+t).
 		(1) So the sum of the page numbers of missing pages is 	t*k + t*(t+1)/2 = 9808.
 		(2) It's clear that the limit of k is 9807 and then t=1 and the the only missing page is the 9808th one.
 		From (1):	t1= (-1-2*k + sqrt( (1+2*k)^2+8*9808 ) )/2
 				 	t2= (-1-2*k - sqrt( (1+2*k)^2+8*9808 ) )/2
		t2 < 0, so it can't be a solution for the problem;
		t1 must be a whole number, hence the discriminant must be a square number, and the numerator must be divisible by 2. The latter
		is clear. We try all values of 'k' up to the the limit to get a square number.
		 				 	
'''

from math import sqrt 

 
def calc(k):

 d= (1+2*k)*(1+2*k)+8*9808	# discriminant
 rt= int(sqrt(d))
 
 if rt*rt == d :
 	t= (-1-2*k + rt )/2
 	print(" Missing pages from {} to {} ".format( k+1, int(k+t)) )
 


print() 	
for k in range(9808):	 # see (2)
	calc(k)
print()


