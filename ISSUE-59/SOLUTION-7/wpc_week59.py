#!/usr/bin/env python
# 28.Jun.2014
# Nikolay Dimitrov

import sys, struct, pickle

def main(args):
    print "Weekend Programming Challenge, Week 59"
    print "Solutions written by Nikolay Dimitrov\n"

    print "Solution 1 (sys.byteorder)\nEndianness = %s" % sys.byteorder

    if struct.pack("<L", 0x12345678) == struct.pack("=L", 0x12345678):
        s = "little"
    else:
        s = "big"
    print "\nSolution 2 (struct)\nEndianness = %s" % s


    if pickle.dumps(0x12345678, 1)[1:5] == "\x78\x56\x34\x12":
        s = "little"
    else:
        s = "big"
    print "\nSolution 3 (pickle)\nEndianness = %s" % s

if __name__ == "__main__":
    main(sys.argv)
