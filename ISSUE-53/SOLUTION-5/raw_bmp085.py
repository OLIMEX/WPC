#!/usr/bin/env python
# -*- coding: utf-8 -*-

from time import sleep
import smbus
import sys

''' 
 2014-05-18 by kantal59
 License: LGPL
 OLIMEX WPC#53: Random Number Generator
			Make your own Random Number Generator.
		 
		 
 			Testing OLIMEX mod-bmp085 UEXT module as a hardware source for bit harvest to create a random number generator.
			The measured raw values (temperature, pressure) are not absolutly precise, maybe the least significant bits change 
			somewhat(??) randomly. The raw values will not be compensated with the calibration data. 
			
			Test platform: OLIMEX A10Lime Rev.A.; Debian Linux, smbus python module
			
			Usage: $ raw_bmp085.py  number_of_random_numbers_to_print
			
			Resource:
				https://www.olimex.com/Products/Modules/Sensors/MOD-BMP085/resources/MOD-BMP085+Olinuxino+Python.zip
				https://www.olimex.com/Products/Modules/Sensors/MOD-BMP085/resources/BMP085-DS000-05_Rev_1_2_15Oct2009.pdf
				http://www.daimi.au.dk/~mg/mamian/random-bits.pdf
'''
#----------- PARAMETERS to play with --------------
bus= 2			# i2c bus
address= 0x77	# slave address
ovs= 0			# bmp085 oversampling value
ttime= 0.005	# sec; for temperature
ptime= 0.005	#sec; for pressure
#----------------------
BUS = smbus.SMBus( bus)
#-------------------------------------------------


def get_values( ):	# read from the BMP085
	global BUS, address, ttime, ptime, ovs

	try:
        # temperature
		BUS.write_i2c_block_data( address, 0xF4, [0x2E])
		sleep( ttime)
		UT= BUS.read_i2c_block_data( address, 0xF6, 2)
            
		rtemp= UT[0] << 8 | UT[1]
            
	except Exception, ex:
		print( str(ex));		sys.exit(1)  
        
	try:
        # pressure
		BUS.write_i2c_block_data( address, 0xF4, [0x34+(ovs<<6)])
		sleep( ptime)
		UP= BUS.read_i2c_block_data( address, 0xF6, 3)
            
		rpress = (UP[0] << 16 | UP[1] << 8 | UP[0]) >> (8 - ovs)
            
	except Exception, ex:
		print( str(ex));		sys.exit(1)  

	return( rtemp,rpress)
	


def myrnd():	# returns a random(?) number between [0,1023]

	bitrslt=[]

	for i in range( 10):
		rt, rp = get_values()	
		rt, rp =  rt%2,  rp%2 
		bitrslt.append( '1' if (rt != rp)  else '0'  )

	return( int( ''.join(bitrslt), 2) )

#-------------------------------------------------

if __name__ == "__main__" :

	count= 10
	if len(sys.argv) >1:	
		count= int( sys.argv[1])
	else:
		print("Usage: $ raw_bmp085.py  number_of_random_numbers_to_print")
	

	for i in range( count):		print( myrnd())


