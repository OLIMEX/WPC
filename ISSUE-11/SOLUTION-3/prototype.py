# author : st0le (http://lostincompilation.blogspot.com)
# github : https://github.com/st0le/
import sys
maze = map(list,sys.stdin.read().split("\n"))


def count_components(maze):
    rows,col = len(maze),len(maze[0])
    def floodfill(x,y):
        stack = [(x,y)]
        c = 0
        while stack:
            x,y = stack.pop()
            if maze[x][y] == '@':
                maze[x][y] = ' '
                c += 1
                for dx,dy in [(0,1),(1,0),(-1,0),(0,-1)]:
                    if 0 <= x+dx < rows and 0 <= y+dy < col:
                        stack.append((x+dx,y+dy))
        return c
    lst = []
    for x,row in enumerate(maze):
        for y,c in enumerate(row):
            if c == '@':
                lst.append(floodfill(x,y))
        
    return lst
print maze    
print max(count_components(maze))