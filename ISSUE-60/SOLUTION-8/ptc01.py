from bisect import bisect
from math import floor
#https://docs.python.org/2.7/library/bisect.html

inputtemp = [-55,\
-50,\
-40,\
-30,\
-20,\
-10,\
0,\
10,\
20,\
25,\
30,\
40,\
50,\
60,\
70,\
80,\
90,\
100,\
110,\
120,\
125,\
130,\
140,\
150, 151]

outputohm = [970,\
1019,\
1123,\
1235,\
1354,\
1480,\
1613,\
1754,\
1903,\
1980,\
2059,\
2222,\
393,\
2571,\
2757,\
2950,\
3150,\
3358,\
3571,\
3779,\
3876,\
3967,\
4125,\
4237, 4237]

readohm = float(raw_input("Enter resistance: "))
if readohm > 150.0 or readohm < -55.0:
    print "resistance out og range"
    exit()

readohmint = floor(readohm)
i = bisect(inputtemp, readohmint)
# assume linear
y1 = 1.00 * outputohm[i-1]
y2 = 1.00 * outputohm[i]
x1 = 1.00 * inputtemp[i-1]
x2 = 1.00 * inputtemp[i]
outtemp = y1 + (y2 - y1)*(readohm - x1)/(x2 - x1)
print outtemp
