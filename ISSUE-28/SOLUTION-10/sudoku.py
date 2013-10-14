#
# /* Copyright (c) 2013 Richard Y. Park */
#


import sys

def blockNumber(j=0,i=0):
  blockDef = [\
    [0,0,0,1,1,1,2,2,2],
    [0,0,0,1,1,1,2,2,2],
    [0,0,0,1,1,1,2,2,2],
    [3,3,3,4,4,4,5,5,5],
    [3,3,3,4,4,4,5,5,5],
    [3,3,3,4,4,4,5,5,5],
    [6,6,6,7,7,7,8,8,8],
    [6,6,6,7,7,7,8,8,8],
    [6,6,6,7,7,7,8,8,8]]
  return blockDef[j][i]


class Sudoku():

  def __init__(self, matrix=None):
    self.reset()
    if matrix:
      self.set(matrix)

  def copyMatrix(self, matrix):
    m=[]
    for j in range(9):
      msub=[]
      for i in range(9):
        msub.append(matrix[j][i])
      m.append(msub)
    self.matrix = m


  def reset(self):
    self.matrix = [\
        [0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0]]

  def resetBanks(self): 
    self.bankRows = [\
        [1,2,3,4,5,6,7,8,9],
        [1,2,3,4,5,6,7,8,9],
        [1,2,3,4,5,6,7,8,9],
        [1,2,3,4,5,6,7,8,9],
        [1,2,3,4,5,6,7,8,9],
        [1,2,3,4,5,6,7,8,9],
        [1,2,3,4,5,6,7,8,9],
        [1,2,3,4,5,6,7,8,9],
        [1,2,3,4,5,6,7,8,9]]
    self.bankCols = [\
        [1,2,3,4,5,6,7,8,9],
        [1,2,3,4,5,6,7,8,9],
        [1,2,3,4,5,6,7,8,9],
        [1,2,3,4,5,6,7,8,9],
        [1,2,3,4,5,6,7,8,9],
        [1,2,3,4,5,6,7,8,9],
        [1,2,3,4,5,6,7,8,9],
        [1,2,3,4,5,6,7,8,9],
        [1,2,3,4,5,6,7,8,9]]
    self.bankBlocks = [\
        [1,2,3,4,5,6,7,8,9],
        [1,2,3,4,5,6,7,8,9],
        [1,2,3,4,5,6,7,8,9],
        [1,2,3,4,5,6,7,8,9],
        [1,2,3,4,5,6,7,8,9],
        [1,2,3,4,5,6,7,8,9],
        [1,2,3,4,5,6,7,8,9],
        [1,2,3,4,5,6,7,8,9],
        [1,2,3,4,5,6,7,8,9]]
    self.bankCells = [\
        [[],[],[],[],[],[],[],[],[]],
        [[],[],[],[],[],[],[],[],[]],
        [[],[],[],[],[],[],[],[],[]],
        [[],[],[],[],[],[],[],[],[]],
        [[],[],[],[],[],[],[],[],[]],
        [[],[],[],[],[],[],[],[],[]],
        [[],[],[],[],[],[],[],[],[]],
        [[],[],[],[],[],[],[],[],[]],
        [[],[],[],[],[],[],[],[],[]]]

  def set(self, S):
    self.copyMatrix(S)
    return self.evaluate()


  def matrixWrite(self, pos, k):
    j,i=pos
    self.matrix[j][i]=k
##########################
  def evaluate(self):
    self.resetBanks()

    for j in range(9):
      s=[]
      for i in range(9):
        sx = self.matrix[j][i]
        if sx in self.bankRows[j]:
          self.bankRows[j].pop(self.bankRows[j].index(sx))

    for i in range(9):
      s=[]
      for j in range(9):
        sx = self.matrix[j][i]
        if sx in self.bankCols[i]:
          self.bankCols[i].pop(self.bankCols[i].index(sx))

    for j in range(9):
      for i in range(9):
        bn = blockNumber(j,i)
        bb = self.matrix[j][i]
        if bb in self.bankBlocks[bn]:
          self.bankBlocks[bn].pop(self.bankBlocks[bn].index(bb))
       

    self.setConflicts()
    #print evaluateMatrix(self.matrix)
    return evaluateMatrix(self.matrix)

