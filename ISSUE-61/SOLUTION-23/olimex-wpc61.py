import itertools

n=9
nstr=map(str,range(1,n))

for c in itertools.product(['','+','-'],repeat=n-1):
	s = "".join(itertools.chain(*zip(nstr,c)))+str(n)
	if eval(s) == 100:
		print s,'=',100