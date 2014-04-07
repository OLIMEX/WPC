
# http://krutov.org/algorithms/easter/
# http://ru.wikipedia.org/wiki/%D0%9F%D0%B0%D1%81%D1%85%D0%B0%D0%BB%D0%B8%D1%8F
#  http://ru.wikibooks.org/wiki/%D0%9F%D1%80%D0%B8%D0%BC%D0%B5%D1%80%D1%8B_%D1%80%D0%B5%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D0%B8_%D0%B0%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC%D0%B0_%D0%BF%D0%B0%D1%81%D1%85%D0%B0%D0%BB%D0%B8%D0%B8
#  http://ru.wikipedia.org/wiki/%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%93%D0%B0%D1%83%D1%81%D1%81%D0%B0_%D0%B2%D1%8B%D1%87%D0%B8%D1%81%D0%BB%D0%B5%D0%BD%D0%B8%D1%8F_%D0%B4%D0%B0%D1%82%D1%8B_%D0%9F%D0%B0%D1%81%D1%85%D0%B8

def gregorian_paskha(x):
    a = x % 19
    b = x / 100
    c = x % 100
    d = b / 4
    e = b % 4
    f = (b + 8) / 25
    g = (b - f + 1) / 3
    h = (19*a + b - d - g + 15) % 30
    i = c / 4
    # j for complex number :)
    k = c % 4
    L = (32 + 2*e + 2*i - h - k) % 7
    m = (a + 11*h + L*22) / 451
    np = (h + L - 7*m + 114)
    return np / 31, np % 31 + 1

def julian_paskha(x):
    a = x % 4
    b = x % 7
    c = x % 19
    d = (19*c + 15) % 30
    e = (2*a + 4*b + 6*d + 6) % 7 
    # d + e = days to Paskha from 22-March
    if d + e > 9:
        m0 = 4
        d0 = d + e - 9
    else:
        m0 = 3
        d0 = d + e + 22
    # adds 13 days for new style date
    ns = d + e + 13 + 22 - 31
    if ns > 30:
        m1 = 5
        d1 = ns - 30
    else:
        m1 = 4 
        d1 = ns
    return m0, d0, m1, d1

if __name__ == "__main__": 
# compare to http://www.oikoumene.org/en/resources/documents/wcc-commissions/faith-and-order-commission/i-unity-the-church-and-its-mission/towards-a-common-date-for-easter/index#table
    for y in range(2001, 2025):
        m, d, m1, d1 = julian_paskha(y)
        m2, d2 = gregorian_paskha(y)
        print "Paskha", y, "Eastern (O.S.):", m, d, "Eastern (N.S.):", m1, d1, "Western:", m2, d2