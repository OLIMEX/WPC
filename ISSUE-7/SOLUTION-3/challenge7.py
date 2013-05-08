#-------------------------------------------------------------------------------
# Name:        code challenge
# Purpose:
#
# Author:      Mike Brown
#
# Created:     03/05/2013
# Copyright:   (c) Mike Brown 2013
# Licence:     <your licence>
#-------------------------------------------------------------------------------
def recurse(steps):
    if steps < 0:
        return 0
    if steps == 0:
        return 1
    return (recurse(steps - 2) + recurse (steps - 1))


def main():
    print recurse(4)

if __name__ == '__main__':
    main()
