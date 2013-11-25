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
    
    It works with xbm file which has the same width and height.
'''


import sys
from math import atan2,pi,sqrt


def get_bits( fbitmap):
    ''' It reads an XBM file and returns the size and the bits or 'None' on error '''
    
    fbitmap= open(sys.argv[1],'r')
    size=0

    line= fbitmap.readline().split()
    while line:
        if "width" in line[1]: size= int(line[-1])
        if "height" in line[1]:  
            if int(line[-1]) != size: 
                print("Bitmap width != height")
                return(None)
        if len(line)>3 and "bits" in line[3]: 
            break            
        line= fbitmap.readline().split()

    if not size:
        print("Input file is not in XBM format")
        return(None)
 
    bits= [  int( s.rstrip('}; \n'),16) for l in fbitmap.readlines() for s in l.split(',') if '0x' in s ]
    
    fbitmap.close()
    return( size, bits)



def mk_stripes( size, bits, ledcount):
    ''' size: xbm picture size(width==height)
        bits: byte list returned by 'get_bits()'
        ledcount: number of leds on the stripe
        return: list of stripes for each angle, where a stripe contains the ids of the luminous leds 
    '''
    stripes=[ [] for i in range(0,360) ]
    rlb= size//8 if not size%8 else size//8+1   # row length in bytes

    for row in range( size):
        for col in range( size):
            
            # get a pixel
            byte= bits[ row*rlb+ col//8 ]
            pixel= (byte >> (col%8)) & 0x01
            if not pixel: continue
            
            # calculate the angle
            y= size//2 - row
            x= col - size//2
            grad=0
            
            if y==0:
                if x<=0:  grad=180
            else:
                grad= atan2(y,x)*180/pi
                if grad<0:   grad+=360
                grad= round(grad)
                if grad>= 360: grad=0    
                
            # locate the led on the stripe                
            led= round( sqrt(x*x+y*y) )
            if led < ledcount   and     led not in stripes[grad]:     stripes[ grad].append( led)
                
    return( stripes)                                                      




def get_stripes( fname, ledcount):
    ''' fname: xbm file name
        ledcount: number of leds on the stripe
        return: list of stripes by 'mk_stripes()'
    '''
    rslt = get_bits( fname )
    if not rslt: return([])

    size,bits = rslt
    return( mk_stripes( size, bits, ledcount) )
    


# TEST
if __name__ =='__main__':

    if len(sys.argv)!=2: 
        print("Usage: $ ledstripe.py  xbm_file")
    else:        
        stripes= get_stripes( sys.argv[1], 100)    
        for i,s in enumerate(stripes):  print("{0}: {1}".format(i,s) )
    


