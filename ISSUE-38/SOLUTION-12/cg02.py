import png
#wget http://pypng.googlecode.com/svn/trunk/code/png.py
#http://pythonhosted.org/pypng/ex.html
#http://pythonhosted.org/pypng/png.html
f = open('100x100.png', 'r')
#http://olimex.files.wordpress.com/2013/12/100x100.png
#black and white image only
p = png.Reader(f)
t = p.read()
width = t[0]
height = t[1]
pixels = list(t[2])
#be careful: black pixel (value=0) means mass
grid = [[(1 if x == 0 else 0) for x in y] for y in pixels]
f.close()
cgxm = 0
cgym = 0
summ = 0
#http://theory.uwinnipeg.ca/physics/rot/node4.html
for j in range(0, height):
    for i in range(0, width):
        cgxm += i * grid[j][i]
        cgym += j * grid[j][i]
        summ += grid[j][i]
if summ > 0:
    print "CG in X axis", (cgxm * 1.0) / summ
    print "CG in Y axis", (cgym * 1.0) / summ
else:
    print "no mass"