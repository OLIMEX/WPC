from fractions import gcd
## finding Egyptian fractions

def ef1(x, y):
    ## find irreducible x/y fraction
    g = gcd(x, y)
    if g > 1:
        x = x / g
        y = y / g

    if x == 1:
        return [y]
        exit

    ## choose d in order to evaluate x/y = (1 / d) + ((x * d - y) / (y * d))
    ## http://en.wikipedia.org/wiki/Greedy_algorithm_for_Egyptian_fractions#Sylvester.27s_sequence_and_closest_approximation
    d = y / x + 1
    retlist = [d]
    retlist.extend(ef1((x * d - y), (y * d)))
    return retlist

## main
## you may choose x/y -> 3/4, 5/6, 5/121, 1805/1806, 18/23, 31/311, 13/17
xx = int(raw_input('Enter x number '))
yy = int(raw_input('Enter y number '))
if xx >= yy:
  print "Cannot compute, sorry\n"
  exit(0)

print ef1(xx, yy)

