#!/usr/bin/env python
#-*- coding:utf-8 -*-
#
# 2014-06-27 by kantal59 
# License: LGPL
# OLIMEX WPC#59: Big – Little Endians
# 			Make code which detects on what machine is ran – with Big or Little Endian. 
# 			Can you do it in other language than C?

# I. The simple way
import sys
print( sys.byteorder)


# II: A more complicated way
import struct
s= struct.pack("=H",0x8000)	# '=': cpu native byte order but "standard" size; 	'H': unsigned short with 2 bytes (standard size)
if s[0]== '\00':
	print("Little endian")
else:
	print("Big endian")	

