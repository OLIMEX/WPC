#!/usr/bin/env python3
#-*- coding:utf-8 -*-
''' 
 2013-11-24 by kantal59
 License: LGPL
 OLIMEX WPC#34: POV LED display
    Persistence of Vision (POV) is made with stripe of LEDs which rotates at 360 degree.
    If we assume the stripe is with 100 LEDs you can make square “screen” with size approx 140×140 pixels.
    Make code which converts 140×140 pixels picture to array of LED stripe values for each angle 0-360. 
    When LED from the stripe are not at exact pixel positions the best way to set their value is to mediate the value 
    depend on the closest pixel neighbors.
    
    Graphic demo for ledstripe.py
'''

import ledstripe
from  tkinter import *
from math import *



def rotate():
    ''' It draws stripes for each angle value. You can play with the 'rtime' value. '''
    global points,cos1,sin1,can,cw,ch,win, angle, rtime, stripes,color,ledsize,ledcount 
        
    if angle>=360: return
    points=[ (x*cos1-y*sin1, x*sin1+y*cos1) for (x,y) in points ]
    for i in range(ledcount-1):
        seg=can.create_line( points[i][0]+cw/2, ch/2-points[i][1], points[i+1][0]+cw/2, ch/2-points[i+1][1], width=ledsize) 
        cc= color if i in stripes[angle] else ''
        can.itemconfigure( seg,fill=cc) 
    
    angle+= 1    
    win.after(rtime, rotate)    


def rotate2():
    ''' It rotates only a single stripe; not a really good demo, too slow, no POV '''
    global points,cos1,sin1,lsegments,can,cw,ch,win, angle, rtime, stripes,color,ledsize,ledcount 
    
    if not lsegments:
        trpoints=[ (x+cw/2, ch/2-y) for (x,y) in points ] 
        lsegments=[ can.create_line( trpoints[i], trpoints[i+1], fill=color, width=ledsize) for i in range(ledcount-1) ]
    
    if angle>= 360: angle=0
    points=[ (x*cos1-y*sin1, x*sin1+y*cos1) for (x,y) in points ]
    for i,seg in enumerate(lsegments):   
        can.coords( seg, points[i][0]+cw/2, ch/2-points[i][1], points[i+1][0]+cw/2, ch/2-points[i+1][1])
        cc= color if i in stripes[angle] else ''
        can.itemconfigure( seg,fill=cc)
    
    angle+= 1    
    win.after(rtime, rotate2) 




if len(sys.argv)!=2: 
        print("Usage: $ gled.py  xbm_file")
        sys.exit(1)

ledcount= 100   
ledsize= 4
angle=0
rtime=5
color='yellow'

stripes= ledstripe.get_stripes( sys.argv[1], ledcount)    

cw, ch = 2*ledsize*ledcount, 2*ledsize*ledcount     # canvas dimension
sin1, cos1 = sin(pi/180), cos(pi/180)       
points=[ (0+k*ledsize,0) for k in range(ledcount)]  
lsegments=[] # for rotate2()

win= Tk()
can= Canvas( win, width= cw, height= ch, background='black')
can.grid(column=0, row=0)
can.create_rectangle(1,1, cw, ch)

win.after(500,rotate)
#win.after(500,rotate2)
win.title("WPC#34 POV LED DISPLAY")
win.mainloop()

