#!/usr/bin/env python3
#-*- coding:utf-8 -*-
''' 
 2014-01-26 by kantal59
 License: LGPL
 OLIMEX WPC#41: Speed typing test
        Make code which displays text, then measures how fast and correct one would enter this test via the keyboard. 
        You can display random text from online book or dictionary. It’s up to you how to make the user interface, 
        make something funny and interesting.
        
        Using difflib,  urllib and Tkinter. The user interface is not ready yet. Not fully tested.
        You can test it and cheat with copy-and-paste.
'''

import urllib.request 
import difflib as df
import tkinter as tk
import tkinter.font as tkFont
import time


class P:   
    ''' Parameters '''
    tstart=0    # measuring elapsed time
    presscount=0

    # These should have been set on a user interface:
    lines_from= 11      # lines will be read from that position; counting from 1 and not from 0
    nlines= 10          # number of non-empty lines to be read
    ncolumns= 80        # line length
    resource='alice-chapter_I.txt'

    '''
    lines_from=1    
    nlines= 10
    ncolumns=80
    # The 'resource' can be an url, too, but it must be a text file. 
    # The Gutenberg site is great, but after some fast requests, for obvious reasons, it requires a captcha.
    # Don't abuse it, you can use the downloaded files offline.
    resource= 'http://www.gutenberg.org/cache/epub/76/pg76.txt' 
    '''
    
    # for joke:
    animcount=0
    animprop= [ (14,'red'),(15,'green'),( 17,'yellow'),(18,'orange'),(19,'blue'), (20,'pink'),(21,'darkgreen')]
    animfont= None
    animtimer=None
    animimage=None
    

def get_text():
    '''
    It reads the resource in. The resource can be a text file or an url to a text file.
    Empty lines are dropped, long lines are wrapped. Parameters are given in class P.
    '''       
    lines=[]
    url= True
    if  P.resource.startswith('http'):
        handle= urllib.request.urlopen( P.resource)  
    else:
        handle= open(P.resource, 'r')
        url= False
         
    for i in range( P.lines_from-1):  handle.readline() # jump over unrequested lines
    
    extra= ''    # Is there a remaining part of the previous line which had more chars than columns?
    while len(lines) < P.nlines:
        
        if not extra:   
            s= handle.readline()
        else:    
            s= extra
            extra= ''
            
        if not s:   break       # eof? ( empty line read from file should be '\n' )
        if url:     s= s.decode('utf-8')
        if not s.strip():  continue  # empty lines dropped
        s= s.rstrip()
        
        if len(s) >P.ncolumns: # trunk the line at word boundary
            words= s.split()
            s=''
            for i,w in enumerate( words):
                if ( len(s)+len(w)+1 ) > P.ncolumns:      # len(s) + len(w) + len(' ');    
                    extra= ' '.join( words[i:] )
                    break
                s+= w + ' ' 
                    
        lines.append( s )
        
    
    handle.close()
    return( lines)



def check_diff():
    ''' The main algorithm '''
    
    srcText.tag_delete('err');    inpText.tag_delete('err')
    srcText.tag_delete('word');   inpText.tag_delete('word')

    diff= df.ndiff( srcText.get('1.0','end').rstrip(), inpText.get('1.0','end').rstrip() )

    errors= prev= sindex= tindex= 0
    for d in diff:   # '-'/'+' :  missing / additional char in user input
        
        if d[0]=='-': 
            if prev!='+' :    errors+=1         # mistyped characters counted only 1
            srcText.tag_add( 'err', '1.0+'+str(sindex)+'c' )    # marks the missing char
            wi= inpText.index( '1.0+'+str(tindex)+'c' )
            inpText.tag_add( 'word', wi+' wordstart', wi+' wordend')     # marks the incorrect word
            sindex+=1
        else:
            if d[0]=='+':  
                if prev!='-' :  errors+=1       # mistyped characters counted only 1
                inpText.tag_add( 'err', '1.0+'+str(tindex)+'c' )  
                wi= srcText.index( '1.0+'+str(sindex)+'c' )
                srcText.tag_add( 'word', wi+' wordstart', wi+' wordend')
                tindex+=1 
            else:
                 sindex+=1; tindex+=1   
                 
        prev= d[0]                 
    
       
    srcText.tag_configure('err', background='yellow');   inpText.tag_configure('err', background='yellow')
    srcText.tag_configure('word', background='green');   inpText.tag_configure('word', background='green')
    statLabel.config(text='Errors: {0}; Elapsed time: {1} secs; Keypress: {2}'.format(errors, int(time.time()- P.tstart) , P.presscount) ) 
    if errors:
        P.animtimer= inpText.after(1000, animate)
        btnClear.config(command= stop_anim, text='Stop madness!')
    else:
        P.animimage = tk.PhotoImage(file='KDE-dragon.gif')
        inpText.insert('1.0','\n')
        inpText.image_create('1.0', image= P.animimage)   
        inpText.insert('1.0','CONGRATULATION!')


