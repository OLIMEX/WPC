maze = '''WWWWWWWWWW
W  WW    W
W       WW
W  @@    W
W @@     W
W      @ W
W@    @@ W
WWWWWWWWWW'''

O = []
lines = maze.split('\n')
for (row, line) in enumerate(lines):
    for (col, char) in enumerate(line):
        O.append((row, col, char))

biggest = 0
while len(O) > 0:
    P = [O.pop()]
    size = len(P)
    while True:
        A = [(x, y, z) for (x, y, z) in O for (a, b, c) in P if abs(x-a) + abs(y-b) == 1 and z == c]
        for a in A:
            if a not in P:
                P.append(a)
            if a in O:
                O.remove(a)
        if size == len(P):
            print len(P), P[0][2]
            if biggest < size:
                biggest = size
            break
        size = len(P)

print biggest
