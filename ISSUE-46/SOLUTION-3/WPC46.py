#!/usr/bin/env python
# -*- coding: utf-8 -*-

import math



if __name__ == '__main__':

    i = 0
        while True:
        a = i / 11
        if a >= 1.0:
            break

        m, h = math.modf(a * 12)
        hi = math.floor(h)
        s, m = math.modf(m * 60)
        mi = math.floor(m)
        s *= 60

        print('{:2}: {:02}:{:02}:{:08.5f}'.format(i + 1, hi, mi, s))
        i += 1


    print('The arrows cross {} times in one twelve hour period'.format(i))


https://gist.github.com/ffoxin/517da160da841a94de0b


