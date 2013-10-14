from itertools import product

#validatesudoku() returns False if dup digit or not 0-9 found
def validatesudoku(grid): 
    for j in range(9):
        a = []
        for i in range(9):
            m = grid[j][i]
            if m in a or m not in range(0, 10):
                return False
            elif m > 0:
                a.append(m)

    for i in range(9):
        a = []
        for j in range(9):
            m = grid[j][i]
            if m in a or m not in range(0, 10):
                return False
            elif m > 0:
                a.append(m)
                    
    for y in [[0, 1, 2], [3, 4, 5], [6, 7, 8]]:
        for x in [[0, 1, 2], [3, 4, 5], [6, 7, 8]]:
            a = []
            for j in y:
                for i in x:
                    m = grid[j][i]
                    if m in a or m not in range(0, 10):
                        return False
                    elif m > 0:
                        a.append(m)
    return True

def posbl(y, x, grid):
    useddigits = []
    for i in range(9):
        if grid[y][i] > 0:
            useddigits.append(grid[y][i])
        if grid[i][x] > 0:
            useddigits.append(grid[i][x])

    b0 = [0, 1, 2]
    b1 = [3, 4, 5]
    b2 = [6, 7, 8]

    if y in b0:
        y1 = b0
    elif y in b1:
        y1 = b1
    elif y in b2:
        y1 = b2

    if x in b0:
        x1 = b0
    elif x in b1:
        x1 = b1
    elif x in b2:
        x1 = b2
            
    for j in y1:
        for i in x1:
            useddigits.append(grid[j][i])    

    lst = [i for i in range(1, 10) if i not in useddigits]
    return list(lst)

#solve_easy_sudoku() finds cell that has possible only only digit for solving
def solve_easy_sudoku(grid):
    soln = 1 # some value that > 0 (Python no do .. while())
    while soln > 0:
        soln = 0
        blankcell = 0
        for j in range(9):
            for i in range(9):
                if grid[j][i] == 0: # o means blank cell (no digit assigned)
                    #find possible values in blank cell a
                    a = posbl(j, i, grid)
                    if len(a) == 1:
                        soln += 1
                        grid[j][i] = a[0]
                    elif len(a) == 0: #some cell no solution
                        return -1
                    else:
                        blankcell += 1 # it still blankcell
    return blankcell

