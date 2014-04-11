#!/usr/bin/env python3
#-*- coding:utf-8 -*-

''' 
 2014-04-12 by kantal59
 License: LGPL
 OLIMEX WPC#50: Circle Find
            In window with size 100 x 100 pixels is drawn solid filled circle with 50 pixels diameter at random coordinates X,Y 
            but the circle is completely inside the window. Make code which finds the circle XY coordinates.
            
            XBM image format is used as input.
            The center must be in the rectangle which has (x,y) corner coordinates: 
            (R,R), (width-R-1,R), (R,height-R-1), (width-R-1,height-R-1). 
            A (cx,cy) point of the rectangle treated as center point 
            if (cx,cy), (cx-R,y),(cx+R,y) are black (i.e.: belongs to the circle).
'''

import sys
import cmass


def matrix( size, bits):
    ''' It creates a matrix with size  width x height
        size: xbm picture size (width,height)
        bits: xbm image byte list returned by 'get_bits()'
        return: the matrix 
    '''        
    width,height = size
    
    mat=[ [] for i in range(width) ]
    
    rlb= width//8 if not width%8 else width//8+1   # row length in bytes
   
    for row in range( height):
        for col in range( width):
            # get a pixel
            byte= bits[ row*rlb+ col//8 ]
            pixel= (byte >> (col%8)) & 0x01
            mat[col].append(pixel)

    '''
    # to examine the granularity:
    for y in range(height): 
        for x in range(width):
            print( mat[x][y], end='')
        print('')    
    '''            
    return(mat)
    


def fc( R, dR, matrix):
    ''' Find Circle
        matrix: as returned by 'matrix()'
        R: circle radius
        dR: radius tolerance
        return: (cx,cy) center coordinates of the circle counting from the top left corner or (0,0) on error
    '''
    if R<=0   or   dR <0  :    return( (0,0) )
    R, dR = int(R), int(dR)
    width,height = len( matrix), len( matrix[0])
    
    if width < 2*R or height < 2*R:     return( (0,0) )
    
    # The center must be in the rectangle which has (x,y) corner coordinates (R,R), (width-R-1,R), (R,height-R-1), (width-R-1,height-R-1).
    for r in range(R, R-dR-1,-1):
        for x in range( R, width-R): 
            for y in range( R, height-R): 
                if not matrix[x][y]:    continue    # does not belong to the circle
                if matrix[x-R][y]   and    matrix[x+R][y]:      return( (x,y) )     # check the both ends of a possible diameter
                        
    return( (0,0) ) 




# TEST
if __name__ =='__main__':

    R= 25   # circle radius
    tolerance= 2
    
    if len(sys.argv)!=2: 
        print("Usage: $ fcircle.py  xbm_file")
        
    else:    
        rslt = cmass.get_bits( sys.argv[1])
        if rslt:
            size, bits = rslt
            center= fc(  R, tolerance, matrix( size, bits) )
            print( "Circle center is {0}".format( "not found" if center==(0,0) else center )  )
            
            
            
            
