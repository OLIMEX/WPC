I = '20W3BWB11WBW4B10WBW2BW2B9WBWB3W2B8W2B5W2B6W2B7W2B4W2B9W2B2W3B9W3B3WBW3BW3BWB2W4BWBWBWBWBW7BWBWBW3BW7BWBWB5W7BWBWB5W35B'

O = ''
P = 0
L = 1
while P < len(I):
    if I[P:P+1] <= '9':
        if I[P+1:P+2] <= '9':
            W = 2
        else:
            W = 1
        L = int(I[P:P+W])
        P = P + W
    else:
        C = I[P:P+1]
        P = P + 1
        O = O + ''.join([C[:1]] * L)
        L = 1

O = O.replace('W', ' ')
O = O.replace('B', '#')

for N in xrange(17):
    print O[N*16:(N+1)*16]

L = 0
X = '?'
A = ''
O = O + '?'
for C in O:
    if C <> X:
        if X <> '?':
            if L == 1:
                A = A + X
            else:
                A = A + str(L) + X
        X = C
        L = 1
    else:
        L = L + 1

A = A.replace(' ', 'W')
A = A.replace('#', 'B')

print I == A
