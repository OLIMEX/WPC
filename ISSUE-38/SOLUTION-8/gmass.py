#!/usr/bin/env python3
#-*- coding:utf-8 -*-

''' 
 2013-12-21 by kantal59
 License: LGPL
 OLIMEX WPC#38: Center of Mass
        A picture is 100×100 pixels and have black object on white background. 
        Make code which calculates the center of mass and display it.
        
        Demo for cmass.py. 
'''
import sys
import tkinter as tk
import cmass

def anim():
    ''' Animation around the centre of the mass '''
    global delta,center
    
    if delta<5:
        delta+=1
    else:
        delta=1
            
    can.coords( pos, center[0]-delta,center[1]-delta, center[0]+delta+1,center[1]+delta+1)
    win.after( 300,anim)
    
    
#----------- MAIN ------------------
if len(sys.argv)!=2: 
    print("Usage: $ gmass.py  xbm_file")
    sys.exit(1)
        
rslt = cmass.get_bits( sys.argv[1])
if not rslt:    sys.exit(2)

size, bits = rslt
mass, center = cmass.compute( *rslt)
 
 
#----- GRAPHICS    
win= tk.Tk()
can= tk.Canvas( win, width= size[0], height=size[1], bg='white' )

pics= [ tk.BitmapImage( file=sys.argv[1] ) ]    # keeping reference to the bitmap to avoid garbage collection on it
can.create_image( size, image= pics[0], anchor=tk.SE )
can.grid(row=0,column=0) 
lb= tk.Label( win,text=" Image size: {0} x {1}\n Total mass= {2}\n Centre of the mass (origo is the top left corner): {3}".format( size[0],size[1],mass, center) )
lb.grid(row=1,column=0)

pos= can.create_oval( center[0],center[1], center[0],center[1], outline='green')
delta=1
pos= can.create_oval( center[0]-delta,center[1]-delta, center[0]+delta+1,center[1]+delta+1, outline='red')


win.after( 500,anim)
win.title("WPC#38 CENTER OF MASS")
win.mainloop()



    
    
        


