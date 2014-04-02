#!/usr/bin/env python
#-*- coding:utf-8 -*-
''' 
 2014-03-28 by kantal59
 License: LGPL
 OLIMEX WPC#48: Geometry
            Let have three points A(x,y), B(x,y), C(x,y). Make code which prints if A->B->C sequence makes clockwise, 
            counter clockwise turn, or A,B,C stay in one line. In the attached picture ABC makes counter clockwise turn.
            
            1) - creating the result vector (rx,ry,rz) of the cross product of B-A and C-A vectors; rx,ry are always equal to 0;
            2) - using the sign of the rz to check rotation.
'''

import sys

if len( sys.argv) != 7:

    print("\n Usage: ${0}   ax ay bx by cx cy\n".format( sys.argv[0]) )

else:
    ax, ay = float(sys.argv[1]), float(sys.argv[2])
    bx, by = float(sys.argv[3]), float(sys.argv[4])
    cx, cy = float(sys.argv[5]), float(sys.argv[6])
    
    bax, bay = bx-ax, by-ay
    cax, cay = cx-ax, cy-ay
    
    rz = bax*cay - bay*cax  
    
    print("\n A{0} ---> B{1} ---> C{2}: {3}\n".format( (ax,ay),(bx,by),(cx,cy), 
                                                "in line" if not rz else "clockwise" if rz<0 else "counter clockwise" ) )
                                                
                                                
