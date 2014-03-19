# -*- coding: utf-8 -*-

"""

Spyder Editor


This temporary script file is located here:

/home/mariaagg/.spyder2/.temp.py

"""


kk=0

time=0


while time <7920:

time=kk*720

hour=time/(60*11)

minutesrest=(time -hour *60*11)%11

minutesintpart=((time -hour *60*11)-minutesrest)/11

print hour, 'hours ', minutesintpart, 'min', minutesrest,'/11 min'

# print hour

kk+=1

print 'counting the initial and final crossings at 00.00 and 12.00 \nthere
are', \

kk ,'crossings between 00.00 hrs and 12.00 hrs'


