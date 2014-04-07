#!/usr/bin/env python
#-*- coding:utf-8 -*-
''' 
 2014-04-06 by kantal59
 License: LGPL
 OLIMEX WPC#49: Easter date calculator
            Make code which enters Year and then calculates the Easter date in both Western and Orthodox style and display it.
                        
'''
import sys

#----------------------------------------------------------
# Easter in Julian Calendar
# Algorithm: http://www.tondering.dk/claus/cal/easter.php
#----------------------------------------------------------
def JulianCalendar_Easter( year):

 if year<33: return(None,None)
 
 G= year % 19
 I= (19*G + 15) % 30
 J= (year + year//4 + I ) % 7
 
 L= I - J
 EM= 3 + (L + 40)//44
 ED= L + 28 - 31*(EM//4)
 
 return(EM,ED)

#----------------------------------------------------------
# Western Easter in Gregorian Calendar
# Algorithm: http://www.tondering.dk/claus/cal/easter.php
#----------------------------------------------------------
def GregorianCalendar_Easter( year):

 if year <1583: return(None,None)
 
 G= year % 19
 C= year // 100
 H= ( C - C//4 - (8*C + 13)//25 + 19*G + 15 ) % 30
 I= H - H//28 * ( 1 - 29//(H+1) * (21-G)//11 )
 J= ( year + year//4 + I + 2 - C + C//4 ) % 7
 
 L= I - J
 EM= 3 + (L + 40)//44
 ED= L + 28 - 31*(EM//4)
 
 return(EM,ED)
 
#------------------------------------------------ 
# Converting Julian calendar date to Julian day 
#  http://en.wikipedia.org/wiki/Julian_day
#------------------------------------------------
def JCalendarDate_to_JDay( year,month,day):

 a= (14-month)//12
 y= year + 4800 - a
 m= month + 12*a - 3
 JDN= day + (153*m + 2)//5 + 365*y + y//4 - 32083
 return( JDN)   

#--------------------------------------------------
# Converting Julian day to Gregorian calendar date 
#  http://en.wikipedia.org/wiki/Julian_day 
#--------------------------------------------------
def JDay_to_GregorianCalendar( JDN):

 y= 4716;   v= 3;   j= 1401;    u= 5;   m= 2;   s= 153;     n=12;   w= 2;   r= 4;   B= 274277;  p= 1461;    C= -38;   
 
 f= JDN + j + ( ((4*JDN + B)//146097) * 3) // 4 + C
 e= r * f + v
 g= ( e % p ) // r
 h= u * g + w
 D= ( h % s ) // u + 1
 M= (h//s+m) % n + 1
 Y= e // p - y + (n + m -M) // n
 
 return(Y,M,D)
 
 
#--------------------------------------- 
# Orthodox Easter in Gregorian Calendar
#---------------------------------------
def OrthodoxCalendar_Easter( year):

 if year<1583:  return (None,None)
 
 jm, jd= JulianCalendar_Easter(year)
 if jm==None:   return (None,None)
 
 JDN= JCalendarDate_to_JDay( year,jm,jd)
 oy,om,od= JDay_to_GregorianCalendar( JDN)
 return( om,od)


#-------------------- 
#----- Testing ------
#--------------------

if __name__ == "__main__":

 years= [ 30,33,1000, 1582, 1583, 1700, 2014, 2015, 2016, 2059, 2100 ]
 
 
 if len(sys.argv)==1:
    print("\nUsage: $ ./easter_date.py  year1 year2 ... \n" )
 else:
    years=[]
    for i in range(1,len(sys.argv)):      
        try:
            years.append( int( sys.argv[i]) )
        except ValueError:
            pass
     
 print('\n Easter date in Gregorian/Julian/Orthodox calendars (month/day)')
 for y in years: 
 
    gm, gd = GregorianCalendar_Easter(y)
    jm, jd= JulianCalendar_Easter(y)
    om,od = OrthodoxCalendar_Easter(y)
    
    gm= '{0:02d}'.format( gm)   if  gm  else  'na'
    gd= '{0:02d}'.format( gd)   if  gd  else  'na'
    jm= '{0:02d}'.format( jm)   if  jm  else  'na'
    jd= '{0:02d}'.format( jd)   if  jd  else  'na'
    om= '{0:02d}'.format( om)   if  om  else  'na'
    od= '{0:02d}'.format( od)   if  od  else  'na'
    
    print( " {0:4d}\t G:{1}-{2}\t J:{3}-{4}\t O:{5}-{6}".format(y,gm,gd,jm,jd,om,od) ) 
    
 print('')    
    
    
