#!/usr/bin/env python
#13.07.2014 By Tim "Butter"
# For the Olimex Weekend Programming Challenge – Week #61 plus minus
# License ist opensource beerware, coffeeware, waterware or whatever

max=6560
pos=0
def ternary(c):
    cl=[2,2,2,2,2,2,2,2]
    for i in range(8):
        j =3**(7-i)
        cl[i] =  c/j
        c=c-j*cl[i]
    return cl

def ttt(cl):
    s=[]
    for i in range(8):
        s.append(str(i+1))
        if cl[i]==0:
            s.append('+')
        elif cl[i]==1: 
            s.append('-')
        elif cl[i]==2: 
            s.append('')
    s.append('9')
    st =''.join(s)
    return st

for i in range(max+1):
    st = ttt(ternary(i))
    result=eval(st)
    if (result == 100):
        print st," = 100"
        pos+=1
print""
print "Voila, there are %s possibilities." %pos
print  "Thank you Olimex!"


