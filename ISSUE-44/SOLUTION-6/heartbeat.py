#!/usr/bin/env python
#-*- coding:utf-8 -*-
''' 
 2014-02-23 by kantal59
 License: LGPL
 OLIMEX WPC#44: ECG heart beat detection
            We all have seen how ECG looks stylized, in real life there is usually lot of noise add to this signal.
            For today’s Challenge I asked one of our employee – Penko to connect himself to EEG-SMT and to stay calm 
            so his ECG signal is captured on file. This file is already upload to GitHub and you can use as input data.
            Make code which detect the heart rate using this raw signal info.
            Description of the data packages is also upload on Github.
            
            
            1) Algorithm: detecting RS shapes positions from max/min values (see: http://en.wikipedia.org/wiki/ECG)
            2) 'matplotlib' must be installed ( http://matplotlib.org/index.html ):
                $ sudo apt-get install python-matplotlib
            3) Tested on Python 2.7.3
'''

from pylab import *
import sys

#---------------------------
#------- Parameters --------
#---------------------------
fdata="ECGSAMPLE.txt"  # see: EEG-SMT-Packet Format.txt

nch= 6           # number of channels
chwidth= 4       # channel value width, 4 bytes
ts= 1.0/256      # time sample rate in sec
rs_timing= 0.030 # 30 ms approximate RS timing, 
rs_ticks= int(rs_timing/ts)+1 # approximate axis ticks for RS shape
tolerance= 0.2   # %  deviation from the global min/max value for RS shape preselection; see below

chs=[ [] for i in range(nch) ]  # storage for the channel data, non negative values


#-------------------------
#------ Read the data ----
#-------------------------
f= open(fdata,'r')
data= ''.join( f.readlines() )
f.close()

start=0
while True:
    try:
        pktpos= data.index( "A55A",start) + 8   # jump to the data in the packet
    except ValueError:  # catch data.index() not found error
        break;
           
    for c in range(nch):
        chs[c].append( data[ pktpos+chwidth*c : pktpos+chwidth*(c+1)] )
        try:
            chs[c][-1]= int( chs[c][-1], 16)
            # other endian:
            #v= chs[c][-1] 
            #v= int( v[2:]+v[0:2], 16)
            #chs[c][-1]= v
        except ValueError:  # catch invalid integer pattern  
            print("Invalid input data")
            sys.exit(1)
        
    start= pktpos+ nch*chwidth
    
#-----------------------------------------    
#---- Caclulate the heartbeat rate -------
#-----------------------------------------
# It finds the QRS shapes

heartbeat=[]

for ch in chs:

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
    
    if(hbeat):   heartbeat.append(hbeat)
        
        
    #print( globmin,globmax,len(mins),len(maxs), len(pairs) )
    print( "heartbeat= {0}  pairs={1}".format(hbeat,pairs) )
    

hbeat= sum( heartbeat )/ len( heartbeat )
print( "Average heartbeat rate: {0}".format(hbeat))
  
#-------------------------------------------------
#------ Show the data using matplotlib pylab -----
#-------------------------------------------------
fig= figure()
fig.canvas.set_window_title('WPC#44 Heartbeat')
fig.suptitle("Sample time 1/256 sec, Average heartbeat rate: {0}".format(hbeat) )


for i,c in enumerate(chs):
    subplot( len(chs), 1, i+1)
    t = arange(0, len(c), 1)
    plot(t, c)
    grid(True)
    ylabel('ch'+str(i))

#savefig("heartbeat.png")
show()

