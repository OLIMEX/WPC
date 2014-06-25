#!/usr/bin/env python
# 22.Jun.2014
# Nikolay Dimitrov

import sys, datetime

def main(args):
    print "Weekend Programming Challenge, Week 58"
    print "Solution written by Nikolay Dimitrov\n"

    try:
        s = args[1].split("/")
        print "Seconds elapsed since %s: %d" % (args[1], (datetime.date(int(s[2]), int(s[1]), int(s[0])) - datetime.date(1, 1, 1)).total_seconds())

    except:
        print "Usage: python %s <dd/mm/yyyy>" % args[0]

if __name__ == "__main__":
    main(sys.argv)
