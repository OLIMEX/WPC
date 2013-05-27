Hi Olimex guys!

Here's my solution for the Weekend Programming Challenge 10.

It's written as a C# console application but the nitty-gritty is in the Denominators class.

The solution uses long values throughout; no floating points as this would be slow and comparisons will be inaccurate.

The steps it takes are:

1.  Refactor the input fraction a/b into a*a/a*b.  This allows us to use longs throughout as the smallest viable fraction (1/n) in the output will be 1/a*b.

2.  The solution enters a loop testing each divisor starting at 2 and incrementing by 1 on each pass through.  It will end at a*b.

3.  On each test, it calculates the integer value of a*b/divisor.  If there's a remainder, the divisor is not a viable value for the output.  The divisor is bumped and we start another cycle.

4.  If the remainder is 0, it could be a viable value for the output.  This is when we also check the residual value.  This starts out at a*a and is reduced each time we find an output value.  It keeps track of the valid fractional amounts in terms of 1/a*b we find.  If the residual less the a*b/divisor value is not negative, the divisor is valid and is added to the output.

5.  If there's still some residual left, we bump the divisor and cycle round the loop again.

6.  When both the remainder and residual reach 0, we're done and we display the values found.

It also runs a check by displaying the input a/b fraction and the result of summing the output 1/n fractions as floating point values.  If all's well, they should be the same!

Nigel