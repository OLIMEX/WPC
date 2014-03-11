#!/usr/bin/env python
#-*- coding:utf-8 -*-
''' 
 2014-03-09 by kantal59
 License: GPL
 OLIMEX WPC#45: Median Filter
            Median Filter is the simplest way to remove random noise from input signal. 
            More about it you can read at http://en.wikipedia.org/wiki/Median_filter.
            Using the info from the previous Week #44 Challenge, make median filter and 
            experiment with different window sizes to filter the raw ECG info and to see 
            how it changes the shape of the signal and the measurements of the pulse rate.
            
            Tested on: Python 2.7.3 with Tkinter, python-matplotlib 1.1.1, Ubuntu 12.04
'''
import matplotlib.pyplot as plt
#import numpy as np
import sys
import Tkinter as tk
import tkFileDialog as fdlg

#---------------------------
#------- Parameters --------
#---------------------------
ftest="ECGSAMPLE.txt"  # see: EEG-SMT-Packet Format.txt

nch= 6           # number of channels
chwidth= 4       # channel value width, 2 bytes = 4 digits in the input file
ts= 1.0/256      # time sample rate in sec
rs_timing= 0.030 # 30 ms approximate RS timing, 
rs_ticks= int(rs_timing/ts)+1 # approximate axis ticks for RS shape
tolerance= 0.2   # %  deviation from the global min/max value for RS shape preselection; see below

chs=[ [] for i in range(nch) ]  # storage for the channel data, non negative values
filtered_chs= []                # storage for the filtered channel data
heartbeats= []                  # storage for heartbeat values for each channel
filtered_heartbeats= []

filter_window= 6
Error= False

#-------------------------
#------ Read the data ----
#-------------------------
def get_data( fname):
 global chs, filtered_chs, heartbeats, filtered_heartbeats, filter_window
 '''
 Read the data file.
 Input: file name
 Return: True/False on success/failure
 '''
 chs=[ [] for i in range(nch) ]
 filtered_chs= [] 
 heartbeats= [] 
 filtered_heartbeats= []
 filter_window= 6
 
 f= open(fname,'r')
 data= ''.join( f.readlines() )
 f.close()

 start=0
 while True:
    try:
        pktpos= data.index( "A55A",start) + 8   # jump to the data in the packet
    except ValueError:  # catch data.index() not found error
        if not chs[0]:  
            return(False)
        break;
           
    for c in range(nch):
        chs[c].append( data[ pktpos+chwidth*c : pktpos+chwidth*(c+1)] )
        try:
            chs[c][-1]= int( chs[c][-1], 16)
            
        except ValueError:  # catch invalid integer pattern              
            return(False)
        
    start= pktpos+ nch*chwidth
  
 return(True)    

#-------------------------------------------------
#------ Heartbeat calculation---------------------
#-------------------------------------------------
def heartbeat_calc( ch):
    '''   
    Caclulate the heartbeat rate finding the QRS shapes.
    Input: one channel data
    Return: hbeat value
    '''
    globmin, globmax = min(ch), max(ch)     # non negative values
    tlr= tolerance*(globmax-globmin)
    
    mins=[] #  it contains ( sample no., value) tuples
    for i,v in enumerate(ch):
        if mins and (i-mins[-1][0]) <= rs_ticks:        continue
        if (v-globmin) <= tlr:  mins.append( (i,v) )
      
    maxs=[]    
    for i,v in enumerate(ch):
        if maxs and (i-maxs[-1][0]) <= rs_ticks:        continue
        if (globmax-v) <= tlr:  maxs.append( (i,v) )
    
    
    pairs=[]
    while maxs:    
        i,v= maxs.pop(0)
        for (k,w) in mins:
            if  k>i and (k-i) <= rs_ticks:  # a max value followed by a min value
                pairs.append( (i,v,k,w) )
                mins.remove( (k,w))
                break;
    
    hbeat=0
    if len(pairs)>=2:
        average_distance= float((pairs[-1][0] - pairs[0][0] )) /( len(pairs)-1)     # float for python2
        hbeat= int(60/(ts * average_distance))
    
   
    return( hbeat) 


#-------------------------------------------------
#------ Median filtering -------------------------
#-------------------------------------------------
def filtering( ch):  
    global filter_window
    '''
    Applying median filter to one channel datas.
    Input: one channel data
    Return: filtered channel data
    '''
    if filter_window<2: return([])
    middle= filter_window//2
    filtered=[]
    for k in range( len(ch)):
        l= ch[ k:k+filter_window]
        if len(l)< filter_window:      l.extend( [ l[-1] ]*( filter_window - len(l) ) )
        l.sort()
        filtered.append( l[ middle] )

    return( filtered)        


