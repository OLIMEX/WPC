{.checks: off, optimization: speed.}

import math, strutils, times

const m = 1_000_000  

var start = epochTime()

for x in 1 .. int(sqrt(float(m))):
  if m mod x == 0:
    var xs = $x
    if not (xs).contains('0'):
      var ys = $(m div x)
      if not (ys).contains('0'):
        echo "Found $1 and $2" % [xs, ys]  

var stop = epochTime()
var delta = 1000 * (stop - start)
echo "Runtime: $1 milliseconds" % formatFloat(delta, ffDecimal, 4)
