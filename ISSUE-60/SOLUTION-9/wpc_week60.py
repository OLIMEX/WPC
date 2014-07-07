#!/usr/bin/env python
# 6.Jul.2014
# Nikolay Dimitrov
#
# I was thinking to write a 6502 assembly solution, but this one is already obscure enough :D

k = [-2.07534349e+2, 4.67289262e-1, -4.39914565e-4, 2.96930016e-7, -1.07707815e-10, 1.58856097e-14]

def main():
    print "Weekend Programming Challenge, Week 60"
    print "Solution written by Nikolay Dimitrov\n"

    try:
        s = raw_input("Please enter KTY81/110 resistance [490-2211 ohms]: ")
        r = float(s)

        if r not in range(490, 2212):
            raise ValueError

        t = 0.
        for p in range(0, 6):
            t += k[p]*pow(r, p)

        t = round(t)
        print "Temperature is %.1fC, %.1fF" % (t, t * 9 / 5 + 32)

    except:
        print "Invalid input value (%s), please use only real numbers in the range [490, 2211]!" % s

if __name__ == "__main__":
    main()
