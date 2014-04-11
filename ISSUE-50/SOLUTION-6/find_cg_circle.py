
# code1 for convert pbm file (header removed) to textfile
code1="""
data = [line.strip() for line in open('./circle100x100.pbm.txt', 'r')]
data2 = []
for i in data:
    for j in i:
        data2.append(j)
data3 = ["".join(data2[i*100: i*100 + 100]) for i in range(100)]
f = open('./circle_100x100.txt', 'w')
f.writelines( "%s\n" % item for item in data3)    
f.close()
"""

# centre of solid circle is its own CG
# finding CG by https://github.com/OLIMEX/WPC/blob/master/ISSUE-38/SOLUTION-12/cg02.py
grid = [[int(c) for c in line.strip()] for line in open("./circle_100x100.txt", "r")]
cgxm = 0
cgym = 0
summ = 0
for j in range(100):
    for i in range(100):
        cgxm += i * grid[j][i]
        cgym += j * grid[j][i]
        summ += grid[j][i]
if summ > 0:
    print "Centre X axis", round(1.0 * cgxm / summ)
    print "Centre Y axis", round(1.0 * cgym / summ)
else:
    print "no object"