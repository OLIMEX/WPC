#!/usr/bin/env python3
#-*- coding:utf-8 -*-
''' 
 2013-12-15 by kantal59
 License: LGPL
 OLIMEX WPC#37: Snake Retro Game
            Make your own snake game!
            Do you remember the Nokia phones Snake game? You move the snake with 4 keys and it eats apples on the screen 
            and gets bigger, collision with walls or snake body ends the game.    
            
            It uses oranges instead of apples:-)
'''

import  tkinter as tk
import tkinter.messagebox as msg
from random import *

# PARAMETERS
ww, hh = 600, 600    # canvas size
sw = 10              # snake/cell segment size
speed = 100          # msec
min_fruits= 10
max_fruits= 50
#min_fruits= 2
#max_fruits= 4

# GLOBALS
mv = {   'Up':    (0,-1, 0,-1), 'KP_Up':    (0,-1, 0,-1) , 
         'Left':  (-1,0,-1,0),  'KP_Left':  (-1,0,-1,0), 
         'Down':  (0,1,0,1),    'KP_Down':  (0,1,0,1),
         'Right': (1,0,1,0),    'KP_Right': (1,0,1,0) }

opposite = [ ('Up','Down'), ('KP_Up','KP_Down'),('Up','KP_Down'), ('Down','KP_Up'), 
            ('Left','Right'), ('KP_Right','KP_Left'), ('Left','KP_Right'), ('Right','KP_Left') ]

direction = 'Up'
timer=None
pause= False
fruit_count=0

# FUNCTIONS

def move():
    global can,snake,direction, timer, fruit_count
       
    direc= mv.get( direction,None)
    if not direc: 
        timer= win.after(speed, move)
        return
    
    if not can.find_withtag('orange'):
        game_over("You won!\n There were {0} fruits.".format(fruit_count) )
        return        
    
    pos = can.coords( snake[0])
    next= direc[0]*sw+pos[0], direc[1]*sw+pos[1], direc[2]*sw+pos[2], direc[3]*sw+pos[3]
    for i in next: 
            if i<0  or  i>=ww  or  i>=hh:
                game_over("Sorry, you lost")
                return
                
    obj= can.find_overlapping( next[0]+1,next[1]+1,next[2]-1,next[3]-1 )
    for o in obj:
        tags= can.gettags(o)
        if 'snake' in tags:
            game_over("Sorry, you lost")
            return
    
        for t in tags:
            if t.startswith('fruit'):
                can.itemconfigure( snake[0], fill='green')
                snake.insert( 0, can.create_oval( next, fill='red', tag='snake') )
                can.delete(t) # e.g.: delete all objects with tag 'fruit12'
                timer= win.after(speed, move)
                return
        
    for i in range(len(snake)):
        tmp= can.coords( snake[i] )
        can.coords( snake[i], *next)
        next=tmp
        
    timer= win.after(speed, move)    
                                    


def dispatch( event):     
     global direction, speed, pause, timer, snake, opposite
     
     key= event.keysym
     if key == 'space' or key ==  'Pause':
        if not pause:
            pause=True
            if timer:
                win.after_cancel(timer)
                timer=None
            return
        pause=False
        timer=win.after(speed,move)   
        return  
      
     if key.upper() == 'N' :
        if timer:
            win.after_cancel(timer)
            timer=None
        start()
        return
        
     
     if key not in mv: return
     if len(snake)>1 and ( (direction,key) in opposite  or  (key,direction) in opposite ) :      return
        
     direction= key
     
     if pause:
        pause=False
        timer=win.after(speed,move)  



def create_apples():
    global ww, hh, sw, fruit_count
    
    seed()
    apples=[]
    
    for i in range( randrange( min_fruits, max_fruits) ):
        pt= randrange(sw,ww-sw,sw), randrange(sw,hh-sw,sw)       
        if pt not in apples: apples.append(pt)
    
    count=0        
    for app in apples:
        fr=can.create_oval( app[0],app[1],app[0]+sw,app[1]+sw,fill="orange", tag="fruit"+str(count) )
        can.addtag_withtag('orange',fr)
        can.create_oval( app[0],app[1],app[0]+sw//2,app[1]+sw//3,fill="green", tag="fruit"+str(count) )
        count+=1
        
    fruit_count= len( apples)    


def game_over( msgstr):
    win.unbind_all("<Key>")
    msg.showinfo("Game over",msgstr)
    start()
    win.bind_all("<Key>", dispatch)
    
    
def start():
    global snake,hh,ww,sw,pause
    
    can.delete("all")
    snake= [ can.create_oval( (ww-sw)//2, (hh-sw)//2, (ww+sw)//2, (hh+sw)//2, fill='red', tag='snake') ]
    create_apples()
    pause=True
     
    

# MAIN

win= tk.Tk()
win.bind_all("<Key>", dispatch)

can= tk.Canvas( win, width= ww, height= hh, background='black')
can.grid(column=0, row=0)

msg.showinfo("Commands",
'''
N: new game\n
Space/Pause: start/pause/continue\n
arrows: change moving direction
''')

start()

win.title("WPC#37 Snake Retro Game")
win.mainloop()


