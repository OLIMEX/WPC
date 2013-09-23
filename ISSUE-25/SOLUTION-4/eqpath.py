#!/usr/bin/env python3
#-*- coding:utf-8 -*-

'''
 2013-09-22 by kantal59
 License: LGPL
 OLIMEX WPC#25: Equal Travel Paths
        If we have matrix with size M x N and two points A(xa,ya) and B(xb,yb), C obstacles which are entered with their coordinates 
        and length of path L, make code which:
        - displays all variants (if any) one can move from point A to point B by traveling via L cells;
        - you can step on one cell just once and only if the cell have no obstacle;
        - the valid moves are only up-down-left-right.             
        
        inputs: the matrix size M and N;
                the points A(x,y) and B(x,y) coordinates;
                the number of obstacles;
                the obstacles C(x,y) coordinates;
                the path length L.

 Input data file: wp25data.py
'''

import sys

def get_data():
    ''' Get the input data '''
    
    import wp25data 
    try:
        wp25data.MSIZE, wp25data.PA, wp25data.PB, wp25data.L, wp25data.C
    except AttributeError as err:
        print("\n Input error: {0}\n".format(err) )
        print(" wp25data.py syntax:\n\tmatrix size: MSIZE= n,m [the matrix bottom left corner positioned to (0,0)]\n\tstart point: PA= x,y\n\tdestination point: PB= x,y\n\trequired path: L= n\n\tobstacles: C= [ (x1,y1), (x2,y2), ...]\n")
        sys.exit(1)
        
    return( (wp25data.MSIZE, wp25data.PA, wp25data.PB, wp25data.L, wp25data.C) )    
    


def dist( p,q):
    ''' Distance between two point measured in 'cell' '''
    if p==q: return(0)
    return( abs(q[0]-p[0])+abs(q[1]-p[1])-1)

def add(p,q):
    ''' Moving from p to p+q '''
    return( (p[0]+q[0],p[1]+q[1]) )
    
def inside( p, smatr):
    ''' Check if p inside the matrix'''
    return( p[0]>=0 and p[0]< smatr[0] and p[1]>=0 and p[1]< smatr[1] )   



def data_check( dat ):
    ''' Data validity check'''
    
    MSIZE, PA, PB, L, C = dat
    
    if PA==PB:
        print("\n The start and destination are the same.\n")
        return(False)
    
    for p in C:
        if not inside( p, MSIZE):
            print("\nObstacle is out of the matrix\n")
            return(False)
    
    for p in [ PA,PB ]:
        if not inside( p, MSIZE):
            print("\nStart or destination is out of the matrix\n")
            return(False)
        if p in C:
            print("\nStart or destination obstacle collision\n")
            return(False)    
            
    if  dist(PA,PB)  > L:
        print("\nL is too short!\n")
        return(False)
        
    if  (MSIZE[0]*MSIZE[1]-2-len(C) ) < L:
        print("\nL is too large!\n")
        return(False)
            
    return(True)            
      



def find_path( length, params, path):
       ''' It extends the path 'path' with path of length 'length' using parameters 'params'. 
       PA and PB are not stored in the path. It is a generator.''' 
       MSIZE, PA, PB, L, C = params
       
       start= PA if not path else path[-1]
       for delta in [ (1,0),(-1,0),(0,1),(0,-1) ]:   # right,left,up,down
        
            p= add( start, delta)
            if p == PB:
                if length == 0:  yield path[:]
                continue
            
            if p==PA  or  not inside( p, MSIZE)  or  p in C  or  p in path  or  dist(p,PB)>= length :   continue  
            # find_path( length-1, params, path[:]+[p])  
            for pth in find_path( length-1, params, path[:]+[p]):  yield pth    # recursive generator
        



if __name__=='__main__':

    data= get_data()
    
    MSIZE, PA, PB, L, C = data
    rslt=[]
    
    if( data_check( data) ): 
    
        count=0
        try:
        
            for pth in find_path( L, data, []):  
                count+=1;   pth.insert(0,PA);   pth.append(PB);      print( pth)
                
        except KeyboardInterrupt:
            print("\nInterrupted. The number of listed paths of length {0} with {1} obstackles: {2}\n".format(L, len(C), count))
        else:    
            print("The number of paths of length {0} with {1} obstackles: {2}\n".format(L, len(C), count))    
       
        
    

