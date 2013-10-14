#!/usr/bin/env python
#-*- coding:utf-8 -*-

''' 
 2013-10-13 by kantal59
 License: LGPL
 OLIMEX WPC#28: Sudoku
                Make code which solves Sudoku in 3×3 configuration.
                Input:  enter the initial cells which are initialized with start numbers
                Check the input for correctness then print solution(s).
'''

from copy import deepcopy 
import sys

def get_data( fname):
    ''' It reads the data file in. 
        The sudoku matrix contains 9 rows as lists.
    '''
    sd=[]   # the sudoku matrix
    handle= open( fname, "r")
    data= handle.read().splitlines()
    handle.close()
            
    count=0
    for s in data:
        s= [ c for c in s if not c.isspace() ]
        if not s: continue
        if len(s) != 9: 
            print("Line is too long")
            return([])
        for c in s:
            if c not in ['.','1','2','3','4','5','6','7','8','9']:
                print("Invalid character")
                return([]) 
        sd.append( list(s)) # adding a row
        count+=1
        if count==9: break


    for c in  ['1','2','3','4','5','6','7','8','9']: 
    
        for l in sd:
            if l.count(c) > 1:
                print("Repeated integer in row")
                return([])
                
        for l in zip(*sd): # creating a mirrored matrix for column check
            if l.count(c) > 1:
                print("Repeated integer in column")
                return([])
        
    # block check    
    for (x,y) in [ (1,1),(4,1),(7,1), (1,4),(4,4),(7,4), (1,7),(4,7),(7,7) ]: 
    
        block= [ sd[yy][xx] for xx in range(x-1,x+2) for yy in range(y-1,y+2) if sd[yy][xx]!='.'  ]
        if len(block)!=len(set(block)):
            print("Repeated integer in block")
            return([])
     
    ''' The modified sudoku matrix contains tuples ( value, 0) or ( value, -1), 
        where the -1 stands for the fixed values and 0 for the mutuable ones.
    '''        
    nsd= [ [ (0,0) if v=='.' else (int(v),-1) for v in row ] for row in sd ]
    
    return(nsd)                                                   
        


def step( (x,y) ):
    if x==8:
        if y==8:    return( () )
        return( (0,y+1) )
    return( (x+1,y))        
    


def sprint( sud):
    ''' Print the sudoku '''
    for r in range(9): 
        if r%3==0: print(' ')
        s= ''.join( [ '.' if v[0]==0 else str(v[0]) for v in sud[r]] )
        print("  {0}  {1}  {2}".format( s[0:3],s[3:6],s[6:9]) )


def blockn(x,y):
    ''' It calculates the block number(0-8) from the coordinates.'''
    return( ((y//3)*9+x)//3 );
    
    
    
def solve( (x,y), sd):
    ''' The solver '''    
    p= (x,y)
    while p and sd[p[1]][p[0]][1]==-1:    p=step(p)
    if not p: return(sd[:])
    x,y= p
    
    for i in range(1,10):
        
        if i in [ v[0] for v in sd[y] ]: continue   # row check
        if i in [ v[0] for v in [ r[x] for r in sd ] ]: continue    # column check
        block= [ sd[yy][xx] for xx in range(x-2,x+3) for yy in range(y-2,y+3) \
                        if xx>=0 and xx<=8 and yy>=0 and yy<=8 and blockn(xx,yy)==blockn(x,y) ]
        if i in [ v[0] for v in block]: continue
        
        nsd= deepcopy(sd); nsd[y][x]=(i,0)
        pp= step((x,y))
        if pp:  
            nsd= solve( pp, nsd)
        if nsd: return( nsd)
        
    return([])
            



def start( sd):
    return( solve( (0,0),sd ) )
    


#-----------------------------------

fname="puzzle1.sud"
if len(sys.argv)!=2:
    print("\nUsage: $sudoku.py data.sud\n")
else:
    fname=sys.argv[1]    

su= get_data( fname)
print(" The sudoku to be solved ({0}):".format(fname) )
sprint( su)

rslt= start(su)
print("\n A solution:")
sprint(rslt)

        
    



