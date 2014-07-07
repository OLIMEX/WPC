#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys

if __name__ == '__main__':
    # load datasheet values from file
    # format:
    # (temp, temp_coef, res_min, res, res_max, temp_error)
    data = []
    with open('KTY81_110.txt') as ds:
        lines = ds.read().splitlines()
        data = [
            (int(l[0]), float(l[1]), int(l[2]), int(l[3]), int(l[4]), float(l[5]))
            for l in [ln.split() for ln in lines]
        ]

    # retrieve resistance value
    if len(sys.argv) > 1:
        res = int(sys.argv[1])
        print('Resistance: {}'.format(res))
    else:
        res = int(input('Resistance: '))

    # check input
    if res < data[0][2] or res > data[-1][4]:
        print('Invalid resistance')
        exit(0)

    # find two corresponding records in table
    for rec in data:
        if res < rec[3]:
            rec_next = rec
            break
        rec_prev = rec

    # find mid value between two records
    mid = (rec_next[3] - rec_prev[3]) * rec_prev[1] / (rec_prev[1] + rec_next[1]) + rec_prev[3]
    if res < mid:
        rec = rec_prev
    else:
        rec = rec_next

    # calculate temp
    temp = rec[0] + (res - rec[3]) * 100 / rec[3] / rec[1]
    print('Temperature: {:.2f} °C'.format(temp))
