

daysinmonth = [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

# finds this year is leap year or not
# http://www.timeanddate.com/date/leapyear.html
# http://support.microsoft.com/KB/214019
def isleapyear(y):
    if y % 4 == 0:
        if y % 100 == 0:
            if y % 400 == 0:
                return 1
            else:
                return 0
        else:
            return 1
    else:
        return 0
# testing for isleapyear()
#for i in [2000, 2400, 2004, 2008, 1816]:
#    print i, isleapyear(i)
#for i in [1800, 1900, 2100, 2200, 2300, 2500, 2003, 2007]:
#    print i, isleapyear(i)
def daysofmonth(m, y=1):
    if m == 2:
        return 28 + isleapyear(y)
    elif m in range(1, 13):
        return daysinmonth[m]
    else:
        return 0

# validate dates
def validatedate(ad, am, ay):
    if am not in range(1, 13):
        return False
    if ad not in range(1, 1 + daysofmonth(am, ay)):
        return False
    return True

def compardates(ad, am, ay, bd, bm, by):
    if not validatedate(ad, am, ay):
        print "ad, am, ay is invalid date -> ", ad, am, ay
        exit()
    if not validatedate(bd, bm, by):
        print "bd, bm, by is invalid date -> ", bd, bm, by
        exit()

    # 2. swap if a < b so that a >= b
    if ay*10000 + am*100 + ad < by*10000 + bm*100 + bd:
        amorethanb = False
        tmpy = ay
        tmpm = am
        tmpd = ad
        ay = by
        am = bm
        ad = bd
        by = tmpy
        bm = tmpm
        bd = tmpd
    else:
        amorethanb = True

    addeddays1 = 0
    if bd > ad: # add days to by, bm, bd until bd = 1, also next month or year if need
        submonth = -1
        addeddays1 = daysofmonth(bm, by) - bd + 1
        bd = 1
        bm += 1
        if bm == 13:
            bm = 1
            by += 1
    # to calculate only months
    am += (ay - by) * 12
    dd = ad - bd + addeddays1
    dm = am - bm
    dy = dm / 12
    dm = dm % 12
    return amorethanb, dd, dm, dy

if __name__ == "__main__": 
    dates = [[2013, 1, 31, 2012, 12, 30], \
    [2012, 12, 1, 2012, 10, 1], \
    [2012, 12, 1, 2012, 10, 30], \
    [2012, 12, 1, 2012, 11, 30], \
    [2013, 12, 1, 2012, 11, 30], \
    [2014, 12, 1, 2012, 11, 30], \
    [2014, 1, 31, 2012, 12, 30], \
    [2014, 1, 1, 2014, 12, 31], \
    [2014, 1, 1, 2013, 1, 1], \
    [2014, 3, 28, 2013, 1, 28], \
    ]
    for x in dates:
        amorethanb, dd, dm, dy = compardates(x[2], x[1], x[0], x[5], x[4], x[3])
        if amorethanb:
            print "a elder than b (or equal)", "diffrence in years =", dy, "months =", dm, "days =", dd
        else:
            print "b elder than a", "diffrence in years =", dy, "months =", dm, "days =", dd
