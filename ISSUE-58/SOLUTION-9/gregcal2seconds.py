#!/usr/bin/env python3
#-*- coding:utf-8 -*-
''' 
 2014-06-22 by kantal59
 License: LGPL
 OLIMEX WPC#58: Date to Seconds converter
			Make code which enters Gregorian calendar date in format: Day/Month/Year and calculates 
			how many seconds passed since the beginning.

 			Leap seconds omitted ( http://en.wikipedia.org/wiki/Leap_seconds )
'''


import sys

 
#------------------------------------------------------
# Converting Gregorian calendar date to Julian day
# http://www.tondering.dk/claus/cal/julperiod.php
# year,month,day must be checked and corrected 
# by 'date_check() previously' !
#------------------------------------------------------ 
def GregorianCalendar_to_JDay( year,month,day):

	a= ( 14	- month) // 12
	y= year + 4800 - a
	m= month + 12*a -3
	jdn= day + (153*m+2)//5 + 365*y + y//4 - y//100 + y//400 - 32045
	return( jdn)


#-----------------
# Leap year check
#-----------------
def leap_year( year):
    if year%4 :      return(0)
    if year%100 :    return(1)
    if not year%400: return(1)
    return(0)


#-----------------------------------------------
# Check date format given as Gregorian date
# The input are strings, year,month,days. 
# The year string can contain 'bc', e.g.: bc3000-3-21
# The Julian day epoch is  bc4714-11-24 in the proleptic Gregorian calendar
#-----------------------------------------------
def date_check( sy,sm,sd):

	dom= [31,29,31,30,31,30,31,31,30,31,30,31]
	
	if sy.lower().startswith('bc'):
		try:
			sy= -(int( sy[2:]))
		except:
			return(None)
				
		if sy != 0:		sy+=1	# BC 1 --> -1 --> 0 astronomical year;  	BC 4713 --> -4712

	try:
		y,m,d = int(sy), int(sm), int(sd)
	except:
		return(None)	
	
	if y< -4800 or m<1 or m>12 or d<1 or d > dom[m-1] or ( m==2 and d==29 and not leap_year(y) ):		return(None)
	
	return(y,m,d)
	
	
#----------------------------------------
# Converting Julian day into seconds
#----------------------------------------	
def JDay_to_Seconds(JDN):
	return( JDN*86400)


#-------------------- 
#----- Testing ------
#--------------------

if __name__ == "__main__":

 dates= [ "bc4714-11-24", "bc753-1-1", "1582-10-15", "1582-10-04", "2000-01-01", "2014-06-22" ]
 
 usage= "\n Usage: $ ./gregcal2seconds.py  date1 date2 ...  \n where date is in [bc]year-month-day format in proleptic Gregorian calendar \n and the Julian Day Epoch is bc4714-11-24"  
 
 if len(sys.argv)==1: 
 	print( usage)
 else:
 	dates= [ sys.argv[i] for i in range(1,len(sys.argv)) ]



 ndates= []
 for i,dstr in enumerate( dates):
 
		d= dstr.split('-')
		if len(d) !=3:
			print( "\n Invalid date string: {0} . {1}\n".format( dstr,usage) ) 
			continue

		rslt= date_check( d[0],d[1],d[2] )
		if not rslt:
			print( "\n Invalid date string: {0} . {1}\n".format( dstr,usage) )
			continue

		y,m,d = rslt
		ndates.append( (dstr,y,m,d) )


 if ndates:		
 	print(" input --> interpretation: [ Julian day ]: seconds from Julian Day Epoch ( bc4714-11-24 )") 
 	for dstr, y,m,d in ndates: 
 		jd= GregorianCalendar_to_JDay( y,m,d)
 		print( " {0} --> {1}-{2:02d}-{3:02d} [{4:,}]:\t {5:,} seconds".format(dstr,y,m,d, jd, JDay_to_Seconds(jd) ) )
    
 print('')



