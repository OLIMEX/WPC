#!/usr/bin/env python
# encoding: utf-8

import datetime
from dateutil.relativedelta import relativedelta


if __name__ == '__main__':
    braw1 = raw_input("Enter the birthday of Person 1 (YEAR/MONTH/DAY): ")
    b1 = datetime.date((int)(braw1.split("/")[0]), (int)(braw1.split("/")[1]), (int)(braw1.split("/")[2]))
    
    braw2 = raw_input("Enter the birthday of Person 2 (YEAR/MONTH/DAY): ")
    b2 = datetime.date((int)(braw2.split("/")[0]), (int)(braw2.split("/")[1]), (int)(braw2.split("/")[2]))
    
    years = relativedelta(b1, b2).years
    months = relativedelta(b1, b2).months
    days = relativedelta(b1, b2).days
    
    print "Time between Person 1 and Person 2: %d/%d/%d (Years/Months/Days)" % (years,months,days)
