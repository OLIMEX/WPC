#!/bin/bash
#
# Olimex weekend challenge #7
# Solution proposed by Francesco Frassinelli

# Surprise! :D

# http://docs.python.org/2/tutorial/controlflow.html#lambda-forms v   v https://en.wikipedia.org/wiki/Multinomial_theorem
python -c"from math import factorial as f;p=lambda s:sum(map(lambda d:f(s-d)/f(d)/f(s-d*2),range((s or -2)/2+1)));print(p(input('N: ')))"
#                          ^ https://en.wikipedia.org/wiki/Factorial   adding double steps ^        ^ correct result for N: 0