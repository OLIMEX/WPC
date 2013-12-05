#!/usr/bin/env python3
#-*- coding:utf-8 -*-

'''
 2013-12-01 by kantal59
 License: LGPL
 OLIMEX WPC#35: Maze
         Maze with 10×10 cells have obstracles placed on random cells marked with the black. 
         Make code which finds path which starts from cell (1,1) and moves through all Maze cells 
         and returns back to cell(1,1) without stepping on same cell more than once.
        
         There is no great idea in the code, it tries the cells step by step.
         No input interface, the test data are embeded.
'''

    
# ----- INPUT ------
'''
MSIZE=3
OB= [(2,2)]
'''
'''
MSIZE=3
OB=[(3,1),(3,2),(3,3),(2,3),(1,3) ]
'''
'''
MSIZE=3
OB=[(2,2),(2,3),(3,2) ]
'''

MSIZE=10
OB=[ (x,y) for x in range(3,9) for y in range(3,9) ]

'''
MSIZE=4
OB=[]
'''
'''
MSIZE=5
OB=[ (x,y) for x in range(2,5) for y in range(2,5) ]
'''

'''
MSIZE=10
OB=[ (x,y) for x in range(2,10) for y in range(2,10) ]
'''

'''
MSIZE=10
OB=[ (x,y) for x in range(1,11) for y in range(1,11)]
OB.remove((1,1))
OB.remove((1,2))
OB.remove((2,1))
OB.remove((2,2))
'''

'''
# It will run forever :-)
MSIZE=10
OB= [ (8,2),(2,3),(5,5),(3,8),(8,8),(5,10)] # obstacles
'''
#------------------


Path=[]

def inside( p):
    ''' Check if p inside the matrix'''
    global MSIZE,OB
    return( p[0]>=1 and p[0]<= MSIZE and p[1]>=1 and p[1]<= MSIZE )   



def data_check():
    ''' Data validity check'''
    global MSIZE,OB
    
    if (MSIZE*MSIZE-len(OB)) % 2:
        print("\nOdd number of free cells, there is no solution\n")
        return( False)
     
    for p in OB:
        if not inside( p):
            print("\n{0} obstacle is out of the matrix!\n".format(p))
            return(False)
    
    if (1,1) in OB:
        print("\nStart point (1,1) is an obstacle!\n")
        return(False)    
        
    if (2,1) in OB or (1,2) in OB:
        print("\n Start point (1,1) is blocked!\n")
        return(False)        
        
    return(True)                  



def find_path():
        global MSIZE,OB,L,Path
               
        p=Path[-1]
        for delta in [ (1,0),(0,1),(-1,0),(0,-1) ]:   
        
            next = p[0]+delta[0], p[1]+delta[1]
            if next == (1,2):
                if len(Path) == L:  return( True )
                continue
            
            if not inside( next)  or  next in OB  or  next in Path:  continue  
            
            Path.append(next)                            
            if find_path(): return(True)  
            Path.pop()
        
        
        return(False)



def start():
    global MSIZE,OB,L,Path
    
    L= MSIZE*MSIZE-len(OB)
    Path.append((1,2))
    Path.append((1,1))
    Path.append((2,1))
    if( find_path() ):
        del Path[0]
        Path.append((1,2))
        Path.append((1,1))
        return(True)
    else:
        return(False)



# Let's go!    
if( data_check() and start()):    
    
    print( Path)
    
else:
    print("Path not found")        

                
       
        
    

