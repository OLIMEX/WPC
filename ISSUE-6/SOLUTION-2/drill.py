#! /usr/bin/env python
# -*- coding: utf-8 -*-

'''
 2013-04-28 by kantal59
 License: LGPL
 OLIMEX WPC#6:
    PCB CNC drill machine path optimizer    
    
 The simplest "nearest neighbour" algorithm is applied. I use integer arithmetic.
'''
from os import sys
from math import sqrt

'''
 readData(fn): It reads the drill data from a file
    input: fn - name of the data file
    return: ( s, dmstr) - 's' is set of the ordered points where each of them a tuple (x,y), 'dmstr' is the drill diameter string
'''
def readData( fn):
    sc=1000.0               # scale for converting 3.3 fixed point number to 6 digits integer 
    maxdim=(999999,999999)  # 999.999; 
    maxdiameter= 9900       # 9.9
    
    fdata= open( fn,"r")
    lc=0   
    s=set()
    dmstring=""
    diameter= None
    err= False
    for line in fdata: 
        lc+=1
        lin= line.strip().upper() 
        if lin=="":
            continue
        if lin[0]=='T':
            diameter= int( lin[1:])*100     # scale!
            if diameter<=0 or diameter > maxdiameter:
                print("Invalid diameter: "+lin)
                err=True
                break
            diameter2= diameter*diameter    
            radius=  diameter/2.0    
            dmstring= lin
            continue
        if not diameter:
            print("Missing diameter value!")
            err=True
            break
        if lin[0]!="X" or lin[7]!="Y":
            print("Syntax error: line {0}, {1}".format(lc,lin) )
            err=True
            break
        x= int(lin[1:7])  
        y= int(lin[8:])
        if x<0 or x>maxdim[0] or y<0 or y>maxdim[1]:
            print("The hole center is out of board: line {0}, {1}".format(lc,lin) )
            err=True
            break
        if x-radius < 0 or x+radius > maxdim[0] or y-radius < 0 or  y+radius > maxdim[1]:
            print("The hole radius extends the border dimension: line {0}, {1}".format(lc,lin) )
            err=True
            break
        if (x,y) in s:
            print("Duplication omitted, {0}".format(lin))
            continue  
        overlap= False      
        for h in s:
            if ((x-h[0])*(x-h[0]) + (y-h[1])*(y-h[1])) < diameter2 :
                print("Hole overlapping, {0}, {1}, diameter={2}".format( (h[0]/sc,h[1]/sc), (x/sc,y/sc), diameter/sc))
                overlap= True
                break
        if overlap:
            err=True
            break            
        s.add( (x,y) )
        
    fdata.close()  
    if err:
        s.clear();  
    return( (s, dmstring) ) 

'''
    writeData( fn, points, dmstr ): It writes the drill data into a file 
    input: fn - the name of the output file
           points - the list of point coordinate tuples (x,y) 
           dmstr - the drill diameter string
'''
def writeData( fn, points, dmstr ):    
    f=open(fn,"w")
    f.write(dmstr+"\n")
    for pos in points:
        f.write("X{0:06d}Y{1:06d}\n".format( pos[0],pos[1]) )
    f.close()                        


'''
    dist2(a,b): It calculates the distance*distance value for the a(x,y) and b(x,y) points
'''
def dist2(a,b):
    return((a[0]-b[0])*(a[0]-b[0]) + (a[1]-b[1])*(a[1]-b[1]))

'''
    pathLength( points): It calculates the length of the resulted path.
    input: points - the list of point coordinate tuples (x,y)
    return: path value
'''
def pathLength( points):
    if  not points:
        return(0)
    path= sqrt( dist2((0,0),points[0]) ) + sqrt( dist2((0,0),points[-1]) )
        
    for p in range(0,len(points)-1):
        dx= points[p][0]-points[p+1][0]
        dy= points[p][1]-points[p+1][1]
        path+= sqrt( dx*dx+dy*dy )
        
    return( path)        


'''
    NN(points): The Nearest Neighbour algorithm for TSP
    input: points - the list of point coordinate tuples (x,y)
    return: rslt - the ordered list of point tuples (x,y)
'''
def NN( points):    
    rslt=[]
    pos=(0,0)    
    while points:
        nd= -1
        for p in points:
            d= dist2( p,pos)
            if nd== -1 or d < nd :
                nd= d
                npos= p
        points.remove( npos)
        rslt.append( npos)
    return(rslt)     

#------------------------------
#       T E S T I N G
#------------------------------ 

if len(sys.argv)!=2:
    print("\nUsage: $> drill.py  drill_file\n")
    fn= "drill.txt"
else:    
    fn= sys.argv[1]
    
    ( points, dmstr) = list( readData( fn))
    
    if points:
        points = NN( points)
    
        fout= "output.txt"
        writeData( fout, points, dmstr )
    
        print( "Output file '{0}' is written.\nNumber of points: {1}.\nPath length: {2}".format( fout, len(points), pathLength(points)/1000.0 ) )
        
    
    
