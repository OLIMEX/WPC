N = 42
for target in xrange(2, N+1):
    found = False
    guess = 2
    while not found:
        binary = guess
        x = 1
        s = '1'
        d = s
        while binary > 1:
            if binary & 1 == 1:
                x = x * 3
                s = s + ' *3'
                d = d + ' *3 (=' + str(x) + ')'
            else:
                x = x // 2
                s = s + ' /2'
                d = d + ' /2 (=' + str(x) + ')'
            if x == target:
                found = True
                break
            else:
                guess = guess + 1
            binary = binary // 2
    print target, s
    if len(d) < 80:
        print target, d
print d                
        
