#!/usr/bin/python2
# -*- coding: utf-8 -*-

'''
Created on 22-03-2013

@author: micign
'''


class P(object):

    '''A minimal,read-only 2D point class'''

    def __init__(self, pair):
        (self.x, self.y) = map(float, pair)

    def __getattr__(self, coord):
        return self[coord]

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y


def d(A, B, C):
    '''returns disatnce from point C to line passing through  points A and B'''

    (a, b, c) = (P(A), P(B), P(C))

    return (((c.x * (b.y - a.y) + c.y * (a.x - b.x) - a.x * b.y + b.x * a.y) ** 2 / ((a.x
            - b.x) ** 2 + (a.y - b.y) ** 2)) ** 0.5 if A != B else None)


if __name__ == '__main__':
    A = [-114, 2.2000]
    B = [-114, 2.201]
    C = [-114.01, -6.3]
    print d(A, B, C)
