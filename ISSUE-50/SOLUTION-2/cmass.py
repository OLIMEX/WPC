#!/usr/bin/env python3
#-*- coding:utf-8 -*-

''' 
 2013-12-21 by kantal59
 License: LGPL
 OLIMEX WPC#38: Center of Mass
        A picture is 100×100 pixels and have black object on white background. 
        Make code which calculates the center of mass and display it.
        
        It uses xbm format file as input, you can convert a picture into xbm format with the ImageMagick 'convert' utility:
        $ convert   pic.png   pic.xbm
        The width and size can be different.
        The get_bits() and compute() are 'recycled' from my wpc34 solution :-)
        
        2014-04-11: correction: the 'mass' value must be checked if not zero
'''


import sys


def get_bits( fname):
    ''' It reads an XBM file and returns the size as tuple (width,height) and the bits or 'None' on error '''
    
    fbitmap= open(fname,'r')
    width, height = 0,0

    line= fbitmap.readline()
    while line:
    
        words= line.split()
        
        if '_bits[]' in line:   break; # go to read the pixels
        
        if words[1].endswith('_width'): 
         
            width= int(words[-1])  
        
        else:
            if words[1].endswith('_height'): 
             
                height= int(words[-1])
        
        line= fbitmap.readline()


    if not width or not height:
        print("Input file is not in XBM format")
        return(None)
 
    bits= [  int( s.rstrip('}; \n'),16) for l in fbitmap.readlines() for s in l.split(',') if '0x' in s ]
    
    fbitmap.close()
    return( (width,height), bits)



def compute( size, bits):
    ''' size: xbm picture size (width,height)
        bits: byte list returned by 'get_bits()'
        return: mass,(cx,cy): where cx,cy the mass center coordinates counting from the top left corner
    '''
    width,height = size
    rlb= width//8 if not width%8 else width//8+1   # row length in bytes
   
    mass, cx, cy = 0,0,0
    for row in range( height):
        for col in range( width):
            # get a pixel
            byte= bits[ row*rlb+ col//8 ]
            pixel= (byte >> (col%8)) & 0x01
            if not pixel: continue
            mass+= 1    # each pixel's mass value is 1
            cx+= col    # (col,row) is the pixel's position vector
            cy+= row
            
    if mass:    # 2014-04-11 check added 
        cx, cy = round(cx/mass), round(cy/mass)
    else:    
        cx,cy = 0,0    
            
            
    return( mass, (cx,cy) )                                                      




# TEST
if __name__ =='__main__':

    if len(sys.argv)!=2: 
        print("Usage: $ cmass.py  xbm_file")
        
    else:    
        rslt = get_bits( sys.argv[1])
        if rslt:
            mass, center = compute( *rslt)
            print( " Total mass= {0}\n Centre of the mass (origo is the top left corner): {1}".format( mass, center) )
        


