#Framework from http://www.cs.mcgill.ca/~aassaf9/python/algorithm_x.html

#exact_cover(X, Y) converts list X to dictionary X 
#its keys are elements in X and its values are set (list) of keys (in dictionary Y)
#that their values are elements of X
def exact_cover(X, Y):
    X = {i: set() for i in X}
    for i, row in Y.items():
        for j in row:
            X[j].add(i)
    return X, Y
            
#Knuth's Algorithm X
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
#using name toselect() to avoid name conflict in select() i/o function
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
#-----------------------------------------------
#and this is my implementation
def solve_maze(maxi, maxj, blockscell):
    X = []
    Y = {}
    for j in range(0, maxj):
        for i in range(0, maxi):
            if (i, j) not in blockscell:
                X.append((0, (i, j)))
                X.append((1, (i, j)))
            if i+1 < maxi and (i+1, j) not in blockscell and (i, j) not in blockscell: #hor
                X.append((3, (i, j)))
                Y[((i, j), (i+1, j))] = [(0, (i, j)), (1, (i+1, j)), (3, (i, j))]
                Y[((i+1, j), (i, j))] = [(0, (i+1, j)), (1, (i, j)), (3, (i, j))]
                Y[(3, (i, j))] = [(3, (i, j))] #"filler"
            if j + 1 < maxj and (i, j+1) not in blockscell and (i, j) not in blockscell: #ver
                X.append((2, (i, j)))
                Y[((i, j), (i, j+1))] = [(0, (i, j)), (1, (i, j+1)), (2, (i, j))]
                Y[((i, j+1), (i, j))] = [(0, (i, j+1)), (1, (i, j)), (2, (i, j))]
                Y[(2, (i, j))] = [(2, (i, j))] #"filler too"
    X, Y = exact_cover(X, Y)
    for solution in solvex(X, Y, []):
        #solution may not be "chained" or "connected" or "ordered"
        yield solution

# _main_ function
#http://olimex.wordpress.com/2013/11/29/weekend-programming-challenge-issue-35-maze/
blockscell = [(0, 3), (3, 0), (1, 1), (2, 2)]
maxi = 10
maxj = 10
#list blockscell contains coordinate of obstracle(s)
#list blockscell should not contain coordinate exceed (maxi, maxj)
for sol in solve_maze(maxi, maxj, blockscell):
    #print sol #if you want to see
    solstr = dict((x, y) for x, y in sol)
    toseek = (0, 0)
    b = []
    while True:
        a = solstr[toseek] #Big O(1) or O(n)
        b.append((a[0]+1, a[1]+1))
        toseek = a
        if toseek == (0, 0):
            break
    #print only traversing all blank blocks
    if len(b) == (maxi*maxj - len(blockscell)):
        print b
#if solution exists, always two solutions, the same path but forward and backward directions