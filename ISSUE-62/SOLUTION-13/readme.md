

Hi,
i'm Mirco from Italy and here's my solution to #62 code challenge, as mail
attachment.

Solution is coded in ANSI C (hope to be strict ANSI compliant :D).

Small explanation:
There is a simple loop that increments a variable, skipping all numbers
that contains 0.
For each number then a calculation is made to check if there is another
number that make a solution for the calculus. If there is one, then is
checked if contains zeroes.
Note: the loop goes from 1 to 999 because no number above 1000 could be a
solution, because the other number should be <1000, and we've already
scanned that range.
For each solution two results are emitted, with reversed number order.

Best Regards
Mirco Boschi

