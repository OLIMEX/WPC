'''
 Input data for wpc25 problem

 M: matrix size;  the matrix bottom left corner positioned to (0,0)
 PA: start point
 PB: destination point
 C: obstacles
 L: required path length
 
 The last uncommented parameter will be used.
'''

'''
MSIZE= 3,3
PA= 0,0
PB=2,2
C= []    # no obstackles
L= 3
'''

'''
MSIZE= 3,3
PA= 0,0
PB=2,2
C= [ (1,1) ]
L= 3
'''

'''
MSIZE= 3,3
PA= 0,0
PB=2,2
C= [ (2,0)]
L= 3
'''

'''
MSIZE= 3,3
PA= 0,0
PB=2,2
C= [ (1,1),(2,0)]
L= 3
'''

'''
# The 'wall'
MSIZE= 4,4
PA= 1,1
PB= 3,3
C= [ (2,0), (2,1), (2,2), (2,3) ]
L= 3
'''

'''
# The 'glass'
MSIZE= 4,4
PA= 1,1
PB= 3,3
C= [ (2,3),(3,2) ]
L= 3
'''


# 'Snakes' 
# paths: 2
MSIZE= 6,5
PA= 2,2
PB= 4,1
C= [(1,1),(2,3),(3,1),(3,2),(4,0),(4,4),(0,4)]
L= 14


'''
# The 'neighbours'
MSIZE= 4,4
PA= 1,1
PB= 2,2
C= [ ]
L= 3
'''







