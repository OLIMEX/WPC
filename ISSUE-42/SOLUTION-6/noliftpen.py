#!/usr/bin/env python3
#-*- coding:utf-8 -*-
''' 
 2014-02-09 by kantal59
 License: GPL
 OLIMEX WPC#42: No-Lift-Pen Drawings
            We all know this game where you draw figure on paper without lifting up your pen and 
            without going through same segment twice.
            Write code which enters N segments with their coordinates X1,Y1,X2,Y2 then check if it’s 
            possible to draw all segments without lifting your pen and if YES write the path sequence.
            
 Solution:  It is allowed that two segments cross each other, but the crossing doesn't form a node, 
            the pen must not turn here.
            If there are nodes with odd number of connected segments, the problem is solvable only if the 
            count of such nodes are 2, and these must be the start and end node of the drawing.
'''
import sys


def remove_duplicates( fig):
    '''It removes duplicated segments.'''
    l=[]
    for s in fig:
        if s not in l   and   (s[2],s[3],s[0],s[1]) not in l:       l.append( s)
    
    return(l)    



def check_parity( fig):
    ''' It returns a list of nodes having odd number of segments. '''
    d=dict()
    for s in fig:
        p1, p2 = (s[0],s[1]), (s[2],s[3])
        d[ p1]= d.get( p1,0) +1
        d[ p2]= d.get( p2,0) +1
        
    l=[ p for p in d if d[p]%2 ]        
    if not l:   return( [] )
    return(l)
 
  

def is_connected( s1,s2):
    ''' It checks if s1,s2 segments are connected.
        NOTE: The argument processesing is ASYMETRIC as the direction matters!
    '''
    if (s1[2]==s2[0]  and  s1[3]==s2[1]):    return( s2)
    if (s1[2]==s2[2]  and  s1[3]==s2[3]):    return( (s2[2],s2[3],s2[0],s2[1]) )
    return(None)



def drawing( figure,path):
    '''The main algorithm: it creates the no-lift-pen path.
       Input: figure:   segment list;
              path:     segment list forming the path to be extended, it must be initialized to
                        the start segment. 
    '''
    if not figure: return(True)
    fig= figure[:]
    ls= path[-1]    # last segment in the path
    lsconn= [ s for s in fig if is_connected(ls,s) ]
    for ns in lsconn:
        
        fig.remove(ns)
        path.append( is_connected(ls,ns) )  # is_connected() reverses the segment's end points if needed (direction matters)
        
        if drawing( fig,path):  return(True)
        fig.append( ns)
        path.pop()  # path contains ns or the reversed ns
        
    return(False)        
    



def go( fig):
    ''' Processing. It returns (message, path) .'''
    path=[]
    fig= remove_duplicates(fig)
    if not fig:     return( 'Empty figure',[]) 
    
    odd_nodes= check_parity(fig)
    pari= len(odd_nodes)
    if pari!=0 and pari!=2:   return( 'Parity problem',[]) 
    
    if pari==0:    path.append( fig.pop(0))   # any segment can be as start one
    else:    
        pstart= odd_nodes[0]
        for s in fig:        # the start segment must contain one of the nodes having odd number of connected segments
            if (s[0],s[1]) == pstart : 
                fig.remove(s) 
                path.append(s)
                break
            if (s[2],s[3]) == pstart :
                fig.remove(s)
                path.append( (s[2],s[3],s[0],s[1]) )
                break
      
    fig_saved= fig[:]
    seg_start= path[0]
    path_saved= [ (seg_start[2],seg_start[3],seg_start[0],seg_start[1]) ]
    
    if drawing( fig,path):  
        return('Drawing completed', path)
    
    return('Unsuccessfull',[])

    


if __name__ =='__main__':

    figure1= ( [ (0,0,10,0), (0,0,8,10), (0,10,8,10) ], 'fig1: given in the problem, solution exists' )
    figure2= ( [ (0,0,0,10), (0,10,9,10), (0,10,5,13), (5,13,9,11), (0,0,9,0), (9,0,9,10) ], 'fig2: given in the problem, solution exists' )
    figure3= ( [ (0,0,0,9), (0,0,10,0), (0,9,10,9), (10,0,10,9), (10,0,13,5), (13,5,10,9), (10,5,13,5)], "fig3: solution doesn't exist")

    test1= ( [ (0,0,10,10) ], 'single segment, solution exists')
    test2= ( [ (0,0,10,10), (1,1,11,11) ], "separate segments, solution doesn't exist")
    test3= ( [ (0,0,0,1), (0,1,1,1), (1,1,1,0), (1,0,0,0)],"square")
    test4= ( [ (0,0,0,1), (0,1,1,1), (1,1,1,0), (1,0,0,0), (10,10,20,20) ], "square + separate segment")
    test5= ( [ (0,0,0,1), (0,1,1,1), (1,1,1,0), (1,0,0,0), (10,0,10,1), (10,1,11,1), (11,1,11,0), (11,0,10,0)], "separate segments, solution doesn't exist")
    test6= ( [ (0,10,0,0), (15,15,0,10) ], "direction test, solution exists")
    test7= ( [ (0,5,0,3), (18,0,18,5), (16,1,18,5), (4,0,18,0), (5,5,16,1), 
               (4,0,4,3), (5,5,0,5), (0,3,4,3), (5,5,5,1), (16,1,5,1) ], "unordered listing, solution exists")
    test8= ( [ (0,0,1,1),(0,0,1,-1),(0,0,1,0),(1,0,2,0),(1,1,1,0),(1,-1,1,0),(1,1,2,0),(1,-1,2,0),(1,1,3,0),(1,-1,3,0) ], "test8" )            
    
    #msg,path= go( test4[0]); print( path)

    for fig in [ figure1, figure2, figure3, test1, test2, test3, test4, test5, test6, test7, test8]:
        msg, path= go( fig[0])
        print("Input: {0}\nComment: {1}\nResult message: {2}\nPath: {3}\n".format( fig[0],fig[1],msg,path) )
        
        
        
