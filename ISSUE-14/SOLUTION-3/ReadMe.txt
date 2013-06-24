The approach taken by this solution is similar to the one I took in WPC 10 which also involved fractions.  We want to avoid dealing with fractions as they require types like float, double, decimal etc which have limited precision.  We need to add and subtract values smaller than 1/10,000,000,000 which aren't going to work well with these types.  What we need is a big integer type.  There is code for lots of these on the net but Microsoft added a BigInteger type to .Net Framework 4.5 which should be good to use here.  Before this challenge, I didn't know about this BigInteger so I've learned something from the exercise!

The Liebniz formula is:

 1     1     1     1     1
--- - --- + --- - --- + --- ...
 1     3     5     7     9
 
The first step we'll do is scale these values up to allow us to use integer arithmetic.  If we know how many decimal places of pi we want to aim for, say n, we can scale up to 10^n.  We can then calculate this:
 
 10^n   10^n
 ---- - ---- + ...
   1      3
   
So when n is 2, we'll get a result of 314
   when n is 5, we'll get a result of 314196

We can then convert this into a string and place the decimal point at the required number of decimal places in from the end of the string.

This works fine and yields these results:

Decimal places   Result            Iterations        Duration (mins)
--------------   ---------------   ---------------   -------------------
     4           3.1416                     1,668         -
     5           3.14196                   16,668         -
     6           3.141548                 166,668         -
     7           3.1416024              1,666,668      0.01
     8           3.14159052            16,666,668      0.08
     9           3.141592408          166,666,668      0.79
    10           3.1415925456       1,666,666,668     12.58
    11           3.14159264012     16,666,666,668    161.21 (2.69 hours)
    12           not attempted                       expected to be > 26 hrs

Obviously the moral of the day is the Liebniz approximation is not an efficient way to calculate pi!

Enjoy.