# solve_hard_sudoku() uses Knuth's Algorithm X
# Framework from http://www.cs.mcgill.ca/~aassaf9/python/algorithm_x.html
# not to reinvent wheel
def solve_hard_sudoku(grid):
    #init X and Y for Sudoku 3x3 problem
    X = ([(0, rc) for rc in product(range(9), range(9))] + \
         [(1, rn) for rn in product(range(9), range(1, 10))] + \
         [(2, cn) for cn in product(range(9), range(1, 10))] + \
         [(3, bn) for bn in product(range(9), range(1, 10))])
    Y = dict()
    for r, c, n in product(range(9), range(9), range(1, 10)):
        b = (r // 3) * 3 + (c // 3) # Box (in Sudoku, not only row and column)
        Y[(r, c, n)] = [ \
            (0, (r, c)), \
            (1, (r, n)), \
            (2, (c, n)), \
            (3, (b, n))]
    X, Y = exact_cover(X, Y)
    #Add values from Sudoku table (grid) to X
    for i, row in enumerate(grid):
        for j, n in enumerate(row):
            if n in range(1, 10):
                toselect(X, Y, (i, j, n))
    #Solve Sudoku problem. Solution may be more than one
    for solution in solvex(X, Y, []):
        #Solution returned in form of (row, column, number)
        #put number to row/column in grid
        for (r, c, n) in solution:
            grid[r][c] = n
        yield grid

#exact_cover(X, Y) converts list X to dictionary X 
#its keys are elements in X and its values are set (list) of keys (in dictionary Y)
#that their values are elements of X
def exact_cover(X, Y):
    X = {i: set() for i in X}
    for i, row in Y.items():
        for j in row:
            X[j].add(i)
    return X, Y
            
#Knuth's Algorithm X used by solve_hard_sudoku() and itself (recursive)
def solvex(X, Y, solution):
    if not X:
        yield list(solution)
    else:
        c = min(X, key=lambda c: len(X[c]))
        for r in list(X[c]):
            solution.append(r)
            cols = toselect(X, Y, r)
            for s in solvex(X, Y, solution):
                yield s
            deselect(X, Y, r, cols)
            solution.pop()

#toselect() used by solvex() and solve_hard_sudoku()
#use name toselect to avoid name conflict in i/o select()
def toselect(X, Y, r):
    cols = []
    for j in Y[r]:
        for i in X[j]:
            for k in Y[i]:
                if k != j:
                    X[k].remove(i)
        cols.append(X.pop(j))
    return cols

#deselect() used by solvex()
def deselect(X, Y, r, cols):
    for j in reversed(Y[r]):
        X[j] = cols.pop()
        for i in X[j]:
            for k in Y[i]:
                if k != j:
                    X[k].add(i)

#stringsudoku() returns "readable" Sudoku grid
def stringsudoku(grid, rowdelim="\n", coldelim=" ", blank="_"):
    rstr = ""
    for i in grid:
        for j in i:
            if j > 0:
                rstr += ("%d" % j)
            else:
                rstr += blank
            rstr += coldelim
        rstr += rowdelim
    return rstr

# http://dingo.sbs.arizona.edu/~sandiway/sudoku/examples.html
grid2 = [ \
    [5, 3, 0, 0, 7, 0, 0, 0, 0],\
    [6, 0, 0, 1, 9, 5, 0, 0, 0],\
    [0, 9, 8, 0, 0, 0, 0, 6, 0],\
    [8, 0, 0, 0, 6, 0, 0, 0, 3],\
    [4, 0, 0, 8, 0, 3, 0, 0, 1],\
    [7, 0, 0, 0, 2, 0, 0, 0, 6],\
    [0, 6, 0, 0, 0, 0, 2, 8, 0],\
    [0, 0, 0, 4, 1, 9, 0, 0, 5],\
    [0, 0, 0, 0, 8, 0, 0, 7, 9]]
    
grid9 = [\
    [0, 2, 0, 0, 0, 0, 0, 0, 0], \
    [0, 0, 0, 6, 0, 0, 0, 0, 3], \
    [0, 7, 4, 0, 8, 0, 0, 0, 0], \
    [0, 0, 0, 0, 0, 3, 0, 0, 2], \
    [0, 8, 0, 0, 4, 0, 0, 1, 0], \
    [6, 0, 0, 5, 0, 0, 0, 0, 0], \
    [0, 0, 0, 0, 1, 0, 7, 8, 0], \
    [5, 0, 0, 0, 0, 9, 0, 0, 0], \
    [0, 0, 0, 0, 0, 0, 0, 4, 0]]
    
grid3 = [\
    [0, 0, 0, 2, 6, 0, 7, 0, 1], \
    [6, 8, 0, 0, 7, 0, 0, 9, 0], \
    [1, 9, 0, 0, 0, 4, 5, 0, 0], \
    [8, 2, 0, 1, 0, 0, 0, 4, 0], \
    [0, 0, 4, 6, 0, 2, 9, 0, 0], \
    [0, 5, 0, 0, 0, 3, 0, 2, 8], \
    [0, 0, 9, 3, 0, 0, 0, 7, 4], \
    [0, 4, 0, 0, 5, 0, 0, 3, 6], \
    [7, 0, 3, 0, 1, 8, 0, 0, 0]]     

def printsolvesudoku(grid):
    print stringsudoku(grid)
    if not validatesudoku(grid):
        print "Invalid Sudoku puzzle"
        exit()
    print "Solution ----------------"
    n = solve_easy_sudoku(grid)
    if n == 0:
        print stringsudoku(grid)
    elif n < 0:
        print "No solution"
    else:
        for solution in solve_hard_sudoku(grid):
            print stringsudoku(solution)
    print "-------------------------"


#example use
grid = grid3
printsolvesudoku(grid)

# sudoku.txt from http://projecteuler.net/project/sudoku.txt
# via http://olimex.wordpress.com/2013/10/11/weekend-programming-challenge-week-28-sudoku-solver/#comment-9715
#grids = [line.strip() for line in open("sudoku.txt", 'r')]

lineno = 0
gridlist = [[],[],[],[],[],[],[],[],[]]
with open('sudoku.txt') as sudokugrids:
    for line in sudokugrids:
        if lineno != 0:
            #print "%d %s" % (lineno, line.strip())
            gridlist[lineno - 1] = [int(c) for c in line.strip()]
        if lineno == 9:
            lineno = 0
            #print gridlist
            printsolvesudoku(gridlist)
        else:
            lineno += 1