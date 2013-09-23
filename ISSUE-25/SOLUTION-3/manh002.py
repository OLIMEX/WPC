def mandis(px, py, qx, qy):
    return abs(px - qx) + abs(py - qy)
    
def manhm(px, py, qx, qy, l, m, n, st, obst):
    if l==0 and px==qx and py==qy and px>=0 and px<=m and py>=0 and py<=n:
        print st #Should I use Python yield?
    else:
        for k in [[1, 0], [0, 1], [-1, 0], [0, -1]]:
            px1 = px + k[0]
            py1 = py + k[1]
            if px1>=0 and px1<=m and py1>=0 and py<=n \
            and mandis(px1, py1, qx, qy)<=l and not [px1, py1] in obst:
                st1 = list(st)
                obst1 = list(obst) #append point that passed as want
                st1.append([px1, py1])
                manhm(px1, py1, qx, qy, l-1, m, n, st1, obst)
                
m = int(raw_input('enter matrix size in x axis: '))
n = int(raw_input('enter matrix size in y axis: '))
px = int(raw_input('enter x of point A: '))
py = int(raw_input('enter y of point A: '))
qx = int(raw_input('enter x of point B: '))
qy = int(raw_input('enter y of point B: '))
l = int(raw_input('enter L: '))
obsn = int(raw_input('enter number of obstacles: '))
obstcl = []
for i in range(obsn):
    print 'obstacle no.%d' % (i+1)
    obstx = int(raw_input(' enter x: '))
    obsty = int(raw_input(' enter y: '))
    obstxy = list([obstx, obsty])
    obstcl.append(obstxy)

print 'begining from %s' % [px, py]
manhm(px, py, qx, qy, l, m, n, [], obstcl)
