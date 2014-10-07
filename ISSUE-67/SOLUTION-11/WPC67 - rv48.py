#!/usr/local/bin/python2.7

i,j,somme=0,0,0

list=[]
N=9808
while (i<=N/2):
  i=i+1

  somme=i

  j=i

  while(somme<N):

    j=j+1

    somme=somme+j

  if somme==N:

    list.append([i,j])

for k in list:

  print "missing pages can be between page",k[0],"and",k[1],"included or"

print "of course the page number",N,"alone"