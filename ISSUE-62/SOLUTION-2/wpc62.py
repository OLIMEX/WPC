import time
start = time.clock()
M=10**6
for i in xrange(2, 1000):
    if M%i == 0 and '0' not in list(str(i) + str(M/i)):
        print i, M/i, time.clock() - start
# 64 15625 0.000131145396643
