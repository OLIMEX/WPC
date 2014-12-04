#!/usr/bin/env python
# -*- coding: utf-8 -*-

def txt2num(string):
    base = { 'one' : 1, 'a' : 1, 'two' : 2, 'three' :3, 'four' : 4, 'five' : 5, 'six' : 6, 'seven' : 7 , 'eight' : 8 , 'nine' : 9 , 'ten' : 10 , 'eleven' : 11 , 'twelve' : 12 , 'thirteen' : 13 , 'fourteen' : 14 , 'fifteen' : 15 , 'sixteen' : 16 , 'seventeen' : 17 , 'eighteen' : 18 , 'nineteen' : 19 , 'twenty' : 20 , 'thirty' : 30 , 'forty' : 40 , 'fifty' : 50 , 'sixty' : 60 , 'seventy' : 70 , 'eighty' : 80 , 'ninety' : 90 } 
    powers = { 'thousand' : 3 , 'million' : 6 , 'billion' : 9 , 'trillion' : 12 }
    n=0
    s=0
    h=0
    string=string.replace(' and ', ' ')
    string=string.replace('-', ' ')
    string=string.replace('is equal to', '')
    string=string.split()[::-1]
    for t in string:
        if(t in powers):
            s=powers[t]
            h=0
        elif(t=="hundred"):
            h=2
        else:
            n=n+base[t]*10**(s+h)
    return n

def list2num(l):
    if len(l)==3:
        if(l[1]=='plus'):
            return l[0]+l[2]
        elif(l[1]=='minus'):
            return l[0]-l[2]
        elif(l[1]=='times'):
            return l[0]*l[2]
        else:
            return l[0]/l[2]
    else:
        b=False
        if('times' in l and not b):
            pos=l.index('times')
            n=l[pos-1]*l[pos+1]
            b=True
        elif('over' in l and not b):
            pos=l.index('over')
            n=l[pos-1]/l[pos+1]
            b=True
        elif('minus' in l and not b):
            pos=l.index('minus')
            n=l[pos-1]-l[pos+1]
            b=True
        elif('plus' in l and not b):
            pos=l.index('plus')
            n=l[pos-1]+l[pos+1]
            b=True
        t=[]
        for i in range(0, pos-1):
            t.append(l[i])
        t.append(n)
        for i in range(pos+2, len(l)):
            t.append(l[i])
        return list2num(t)

def mathtxt2num(string):
    operators=['plus', 'minus', 'times', 'over']
    l=[]
    i=0
    s=""
    for t in string.split():
        if(t in operators):
            l.append(txt2num(s))
            s=""
            l.append(t)
        else:
            s=s+t+" "
    l.append(txt2num(s))
    return list2num(l)

print mathtxt2num("one million two hundred and fifty-six thousand seven hundred and twenty-one plus six hundred and thirty-one million two hundred and fifty-six thousand seven hundred and twenty-one times seven hundred and twenty-one thousand and eleven minus one hundred and seventy-two million seven hundred and eighty-six thousand two hundred and ninety-seven is equal to")

print mathtxt2num("one plus two minus three times four plus seven times two minus ten over two is equal to")

print mathtxt2num("fifteen hundred plus one is equal to")
