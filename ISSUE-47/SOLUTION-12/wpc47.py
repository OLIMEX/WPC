#!/usr/bin/env python

__author__ = 'theAdib'
__copyright__ = 'Copyright (c) 2014 Adib'
__license__ = 'New-style BSD'
__version__ = '0.1'



import datetime
import dateutil

""" implementation of julian day calculation taken from here: http://code-highlights.blogspot.de/2013/01/julian-date-in-python.html"""
def date_to_julian_day(my_date):
    """Returns the Julian day number of a date."""
    a = (14 - my_date.month)//12
    y = my_date.year + 4800 - a
    m = my_date.month + 12*a - 3
    return my_date.day + ((153*m + 2)//5) + 365*y + y//4 - y//100 + y//400 - 32045
    
    
date1 = datetime.datetime.strptime('Jun 1 2005', '%b %d %Y')
date2 = datetime.datetime.strptime('Jun 2 2005', '%b %d %Y')

print "The calculated difference of {0} and {1} is {2} days.".format(date1.strftime("%Y-%m-%d"), date2.strftime("%Y-%m-%d"), abs(date_to_julian_day(date1) - date_to_julian_day(date2)))
