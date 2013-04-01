#!/usr/bin/env python

#sort list of integers [a,b,c,d] so that (a - b) <= (b - c) <= (c - d)
def sortdiff(integers, sortedlist=[], verbose=False):
    #print each recusive step for debugging and visualization
    if verbose:
        print sortedlist, ', ', integers
    #no more integers left -> we found a solution and return it!!
    if len(integers) == 0:
        return sortedlist
    if len(sortedlist) < 2:
        #not enough integers in list yet to subtract
        beginning = True
    else:
        #subtract last to integers in list
        beginning = False
        a = sortedlist[-2]
        b = sortedlist[-1]
        d = a - b
    #try every remaining integer as possible next one in list
    for i in range(0,len(integers)):
        c = integers[i]
        #put c in sortedlist only if it satisfies the condition
        #condition here is <, could be <= 
        if beginning or (d < (b - c)):
            #build new array of remaining integers
            remaining_ints = integers[:]
            del(remaining_ints[i])
            #enter recursion
            solution = sortdiff(remaining_ints,sortedlist[:]+[c])    
            #if a solution was found stop searching
            if solution:
                ## if you want to see all solutions use "print solution" instead of return
                return solution
    #no solution found, return empty list
    return []

#print differences of neighbors to check solution
def print_diffs(integers):
    for i in range(0,len(integers)-1):
        print (integers[i] - integers[i+1]), ', ',

#time exection of sortdiff
def timed_sortdiff(integers,sortedlist=[],verbose=False):
    import time
    start = time.time()
    res = sortdiff(integers,sortedlist,verbose)
    stop = time.time()
    print "Execution time: %fsec" % (stop - start)
    return res

if __name__=='__main__':
    import sys
    integers = []
    for i in sys.argv[1:]:
        integers.append(int(i))
    if not integers:
        print "Usage: %s 1 2 3 4 5 ..." % sys.argv[0]
        print "Using 10 2 7 4 as sample.\n"
        integers = [10, 2, 7, 4]
    print "Sorting %s..." % str(integers)
    solution = timed_sortdiff(integers)
    print "Solution is %s" % str(solution)
    print "Checking correctness: ",
    print_diffs(solution)