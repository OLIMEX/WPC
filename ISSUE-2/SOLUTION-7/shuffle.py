import random
import sys

def shuffle(a):
  """Yields all solutions up to mirror symmetry."""
  # Process integers in decreasing order, each can be appended only
  # at the beginning or the end.
  s = list(reversed(sorted(a)))
  stack = [s[:2]]
  n = len(s)
  while stack:
    middle = stack.pop()
    m = len(middle)
    if m == n:
      yield middle
    else:
      h = s[m]
      if h - middle[0] <= middle[0] - middle[1]:
        stack.append([h] + middle)
      if middle[-2] - middle[-1] <= middle[-1] - h:
        stack.append(middle + [h])

def check(a):
  if len(a) <= 2: return True
  return all([a[i] - a[i+1] <= a[i+1] - a[i+2] for i in range(len(a)-2)])

# generate a random array that has a solution
if len(sys.argv)<3:
  d = sorted(random.sample(range(1000), int(sys.argv[1])))
  a = [0]
  for di in reversed(d):
    a.append(a[-1] + di)
else:
  a = map(int, sys.argv[1:])

s = list(shuffle(a))

print "# solutions to random problem:", len(list(shuffle(random.sample(range(1000000), 100))))
print "# {0} has {1} solutions. Check={2}".format(a, len(s), all(map(check, s)))
# Print solutions for gnuplot> plot "output" w lp palette
for i,sl in enumerate(s):
  color = float(i)/(len(s)-1)
  print
  print
  print '\n'.join(["%d %d %f"%(x[0],x[1],color) for x in enumerate(sl)])

    
    
