
#problem: given p: find m, n so that p==sum([m..n]); p, m, n are >0 integers
#find sum([1..m-1]) and sum([1..n]) in hash table for finding sum([m..n])
p=9808
s=0
h={}
for i in range(1, p):
    s+=i
    if s-p in h:
        print "Page", h[s-p]+1, "to", i
    h[s]=i
