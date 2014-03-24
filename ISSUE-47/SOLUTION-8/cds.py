#!/usr/bin/env python3
#-*- coding:utf-8 -*-
''' 
 2014-03-23 by kantal59
 License: LGPL
 OLIMEX WPC#47: Calendar dates substraction
            Enter the birthday dates of two persons and display how many Years/Months/Days one is older than the other.
            
            Python modules 'datetime','calendar' are not applied.
'''

import sys

dom=[ 31,28,31,30,31,30,31,31,30,31,30,31 ]

def leap_year( year):
    if year%4 :      return(0)
    if year%100 :    return(1)
    if not year%400: return(1)
    return(0)

def dim( month, year):  #days in month
    return(  dom[month-1] if month!=2 else 28 + leap_year(year) )   

def dcheck( year, month, day):
    if year<1 or year >9999 or month<1 or month>12 or day<1 or ( month!=2 and day > dom[month-1] ) or (month==2 and day > (dom[1]+leap_year(year)) ) :
        return False
    return True
         

def isoformat( year, month, day):
    return( "{0:04d}-{1:02d}-{2:02d}".format(year, month,day) )
#-----------------------------------    


dates= [] 
if len(sys.argv)!=3:

    print("\nUsage: $ ./cds.py  date1 date2\n where the date format is y-m-d\n\n" )
    # test data:
    dates=[ ((1969,7,20),(2014,7,20)), ((2010,8,20),(2010,8,22)), ((2010,8,20),(2010,7,23)), 
            ((2014,3,21),(2013,3,21)), ((2013,3,31),(2014,3,21)), ((2013,3,1),(2014,3,21)),
            ((2014,3,21),(2013,9,30)), ((2013,2,25),(2014,3,21)), 
            ((2012,2,28),(2013,2,28)), ((2012,2,27),(2013,2,28)),  ((2012,2,29),(2013,2,28)),
            ((2012,2,28),(2014,2,28)), ((2012,2,29),(2014,2,28)),
            ((2012,2,28),(2013,3,1)),  ((2012,2,29),(2013,3,1)),
            ((2012,2,28),(2016,2,28)), ((2012,2,28),(2016,2,29)), ((2012,2,29),(2016,2,29)),((2012,2,29),(2016,2,28)),
            ((2012,2,28),(2020,2,28))  ]

else:

    d1= sys.argv[1].split('-')
    d2= sys.argv[2].split('-')
    dates=[ ( (int(d1[0]),int(d1[1]),int(d1[2])), (int(d2[0]),int(d2[1]),int(d2[2])) ) ]



for dpair in dates:

    if not dcheck( *dpair[0]) or not dcheck( *dpair[1]):
        print( " Invalid date in {0}".format( dpair) )
        sys.exit(2)

    # put in ascending order
    date1,date2= dpair
    
    y1,m1,d1 = date1
    y2,m2,d2 = date2
    if  isoformat( *date1 ) > isoformat( *date2 ) :
        y1,m1,d1 = date2
        y2,m2,d2 = date1
    
    # get the difference        
    dy= y2-y1
    dm= m2-m1
    dd= d2-d1
    
    diff=()
    if dm < 0:  
        diff=( dy-1, dm+11, dim(m1,y1)-d1+d2 )
    
    else:
        
        if dm == 0:
            if dd < 0:  
                diff=( dy-1, 11, dim(m1,y1)-d1+d2 ) 
            else:
                if m1==2 and d1!=29:    dd+=1
                diff=( dy, dm, dd)
        else:  # dm>0
            if dd < 0:
                diff=( dy, dm-1, dim(m1,y1)-d1+d2 )
            else:
                if m1==2 and d1!=29:    dd+=1
                diff=( dy, dm-1, dd)    
                             
    # output
    msg=''
    if leap_year(y1):   msg+= "1. leap year; "
    if leap_year(y2):   msg+= "2. leap year; "
    print( "{0} ---> {1}".format( isoformat(y1,m1,d1), isoformat(y2,m2,d2) ), end=' ' )
    print( " diff: {0:4d} year(s), {1:2d} month(s), {2:2d} day(s); {3}".format( diff[0],diff[1],diff[2],msg ) )



