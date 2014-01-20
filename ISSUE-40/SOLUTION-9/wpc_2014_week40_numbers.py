# -*- coding: utf-8 -*-
#------------------------------------------------------------------------------
# Name:     wpc_2014_week40_numbers.py
# Goal:		all integer are represent by 1,*3,/2
#	Olimex Programming Challenge 40 - January 2014
#
# Author:   Jean Sorgemoel
#
# Created:  14th January 2014
# Licence:  <GNU GPL v3>
#
#------------------------------------------------------------------------------
# GNU GPL v3 Licence Summary:
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#------------------------------------------------------------------------------
#
# Problem:
# 	Any positive integer number can be presented as 1 and several operations *3
#		and /2 discarding the result after the decimal point when dividing.
#
# 	for instance:
# 		4 = 1 *3 *3 /2
# 		12 = 1 *3 *3 /2 *3
#
# 	make code which enters positive integer N then present it with 1 *3 /2
#		equation.
#
# see web site :
#    http://olimex.wordpress.com/2014/01/17/


class NotPositiveNumber(ValueError):
    pass


# challenge_40 : for number, search mix of '1' '*3' '/2'
# number : integer (>=1)
# maxiloop : (security (0=desactivate)
# return : result (format:string)
def challenge_40(number, maxiloop=0):
    result = ""
    value = number
    dico = {}
    order = {}
    pos = 0
    # if you want, for number = 1, you can give result 1*3/2
    while value > 1:
        # erase value ignored
        ignore = 0
        # search if loop
        if value in dico:
            revert_order = {}
            for key, tmp in order.items():
                revert_order.setdefault(tmp, key)
            if revert_order[value] == 0:
                tmppos = revert_order[value]
                ignore = order[tmppos + 1]
                value = order[tmppos]
                result = dico[value]
            else:
                tmppos = revert_order[value] - 1
                ignore = value
                value = order[tmppos]
                result = dico[value]
            # regenerate dico (suppress value after value)
            newdico = {}
            neworder = {}
            for key in range(tmppos + 1):
                newdico.setdefault(order[key], dico[order[key]])
                neworder.setdefault(key, order[key])
            dico = newdico
            newdico = {}
            neworder = {}
            pos = tmppos + 1
        else:
            dico.setdefault(value, result)
            order.setdefault(pos, value)
            pos = pos + 1
        # for security
        if maxiloop > 0:
            maxiloop = maxiloop - 1
            if maxiloop == 0:
                raise 'maxi loop'
        tmp = ""
        while value % 3 == 0:
            value = value // 3
            tmp = tmp + "*3"
        if value > 1 and value % 3 != 0:
            tmp = "/2" + tmp
            while((value * 2 + 1 == ignore) or (
                    (value * 2 + 1) % 3 != 0 and
                    (value * 2) % 3 != 0)):
                # for security
                if maxiloop > 0:
                    maxiloop = maxiloop - 1
                    if maxiloop == 0:
                        raise 'maxi loop'
                tmp = "/2" + tmp
                value = value * 2
            value = value * 2
            if (value * 2 + 1) % 3 != 0:
                value = value + 1
        result = tmp + result
    return "1" + result


# To generate with range
def loop_result(begin=1, end=10):
    for i in range(begin, end + 1):
        print("%d = %s" % (i, challenge_40(i)))


# main program
def main():
    print("Program to convert integer in format (1,*3,/2)")
    number = input("what's number?")
    try:
        i = int(number)
        if i <= 0:
            raise NotPositiveNumber
    except NotPositiveNumber:
        print("it's not positive number (>=1)")
    except ValueError:
        print("it's not number")
    else:
        print("%d = %s" % (i, challenge_40(i)))

if __name__ == '__main__':
    main()
    #loop_result(end=1500)
    print('End')
