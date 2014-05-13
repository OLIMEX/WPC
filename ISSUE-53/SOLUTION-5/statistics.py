#!/usr/bin/env python
#-*- coding:utf-8 -*-
''' 
 2014-05-18 by kantal59
 License: LGPL
 utility for OLIMEX WPC#53
'''

import sys
import raw_bmp085 as rbmp


CNT= 10
if len(sys.argv) == 2:	
	CNT= int( sys.argv[1])
else:
	print(" Usage: $ statistics.py 	[number_of_read]")

print( "\nMOD-BMP085 lowest bit statistics:\n bus: {0}, addr: {1}, ovs: {2}, temp. sleep time: {3}	\
			\n press. sleep time: {4}\n COUNT: {5}\n".format( rbmp.bus, rbmp.address, rbmp.ovs, rbmp.ttime, rbmp.ptime, CNT) )
			
tcount=0
pcount=0
diff=0

for i in range( CNT):
	
	rt, rp = rbmp.get_values()	
	rt, rp =  rt%2,  rp%2 
	if rt:	tcount+= 1
	if rp:  pcount+= 1
	if rt != rp:		diff+= 1


print( " temp. odd: {0}\n press. odd: {1}\n temp. and press. have different parity: {2}\n".format(tcount,pcount,diff) )

 
