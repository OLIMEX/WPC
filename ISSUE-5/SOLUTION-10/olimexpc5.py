#!/usr/bin/env python

import math
import optparse
import random
import sys

class Floor:

    def __init__(self,l,t):
        """
        - l: lenght of needles
        - t: distance between floor lines
        """
        if l > t or l <=0:
            raise ValueError
        else:
            self.l = l
            self.t = t
        self.crossed = 0
        self.throws = 0

    def throw(self,n):
        """Throw n needles"""
        self.crossed = 0
        for i in xrange(n):
            d = random.random() * self.t / 2
            y = self.random_angle_sin() * self.l / 2
            self.crossed += ( (d - y) < 0 ) * 1
        self.throws = n
        

    def random_angle_sin(self):
        """Return the sin of an uniformely distributed angle
        
        We don't know pi, so we just get a random point in the unit 
        square and exlude those that are outside the unit circle.
        
        We arbitrarily decide to ignore the fact that this already 
        gives an aproximation of pi :D
        """
        d = 2
        while d > 1:
            x = random.random()
            y = random.random()
            d = x**2 + y**2
        return y/math.sqrt(d)

    def get_pi(self):
        """Return the current approximation of pi"""
        if self.t == 0 or self.crossed == 0:
            return None
        else:
            return ( 2 * self.l * self.throws) / float( self.t * self.crossed )


def main():
    parser = optparse.OptionParser()
    parser.add_option('-t', help='Distance between parallel lines', 
            type="float")
    parser.add_option('-l', help="Lenght of the needles (must be < t)",
            type="float")
    parser.add_option('-n', help="Number of throws",
            type="int")
    opt, arg = parser.parse_args()

    if opt.t == None or opt.l == None or opt.n == None:
        parser.print_help()
        sys.exit(1)

    try:
        floor = Floor(opt.l,opt.t)
    except ValueError:
        parser.print_help()
        sys.exit(1)
    floor.throw(opt.n)
    print floor.get_pi()


if __name__ == '__main__': main()