#------------------------------------------
#------------------------------------------
def unfiltered_calculation():
    global heartbeats, chs
    '''
    Heartbeats calculation on unfiltered data.
    Input: all the channels data
    Output: a list of calculated heartbeats
    '''
    heartbeats= [ heartbeat_calc( ch) for ch in chs ]


def filtered_calculation():
    global filtered_heartbeats, chs, filtered_chs
    '''
    Heartbeats calculation on filtered data.
    Input: all the unfiltered channels 
    Output: the filtered channels list and the list of calculated heartbeats
    '''
    filtered_chs= [ filtering( ch) for ch in  chs ]
    filtered_heartbeats= [  heartbeat_calc( ch) for ch in  filtered_chs ]   
        
    
    
def average_hbeat( hbeats):    
    '''
    Average heartbeat calculation from heartbeat list, extreme values ignored
    Input: heartbeat list
    Return: an average hearbeat value
    '''
    hb= [ h for h in hbeats if h>30 and h<200 ]
    return( sum( hb )/ len( hb ) )
 

  
#-------------------------------------------------
#------ Show the data using matplotlib -----------
#-------------------------------------------------
def plotting():   

 global heartbeats, filtered_heartbeats, chs, filtered_chs, filter_window
 
 plt.ion()
 plt.clf()
 fig= plt.figure(1)
 fig.canvas.set_window_title('WPC#45 Heartbeat - Median Filtering')
 fig.suptitle("Sample time 1/256 sec, filter window {0}".format(filter_window) )
 
 for n in range( nch):
    plt.subplot( nch, 1, n+1)
    #t = np.arange(0, len( chs[n]), 1)
    t = [ i for i in range(len(chs[n])) ]
    if not filtered_chs:
        plt.plot(t, chs[n],'blue')
        plt.ylabel('ch'+str(n)+'\nhb='+str(heartbeats[n]), rotation='horizontal' )
    else:
        plt.plot(t, chs[n],'blue', t, filtered_chs[n],'red') 
        plt.ylabel('ch'+str(n)+'\nhb='+str(heartbeats[n]) +'\nfilt.hb='+str(filtered_heartbeats[n]), rotation='horizontal' )
           
    plt.grid(True)
    

 plt.draw()


#----------------------------------------
#--------- Tkinter callbacks ------------
#----------------------------------------
def plot_update():
    global strvWindowSize, filter_window, Error
    
    if Error:   return
    
    fw= int(strvWindowSize.get())
    if fw<2 or fw >100: 
        strvWindowSize.set( str(filter_window) )
        return
        
    filter_window= fw
    strvWindowSize.set( str(fw) )  
    
    filtered_calculation()
    plotting()

#-----------------------------------------
def new_data():
    global strvFileName,filter_window, strvMsg, Error
   
    msg=''; strvMsg.set( msg)
    
    fn=fdlg.askopenfilename(filetypes=[('Allfiles','*.*')])
    if not fn:   return
    try:
        if get_data( fn):   
            Error= False         
            strvFileName.set(fn)
            strvWindowSize.set( str(filter_window) )
            unfiltered_calculation()
            plot_update()
            win.after( 2000, put_top )
            return
        else:
            msg="Invalid file format"
    except:
        msg="File read error"
    
    Error= True
    strvMsg.set( fn+": "+ msg)
    plt.clf()
    
    
    
#-----------------------------------------    
def put_top():  
    global win
    win.lift()
    win.after( 2000, put_top )


#------------------------------
#----- Main with Tkinter ------
#------------------------------
if __name__ == "__main__":

 if not get_data( ftest):
    print(ftest+": Data reading error")
    sys.exit(1)
    
 unfiltered_calculation()
 filtered_calculation()
  
 win=tk.Tk()   
 
 strvWindowSize= tk.StringVar();        strvWindowSize.set( str(filter_window) )
 strvFileName= tk.StringVar();          strvFileName.set( ftest )
 strvMsg= tk.StringVar();               strvMsg.set( "" )
 
 tk.Label(win, text="window size=").grid( row=0, column=0, sticky=tk.E)
 entryWindowSize= tk.Entry(win, textvariable= strvWindowSize, width=5 )
 entryWindowSize.grid(row=0, column=1, sticky=tk.W)
 btnUpdate=tk.Button(win, text='Update', command= plot_update)
 btnUpdate.grid(row=0,column=2)
 
 lblFName= tk.Label(win, textvariable= strvFileName)
 lblFName.grid(row=1, column=0, columnspan=5)
 btnNew=tk.Button(win, text='New data', command= new_data)
 btnNew.grid(row=2,column=2)
 lblMsg= tk.Label(win, textvariable= strvMsg)
 lblMsg.grid(row=3, column=0, columnspan=5)
 
 win.title('Median Filtering' )
 plot_update()
 win.after( 2000, put_top )
 
 win.mainloop()


