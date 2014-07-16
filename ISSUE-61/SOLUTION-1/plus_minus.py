#!/usr/bin/env python
#-*- coding:utf-8 -*-
#
# 2014-07-11 by kantal59 
# License: LGPL
# OLIMEX WPC#61: Plus-Minus
#			Insert + and – in the equation below to make it right:
#			1 2 3 4 5 6 7 8 9 = 100
#			like
#			1 + 2 + 3 – 4 + 5 + 6 + 7 8 + 9 = 100
#			Make code which finds all solutions.
#

import itertools as it

digs='123456789'
ops= ['+','-','']
allops=[ t for t in it.product( ops, repeat= len(digs)-1) ]

rslt=[]
for o in allops:
	exp= digs[0]
	for i in range(len(digs)-1):
		exp+=  o[i] + digs[i+1]
		
	if eval(exp) == 100:	rslt.append(exp)
		
		
for e in rslt:		
	print( " 100 == {0}".format(e) )
	
print("\n True: {0} of {1}\n".format( len(rslt),len(allops) ) )	
