#!/usr/bin/python
# encoding: utf-8
# http://olimex.wordpress.com/2014/03/21/weekend-programming-challenge-week-47-calendar-dates-substraction/
# Matthias Schmitz <matthias@sigxcpu.org>

import argparse
import datetime
import sys


try:
    from dateutil import relativedelta as rd
except:
    print 'Could not import dateutil.relativedelta. Please install python-dateutil/dateutil.'
    sys.exit(1)


def calculate_difference(date1, date2):
    ''' (str, str) -> tuple
    Calculate the difference between date1 and date2 and return a tuple with an
    adjective as string and a relativedelta object.

    >>> a = '31.12.2013'
    >>> b = '22.03.2014'
    >>> calculate_difference(a, b)
    ('older', relativedelta(months=-2, days=-22))
    >>> c = '22.03.2014'
    >>> d = '22.03.2014'
    >>> calculate_difference(c, d)
    ('same', relativedelta())
    >>> e = '29.04.1989'
    >>> f = '22.03.1952'
    >>> calculate_difference(e, f)
    ('younger', relativedelta(years=+37, months=+1, days=+7))

    '''
    birthday1 = parse_datestring(date1)
    birthday2 = parse_datestring(date2)

    if birthday1 < birthday2:
        adj = 'older'
    elif birthday1 > birthday2:
        adj = 'younger'
    else:
        adj = 'same'

    return (adj, rd.relativedelta(birthday1, birthday2))


def parse_datestring(datestring):
    ''' str -> datetime.datetime
    Convert the string datestring to datetime.datetime.
    >>> parse_datestring('31.12.2013')
    datetime.datetime(2013, 12, 31, 0, 0)

    '''
    try:
        date = datetime.datetime.strptime(datestring, '%d.%m.%Y')
    except ValueError as e:
        print "Could not parse date \"%s\"." % datestring
        sys.exit(1)
    return date


def main():

    parser = argparse.ArgumentParser()
    parser.add_argument('--birthday-one', dest='date1', required=True,
                        help='birthday of person one in format DD.MM.YYYY')
    parser.add_argument('--birthday-two', dest='date2', required=True,
                        help='birthday of person two in format DD.MM.YYYY')

    args = parser.parse_args()

    adj, delta = calculate_difference(args.date1, args.date2)

    if adj == 'same':
        print "Person one and person two are at the same age."
    else:
        print "Person one is %i day(s), %i month(s) and %i year(s) %s than person two." % (abs(delta.days), abs(delta.months), abs(delta.years), adj)


if __name__ == '__main__':
    main()