##########################
  def getZeros(self):
    zeros=[]
    for j in range(9):
      for i in range(9):
        if not self.matrix[j][i]:
          zeros.append( (j,i) )
    return zeros


#########################
  def solve(self):
    limit = 81
    i=0;
    while( self.solve_loop() ):
      i+=1
      if i > limit:
        print 'loop', i
        break
    if self.evaluate():
      print
      print 'Done :)'
      self.display()
      return True

    print 'bruteforce!'
    s=Sudoku(self.matrix)
    if not s.evaluate():
      s = s.bruteforce(0,0)
    if s:
      print
      print 'Done :)'
      s.display()
      return True

    print 
    print 'No solution :('
    self.display()
    return False

#########################
  def bruteforce(self,j,i):
    #print 'bruteforce', j, i
    if j>8:
      ret = self.evaluate()
      if ret:
        return self
      return False
    if i>8:
      return self.bruteforce(j+1,0)

    ret = self.evaluate()  #evaluateMatrix(self.matrix):
    if ret:
      return self


    # skip if empty
    if not self.bankCells[j][i]:
      #print 'bankCell empty'
      return self.bruteforce(j,i+1)
    else:
      s = Sudoku(self.matrix)
      klist = []
      for k in s.bankCells[j][i]:
        klist.append(k)
      for k in klist:
        #print klist, k
          s.matrix[j][i]=k
          ret = evaluateMatrix(s.matrix)
          if ret:
            return s
          #s.display()
          ret = s.bruteforce(j,i+1)
          if ret:
            return ret
    return False

#########################
  def setConflicts(self):
    zeros = self.getZeros()
    for zero in zeros:
      j,i = zero
      rs = self.bankRows[j]
      cs = self.bankCols[i]
      bs = self.bankBlocks[blockNumber(j,i)]
      
      p=[]
      for x in rs:
        if x in cs:
          p.append(x)
      q=[]
      for x in p:
        if x in bs:
          q.append(x)
      self.bankCells[j][i]=[]
      for qq in q:
        self.bankCells[j][i].append(qq)
    return zeros


######################
  def solve_loop(self):
    zeros = self.setConflicts()
    for zero in zeros:
      j,i = zero
      if len( self.bankCells[j][i] ) == 1:
        self.matrix[j][i]=self.bankCells[j][i][0]
        self.evaluate()
        return True
    return False


###########################
  def display(self):
    for j in range(9):
      if j%3 == 0:
        print '-------------------------'
      for i in range(9):
        if i == 0:
          print '|',
        print self.matrix[j][i],
        if i%3 == 2 and i!=0:
          print '|',
        if i == 8:
          print

    print '---------------------------'
###############

def sum9(L):
  if len(L) != 9: 
    return False
  for i in range(9):
    if (i+1) not in L: 
      return False
  return True

################


# BLOCK
# 0,1,2 # row0
# 3,4,5 # row1
# 6,7,8 # row2
def getBlock(S,n=0):
  if len(S) != 9:
    return []
  if n < 0 or n > 9:
    return []
  c = n%3
  r = n/3
  x = []
  for j in range(3):
    for i in range(3):
      x.append( S[r*3+j][c*3+i] )
  return x

def getCol(S,c=0):
  if len(S) != 9:
    return []
  if c < 0 or c > 9:
    return []
  x=[]
  for i in range(9):
    x.append( S[i][c] )
  return x

def getRow(S,r=0):
  if len(S) != 9:
    return []
  if r < 0 or r > 9:
    return []
  return S[r]



def evaluateMatrix(S):
  for i in range(9):
    if False == sum9(getBlock(S, i)): 
      #print 'getblock false'; 
      return False
    if False == sum9(getRow(S, i)): 
      #print 'getRow false'; 
      return False
    if False == sum9(getCol(S, i)): 
      #print 'getCol false'; 
      return False
  return True


L=[1,2,3,4,5,6,7,8,9]





