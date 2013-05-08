#!/usr/bin/env python
#coding:utf-8
"""

Author:      Alexios Chouchoulas <alexios@bedroomlan.org>
Date:        2013-05-04
Website:     http://www.bedroomlan.org
Solution to:

http://olimex.wordpress.com/2013/05/03/weekend-programming-challenge-issue-7 

There are three solutions to the problem here. Two naïve ones (one iterative,
one recursive), and one using path finding in direct acyclic graphs (DAGs). The
last one is the fastest, but each sheds a different sort of light on the
problem.

If ran as an executable, the program expects the number N (in decimal) as its
only command line argument, and runs the DAG version of the solution.

Please note that this interpretation of the problem is that the cat only jumps
forward on the stairs, and not back (i.e. there are no cycles in the paths).

"""

import sys

# Python 3 doesn't have list-generating range(), and xrange() (which is better
# anyway) has been ranemed.
if sys.version.startswith('3'):
    xrange = range


def naive_step_iterative(n):
    """The cat-step problem, naïve iterative Python-fu solution.

    Since the cat can make one or two-step moves, we can represent any movement
    'plan' (ha! Cats don't plan) as a binary number. To do this, we just
    convert integers to binary representations, and increment each digit by 1,
    so that 00111 becomes 11222, represenging two single-step moves followed by
    three single-step moves.

    We loop through all 2**n numbers and check whether or not each of them is a
    solution, which we then convert to a movement plan and print.

    TOLD you you it's a naïve solution.

    """

    def mybin(num, pad=16):
        """Convert a number to its binary representation, padded to pad
        digits (defafult 16)."""
        # Python's bin() returns a '0b' prefix, which we strip away using
        # the [2:] array slice. We pad the remaining string with zeroes up
        # to pad.
        return bin(num)[2:].zfill(pad)

    # steps ranges from 1 to n.
    for steps in xrange(1, n + 1):

        # i ranges from 0 to (2^steps)-1, which represents the set of
        # all potential walking plans of j moves (only a few will be
        # solutions). Where the number has a '0' bit, the cat moves by
        # one. Where the number has a '1' bit, the cat moves by two
        # steps. We interpret this from most-significant to
        # least-significant bit, but that's just for ease.

        for i in xrange(1 << steps):
            # Convert i into a binary number 
            plan = [int(x) + 1 for x in mybin(i, pad=steps)]
            if sum(plan) != n:
                continue
            print("N=%d %d-step solution: %s" % (n, steps, plan))


def naive_step_recursive(n):
    """The cat-step problem, naïve recursive solution. Do it the Prolog way,
    depth-first searching through the entire path space, looking for paths that
    match our requirements, i.e. the total number of steps taken ."""

    def recurse(plan, total, steps):
        if total > steps:
            # The kitty overstepped. It lands somewhat awkwardly,
            # makes sure no-one saw, brushes itself off and goes to
            # sleep. (no solution, terminating step)
            return
        elif total == steps:
            # We're on the last step, solution found!
            print("N=%d %d-step solution: %s" % (n, len(plan), plan))
        else:
            recurse(plan + [1], total + 1, steps)
            recurse(plan + [2], total + 2, steps)
            
    recurse([], 0, n)


def graph_solution(n):
    """The cat-step, problem, fast solution.

    Visualise the stairs as a simple lattice tree, like this (for n=3 we have
    four vertices, since the conventional definition of a step is derived from
    the 'going up' part, or the edge of the step graph — not the vertex so we
    need three edges and hence four vertices. The starting position doesn't
    count):
          ________
         /        \         Vertices: 0→1, 0→2, 1→2, 1→3, 2→3
    0--->1--->2--->3        
     \_______/              (number of vertices: 2(n - 1) - 1)

    This graph (a directed acyclic graph or DAG) shows valid paths only, and if
    we generate all paths within it, we have a solution that doesn't involve
    testing random paths — i.e. is non-naïve.

    To do this, we follow the standard DAG traversal algorithm, counting paths
    going from 3 to 0 (in topological order).

    Please note that the solution representation is different here. Rather then
    1-step or 2-steps plans, we print out paths through the graph showing which
    steps the cat jumps to.
    """

    # First, make the graph. We represent a graph as a list of source
    # vertices. Each item in the list is a list of the nodes to which we can
    # get to from this vertex, i.e. g[src] = [dst1, dst2, ... dstn]. The
    # example graph would be represented as:
    #
    # [[1, 2], [2, 3], [3], []]
    
    g = []
    for i in range(n + 1):   # from 0 (inclusive) to n (inclusive)
        g.append([ x for x in range(i + 1, i + 3) if x <= n ])

    # Sanity checks
    assert len(g) == n + 1
    assert sum(len(x) for x in g) == (2 * n) - 1

    # Now iterate, generating paths
    paths = dict()
    paths[n] = [[n]]
    for src in range(n - 1, -1, -1): # [n-1, ..., 0]
        p = []
        for dst in g[src]:
            p += [ [src] + x for x in paths[dst] ]
        paths[src] = p

    print("n: %d" % n)
    print("Solutions: %s" % (', '.join(str(x) for x in paths[0]) + "."))
    print("Number of solutions: %d" % len(paths[0]))



if __name__ == '__main__':
    try:
        n = int(sys.argv[1])
    except:
        sys.stderr.write("Syntax:\n\n  %s N\n\n" % sys.argv[0])
        sys.exit(0)

    graph_solution(n)


# End of file.
