#!/usr/bin/env python

__author__ = 'theAdib'
__copyright__ = 'Copyright (c) 2014 Adib'
__license__ = 'New-style BSD'
__version__ = '0.1'

'''
Make code which input KTY81/110 real number of resistance in ohms and output the temperature of the sensor.
'''

import decimal

# values taken from datasheet on 1mA
kty81_110_values =  [(490.0, -55.0), (515.0, -50.0), (567.0, -40.0), (624.0, -30.0), (684.0, -20.0), \
    (747.0, -10.0), (815.0, 0.0), (886.0, 10.0), (961.0, 20.0), (1000.0, 25.0), (1040.0, 30.0), \
    (1122.0, 40.0), (1209.0, 50.0), (1299.0, 60.0), (1392.0, 70.0), (1490.0, 80.0), (1591.0, 90.0), \
    (1696.0, 100.0), (1805.0, 110.0), (1915.0, 120.0), (1970.0, 125.0), (2023.0, 130.0), \
    (2124.0, 140.0), (2211.0, 150.0)]
    

def temperature(ohm):
    '''
    calculate the temperature by linear interpolating values
    returns -Infinity/Infinity in case of range under/overflow
    '''
    if ohm < kty81_110_values[0][0]:
        # too small
        return -decimal.Decimal('Infinity')
    for i in range(len(kty81_110_values) - 1):
        if ohm >= kty81_110_values[i][0] and ohm <= kty81_110_values[i + 1][0]:
            # print ohm, kty81_110_values[i][0], kty81_110_values[i +1][0], kty81_110_values[i][1], kty81_110_values[i +1][1]
            x0 = kty81_110_values[i][0]
            x1 = kty81_110_values[i + 1][0]
            y0 = kty81_110_values[i][1]
            y1 = kty81_110_values[i + 1][1]
            t = (((y1 - y0)*(ohm - x0))/(x1 - x0) ) + y0
            return t
    return decimal.Decimal('Infinity')
    

for x in [490, 517, 2211, 400]:
    print x, temperature(x)