def info_res():
    srcLabel.config( text='Source: {0}; from line {1}'.format(P.resource, P.lines_from) )


def clear():
    srcText.tag_delete('err');    inpText.tag_delete('err')
    srcText.tag_delete('word');   inpText.tag_delete('word')
    inpText.delete('1.0','end')
    statLabel.config(text='Errors:') 
    P.tstart= P.presscount= 0
    if P.animtimer: 
        inpText.after_cancel(P.animtimer)
        P.animtimer=None


def aftermod(event):
    if not P.tstart:   P.tstart= time.time()
    P.presscount+=1
    
    
def animate():
    index= P.animcount%len(P.animprop)
    P.animfont.config(size= P.animprop[ index ][0])
    inpText.tag_configure( 'err', foreground= P.animprop[ index ][1], font= P.animfont )
    inpText.tag_configure( 'word', foreground= P.animprop[ index ][1], font= P.animfont )
    P.animcount+=1
    P.animtimer= inpText.after(200, animate)
    
        
def stop_anim():
    if P.animtimer: 
        inpText.after_cancel(P.animtimer)
        P.animtimer=None
    inpText.tag_configure( 'err', foreground= 'black', font= textfont )
    inpText.tag_configure( 'word', foreground= 'black', font= textfont )  
    btnClear.config( command= clear, text='Clear')     
        
#------------ M A I N -------------

win= tk.Tk()

textfont= tkFont.Font(family='Courier', size=14 )
sysfont= tkFont.Font(family='Times Roman', size=12)
P.animfont= tkFont.Font(family='Courier', size=14, weight='bold' )

srcText= tk.Text(win, height= P.nlines, width= P.ncolumns, font= textfont)
srcText.grid(row=0,column=0, columnspan=3)
inpText= tk.Text(win,height= P.nlines+1, width= P.ncolumns, font= textfont)
inpText.grid(row=1,column=0, columnspan=3)

srcLabel= tk.Label(win,text='', font= sysfont)
srcLabel.grid(row=2,column=0)
statLabel= tk.Label(win,text='', font= sysfont)
statLabel.grid(row=2,column=1)

btnStart= tk.Button(win, text='Check', command= check_diff, font= sysfont)
btnStart.grid(row=3,column=0, sticky=tk.NSEW)
btnClear= tk.Button(win, text='Clear', command= clear, font= sysfont)
btnClear.grid(row=3,column=1, sticky=tk.NSEW)
btnQuit= tk.Button(win, text='Quit', command= win.destroy, font= sysfont)
btnQuit.grid(row=3,column=2, sticky=tk.NSEW)

# get the text from file or url
srclines= get_text()
for l in srclines:    srcText.insert('end', l.rstrip()+'\n')

info_res()

srcText.config(state='disabled')
inpText.bind('<KeyRelease>', aftermod)

P.animprop= P.animprop+P.animprop[::-1]

win.title("WPC#41 Speed Typing Test")
win.mainloop()