d_9x9 = [\
    [1,2,3,4,5,6,7,8,9], # row 0 from the top
    [4,5,6,7,8,9,1,2,3], # row 1
    [7,8,9,1,2,3,4,5,6],
    [2,3,4,5,6,7,8,9,1],
    [5,6,7,8,9,1,2,3,4],
    [8,9,1,2,3,4,5,6,7],
    [3,4,5,6,7,8,9,1,2],
    [6,7,8,9,1,2,3,4,5],
    [9,1,2,3,4,5,6,7,8]]

d_9x9_false = [\
    [1,2,3,4,5,6,7,8,9], # row 0 from the top
    [4,5,6,7,8,9,1,2,3], # row 1
    [7,8,9,1,2,3,4,5,6],
    [2,3,4,5,6,7,8,9,1],
    [5,6,7,8,9,1,2,3,4],
    [8,9,1,2,3,4,5,6,7],
    [3,4,5,6,7,8,9,1,2],
    [6,7,8,9,1,2,3,4,5],
    [9,1,2,3,7,5,6,4,8]]

d_9x9_miss = [\
    [0,2,3,4,5,6,7,8,9], # row 0 from the top
    [4,5,6,7,8,9,0,2,3], # row 1
    [7,8,9,0,2,3,4,5,6],
    [2,3,4,5,6,7,8,9,0],
    [5,6,7,8,9,0,2,3,4],
    [8,9,0,2,3,4,5,6,7],
    [3,4,5,6,7,8,9,0,2],
    [6,7,8,9,0,2,3,4,5],
    [9,0,2,3,4,5,6,7,8]]

d_9x9_miss2 = [\
    [1,2,0,4,5,6,7,8,9], # row 0 from the top
    [0,5,0,7,8,9,1,0,3], # row 1
    [0,0,9,1,2,3,0,0,6],
    [2,3,0,0,6,7,0,0,1],
    [5,6,0,0,9,1,0,3,0],
    [0,9,0,2,3,0,5,0,7],
    [3,4,0,6,0,0,9,0,0],
    [0,0,0,9,1,2,3,4,5],
    [0,0,0,0,4,5,6,7,8]]

d_9x9_miss3 = [\
    [1,2,3,4,5,6,0,0,0], # row 0 from the top
    [4,5,6,7,8,9,0,0,0], # row 1
    [7,8,9,1,2,3,0,0,0],
    [2,3,4,5,6,7,0,0,0],
    [5,6,7,8,9,1,0,0,0],
    [8,9,1,2,3,4,0,0,0],
    [0,0,0,0,0,0,0,0,0],
    [0,0,0,0,0,0,0,0,0],
    [0,0,0,0,0,0,0,0,0]]

d_9x9_miss4 = [\
    [0,2,0,0,0,6,0,0,0], # row 0 from the top
    [0,5,0,0,8,0,0,2,3], # row 1
    [0,0,9,0,2,0,4,0,0],
    [2,0,0,0,0,0,0,0,0],
    [0,6,7,0,9,0,2,3,0],
    [0,0,0,0,0,0,0,0,7],
    [0,0,5,0,7,0,9,0,0],
    [6,7,0,0,1,0,0,4,0],
    [0,0,0,3,0,0,0,7,0]]


d_9x9_ex2 = [\
    [0,8,0, 0,0,4, 0,0,0], # row 0 from the top
    [0,2,0, 0,7,0, 0,3,8], # row 1
    [0,0,7, 0,6,0, 2,0,0],

    [5,0,0, 0,0,0, 0,0,0],
    [0,7,6, 0,2,0, 1,8,0],
    [0,0,0, 0,0,0, 0,0,9],

    [0,0,2, 0,8,0, 3,0,0],
    [3,5,0, 0,9,0, 0,7,0],
    [0,0,0, 3,0,0, 0,6,0]]


print '....................'

#s=Sudoku(d_9x9)
#s=Sudoku(d_9x9_false)
s=Sudoku(d_9x9_miss3)
s.solve()
#s=Sudoku(d_9x9_ex2)
#s.solve()
