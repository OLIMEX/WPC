#! /usr/bin/env python3
# -*- coding: utf-8 -*-

''' 
 2013-06-02 by kantal59
 License: LGPL

 OLIMEX WPC#11:
    Let’s have a maze with size X x Y where X and Y are integer (3..100) .
    The maze is defined with strings, where in the string ‘W’ is wall, ‘@’ is obstacle and ‘ ‘ is air.
    Make code which finds the largest by area connected obstacles in the maze.
        
 Python3 required.
 Counting the '@' which are neighbours. Input will be read from file, which must contain SPACES instead of TABS, or using test data.
 The main algorithm consist of 8 lines of code, the rest is just glitter.
 For graphics demo (with fixed canvas size), the 'GUI' must be set to True. The 'tkinter' module required.  
'''

#GUI= False
GUI= True

from os import sys

#---------------------------------
#         THE ALGORITHM
#---------------------------------
def neighbours( obi, obstacles ):
    ''' The algorithm.
    '''                    
    yield obi
    nb= [ (x,y) for (x,y) in obstacles if (x,y) in [ (obi[0]+i, obi[1]+j) for i in range(-1,2) for j in range(-1,2) ] ]
    for p in nb:
        obstacles.remove(p)
    for p in nb:
        # neighbours( p, obstacles) <-- yielded values of recursive generator must be propagated explicitly 
        for others in neighbours( p, obstacles): 
            yield others

#----------------------------------
#        DATA READING
#----------------------------------
def load_data( fname, obstacles):
    ''' Input
    '''
    row=0
    fd=open(fname,'r')
    for line in fd:    
        
        pos= line.find('@')
        while pos!=-1:
            obstacles.append( (row,pos) )
            #---- graphics begins
            if GUI: 
                chgcolor( (row,pos), "red")
            #---- graphics ends
            pos= line.find('@',pos+1)
            
        #---- graphics begins
        if GUI:
            line=line.upper()
            pos= line.find('W')    
            while pos!=-1:
                chgcolor( (row,pos), "black")
                pos= line.find('W',pos+1)
        #---- graphics ends
        row+=1
    fd.close()                    
 
#---------------------------------- 
#           GRAPHICS
#----------------------------------       
if GUI:
    from tkinter import *
    from tkinter import ttk
    scell=10; xmaze=300; ymaze=300; title='OLIMEX WPC#11' 
    it=None
    
    def chgcolor( t, color):
        oid= can.find_closest( t[1]*scell, t[0]*scell)
        can.itemconfigure( oid, fill=color  )
 
        
    def step( points,bls,mx):
        global it
        if it==None:
            it=iter(points)
        try:
            chgcolor( next(it),"green")
            win.after( 500, step, points,bls,mx)
        except  StopIteration:
            win.title( title+" ---> the largest block size: {0}".format(mx))
            for b in bls:
                if len(b)==mx:
                    for p in b:
                        chgcolor( p,"yellow")                                   
        
        
    win= Tk()
    hsc = ttk.Scrollbar(win, orient=HORIZONTAL)
    vsc = ttk.Scrollbar(win, orient=VERTICAL)
    can= Canvas( win, width=500, height=400, scrollregion=(0, 0, scell*ymaze, scell*xmaze), bg='gray', yscrollcommand=vsc.set, xscrollcommand=hsc.set )  
    hsc['command'] = can.xview
    vsc['command'] = can.yview

    can.grid(column=0, row=0, sticky=(N,W,E,S))
    hsc.grid(column=0, row=1, sticky=(W,E))
    vsc.grid(column=1, row=0, sticky=(N,S))

    ttk.Sizegrip(win).grid(column=1, row=1, sticky=(S,E))
    win.grid_columnconfigure(0, weight=1)
    win.grid_rowconfigure(0, weight=1)

    for i in range(0,xmaze):
        x=i*scell
        for j in range(0,ymaze):
            y=j*scell   
            can.create_rectangle( x,y, x+scell, y+scell) 
               
    win.title(title)
    
        
#----------------------------------
#            TESTING
#----------------------------------
def main():
    ''' Test
    '''
    #--- Input
    stones=[]
    if len(sys.argv)!=2:
        print("\nUsage: $> obstacles.py  maze_file\n- using test data:\n")
        stones= [ (3,3),(3,4),(4,2),(4,3),(5,7),(6,1),(6,6),(6,7) ]
        #stones= [ (3,3),(3,4),(4,2),(4,3),(5,7),(6,1),(6,6),(6,7), (4,4),(4,5),(4,6),(3,6) ]
        #---- graphics begins
        if GUI:
            for p in stones:
                chgcolor( p, "red")
        #---- graphics ends
    else:
        print("- using the file: {0}".format(sys.argv[1]))
        load_data( sys.argv[1], stones)
        
    #--- Calculation    
    blocks=[]
    while stones:
       p=stones.pop()
       blocks.append( [ a for a in neighbours( p, stones) ] )
    
    #--- Output   
    l=0
    for a in blocks:
        if len(a) > l:
            l=len(a)
        print("size: {0} -->{1}".format( len(a),a))

    print("The largest size: {0}".format(l) )
    #---- graphics begins
    if GUI:
        pnts=[ p for bl in blocks for p in bl ]    
        win.after( 1000, step, pnts, blocks, l)
    #---- graphics ends
   

# LET'S GO !
if GUI:
    #---- graphics begins
    win.after( 100, main)
    win.mainloop()
    #---- graphics ends
else:
    main()
    



