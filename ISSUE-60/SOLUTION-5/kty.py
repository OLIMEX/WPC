#!/usr/bin/env python3
#-*- coding:utf-8 -*-
#
# 2014-07-06 by kantal59 
# License: LGPL
# OLIMEX WPC#60: PTC linearization
#			KTY81/110 is non linear resistor which increases it’s value with temperature. 
#			You can read the datasheet here: http://www.nxp.com/documents/data_sheet/KTY81_SER.pdf
# 			Make code which input KTY81/110 real number of resistance in ohms and output the temperature of the sensor.
#
#
# 			Resources: 
#			 	http://www.nxp.com/documents/data_sheet/KTY81_SER.pdf
#			 	http://www.nxp.com/documents/other/SC17_GENERAL_TEMP_1996_3.pdf
# 	

import sys

def mktbl_kty81_110():
	''' Creating table of (resistance,temperature) values.
		Formula used:	RT = Rref*( 1 + A*( T – Tref ) + B*( T – Tref )^2 – C*( T – Ti )^D )	where  C==0 if T < Ti 
		Sensor current: 1mA
		(It is easy to create a similar procedure for other KTY devices if the parameters are given.)
	'''
	Tref= 25
	Rref= 1000
	Ti= 100
	A= 7.874e-3
	B= 1.874e-5
	C= 3.42e-8 
	D= 3.7
	Trange= range( -56, 151)
	prec= 2	#  one unit is divided into 'prec' equal part

	tbl=[]	

	for t in Trange:
		for k in range(prec):
			T= t + k/prec
			if T >= Ti:
				tbl.append( ( Rref*( 1+A*(T-Tref)+B*(T-Tref)*(T-Tref)-C*pow(T-Ti, D) ), T ) )
			else:
				tbl.append( ( Rref*( 1+A*(T-Tref)+B*(T-Tref)*(T-Tref) ), T ) )

	return( tbl)				



def get_temperature( ohm, tbl):
	''' It returns the temperature value from the table "tbl" corresponding to resistance "ohm". 
		"tbl" has (resistance,temperature) values.
		It can be used for other KTY devices with different tables, too.
	'''
	if ohm < tbl[0][0]  or  ohm > tbl[-1][0] :	return( None)		# invalid input resistance value
	
	v= (0,tbl[0])	# (tbl index, (resistance,temperature) )
	
	for i,(r,t) in enumerate(tbl):
		if r > ohm:	break;				
		v= ( i,(r,t) )
		
	k,(r1,t1) = v;
	if ohm == r1:	# the given resistance is listed in the table
		return( t1)

	r2,t2 = tbl[k+1];
	return( t1+ (t2-t1)*(ohm-r1)/(r2-r1) )



TBL_kty81_110= mktbl_kty81_110()


# ------------ TEST ------------
if __name__ == '__main__':

	R=[ 100,490, 814.85, 1000,1002,1010,1012,1020,1028,1029,1040, 1300, 1700, 1900, 2200, 2300 ] # test data
	if len(sys.argv) < 2:
		print(" Usage: $ ./kty.py  resistance1 resistance2 ...\n  where the values are in Ohms")
	else:
		R=[]
		for i in range( 1, len(sys.argv)):
			R.append( float(sys.argv[i]))		


	print("KTY81_110:")
	#print("KTY81_250:")
	for r in R:
		t= get_temperature( r,TBL_kty81_110 )
		# t= get_temperature( r,TBL_kty81_250 )
		if t:	t= "{0:.2f} Celsius".format(t)
		print( " {0} Ohms\t{1}".format( r, t)) 	

			
