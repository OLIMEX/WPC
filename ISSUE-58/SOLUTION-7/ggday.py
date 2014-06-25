def jdn(d, m, y, isgregorian = True):
    y += 4800
    m -= 3
    if m < 0:
        y -= 1
        m += 12
    jd = d + (153*m + 2)//5 + 365*y + y//4
    if isgregorian:
        jd = jd - y//100 + y//400 - 32045
    else:
        jd = jd - 32083
    return jd
# -- main --
d, m, y = raw_input("Enter Gregorian date d/m/y: ").split('/')
dn = jdn(int(d), int(m), int(y)) - 1721424
print dn * 86400, " seconds since 1/1/1"

# -- test code --
#lj = jdn(15, 10, 1582, True) #1-st Gregorian date
#rd = jdn(1, 1, 1, False)
#print lj, rd, lj-rd
#chsk = jdn(25, 3, 638, True)
#print "Julian day number when Chula Sakarat started", chsk
#print "Actually it should be 1954167.5. Julian day started at noon"
#print "0001-01-01 to 0638-03-25 (Chula Sakarat started)-> 232747 ->", chsk - 1721424
#print jdn(1, 1, 2000, False) # = 2,451,545 -> OK
#print jdn(1, 5, 2005, True) - 1721424 # = 732,068 days -> OK

# -- ref --
# http://en.wikipedia.org/wiki/Julian_day#Calculation
# http://suriyayart.blogspot.com/2005/05/julian.html?m=1
# http://quasar.as.utexas.edu/BillInfo/JulianDatesG.html
# http://mathforum.org/library/drmath/view/62338.html
# http://www.rungnapa-astro.com/Suriyayatra/Suriya-05.php
# http://www.preceden.com/calculators/duration
