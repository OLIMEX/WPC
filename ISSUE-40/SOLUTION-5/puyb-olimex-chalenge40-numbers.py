# Convert an integer in a list of multiplication by 3 and integer division by 2
# Olimex Weekend Prorgamming Challenge  Week #40 Numbers
# http://olimex.wordpress.com/2014/01/17/weekend-prorgamming-challenge-week-40-numbers/
# Author: Stephane Puybareau (puyb) <puyb@puyb.net>
# 2014-01-18 - WTFPL licence


def calc(number):
    if number <= 0:
        raise "number must positive"

    # list previously seen configuration to skip them and avoid end loop
    seen = [number]

    #actual is the current list of number and solutions we're working on
    actual = [ (number, '') ]
    # suiv (next in french), is the next list of number to work on
    suiv = []
    while True:
        for item in actual:
            # first optimisation, skip if we've already seen this number
            if item in seen:
                next
            seen.append(item)

            # end condition
            if item[0] == 1:
                return '1' + item[1]


            # this result is a multiple of 3, 
            # so we asume it's the result of a multiplication
            if item[0] % 3 == 0:
                # second optimisation, fast skip multiple *3 multiplication
                while item[0] % 3 == 0:
                    item = (item[0] / 3, '*3' + item[1])
                suiv.append(item)
                next

            # this number can either be the result of the division by 2 
            # of ( 2 * item[0] ) or ( 2 *  item[0] + 1 )
            suiv.append((item[0] * 2    , '/2' + item[1]))
            suiv.append((item[0] * 2 + 1, '/2' + item[1]))

        actual = suiv
        suiv = []

if __name__ == '__main__':
    # simple test 1 .. 12
    for number in range(1, 13):
        print(number, '=', calc(number))
