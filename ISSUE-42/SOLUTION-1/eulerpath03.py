
# eulerPath() adapted from http://code.activestate.com/recipes/498243-finding-eulerian-path-in-undirected-graph/
# but uses dict of dicts instead of dict of lists for representing graph
# hope that del and popitem() is O(1) for dict https://wiki.python.org/moin/TimeComplexity or should doubly linked-list be use
# key of dict means node number
def eulerPath(graph):
    # counting the number of vertices with odd degree
    oddcount = 0
    oddvertix = None
    for x in graph.keys():
        if (len(graph[x]) % 2) == 1:
            oddcount += 1
            oddvertix = x
            if oddcount > 2:
                # Euler path found only at most two odd degree vertices
                return None

    #If graph contains odd vertix, it is start or end of Euler path
    stack = [oddvertix] if oddcount > 0 else [graph.keys()[0]]
    path = []
    
    while stack:
        v = stack[-1]
        if graph[v]:
            u, notused = graph[v].popitem()
            stack.append(u)
            # deleting edge that connects u and v vertices
            del graph[u][v]
            # no need to del graph[v][u] #already deleted by popitem()
        else:
            path.append(stack.pop())
    
    return path

# for testing eulerPath()
#print eulerPath({1:{2:None, 4:0, 5:0, 6:0}, 2:{1:0, (3,3):0, 4:0, 5:0}, (3,3):{2:0, 4:0}, 4:{2:0, (3,3):0, 1:0, 5:0}, 5:{2:0, 6:0, 4:0, 1:0}, 6:{1:0, 5:0}})
#print eulerPath({1:{2:None, 4:0, 5:0}, 2:{1:0, 3:0, 4:0, 5:0}, 3:{2:0, 4:0}, 4:{2:0, 3:0, 1:0, 5:0}, 5:{2:0, 4:0, 1:0}})
#print eulerPath({1:{2:None, 4:0}, 2:{1:0, 3:0, 4:0}, 3:{2:0, 4:0}, 4:{2:0, 3:0, 1:0}})
#print eulerPath({1:{2:0, 4:0, 5:0}, 2:{1:0, 4:0, 5:0}, 4:{2:0, 1:0, 5:0}, 5:{2:0, 4:0, 1:0}})

g2 = [ \
[(2, 1), (1, 2)], \
[(2, 1), (3, 2)], \
[(1, 2), (3, 2)], \
[(1, 2), (1, 3)], \
[(1, 2), (3, 3)], \
[(1, 3), (3, 2)], \
[(1, 3), (3, 3)], \
[(3, 2), (3, 3)], \
[(1, 3), (2, 4)], \
[(2, 4), (3, 3)], \
]
# constructs dict of dicts for eulerPath() from coordinates
g3 = dict()
for a in g2:
    x = a[0]
    y = a[1]
    if x in g3:
        g3[x].setdefault(y)
    else:
        g3[x] = {y:None}
    if y in g3:
        g3[y].setdefault(x)
    else:
        g3[y] = {x:None}
        
print g3 
print "----"
print eulerPath(g3)