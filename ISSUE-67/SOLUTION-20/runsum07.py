
#Thanks http://www.maths.surrey.ac.uk/hosted-sites/R.Knott/runsums/runsumsref.html#algrunnb
p=9808
i=0
t=0
while True:
    i+=1
    t+=i
    a=p-t
    if a<0:
        break
    elif a%i == 0:
        b=a//i
        print "From page", b+1, "to", b+i
