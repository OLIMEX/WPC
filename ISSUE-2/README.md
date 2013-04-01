ISSUE#2 - Sorting
===

Problem:

Let A[N] is array of N integers. 
Shuffle the elements of A in such way that the differences between each neighbour elements d[i] = A[i]-A[i+1] make row in ascending order.

For instance:

A[4] = { 10, 2, 7, 4 }

possible soluions are:

{  2, 7, 10, 4 } because  (2 – 7) < (7 – 10) < (10 – 4)

or:

{ 4, 10, 7, 2 } because (4 – 10) < (10 – 7) < (7 – 2)



Solutions:
==

1. Vasil Kalkov, Ruby - we tested but do not do what is necessary

2. Mateusz Klatecki, C - works!

3. Niki Qnakiev, C - non working

4. Miller Wang, C - works for N=3 but when change N=4 stop working

5. Tobias Hulsdau, Python - works!

6. Piotr Gapinski, Prolog - most exotic solution! works