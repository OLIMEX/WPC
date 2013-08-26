#!/usr/bin/env python3
#-*- coding:utf-8 -*-
import random
import re
import sys

# rules:
# Write code which takes as input normal text and shuffles the letters inside the words 
# to make text like this one above.

if len(sys.argv)!=2:
	print("Usage: python3 challenge21.py  (text file to convert)")
	print("Example: python3 challenge21.py test.txt")
	w= input("\ncontinue with test.txt? y or n ")
	if w == "y":
		print("ok")
		f = open("test.txt", "r")
	else:
		sys.exit(1)
else:
	f = open(sys.argv[1], "r")
 
a = f.read()
f.close()
print(a)
a = re.findall(r"\w+|[^\w\s]", a, re.UNICODE)

for i in a:
	x = list(i)
	l = len(x)
	if l >= 4:
		first = x[0]
		last = x[l-1]
		del x[l-1]
		del x[0]
		while x == random.shuffle(x):  
			random.shuffle(x)
		x.insert(0, first)
		x.append(last)
	w=""
	for i in x:
		w = w+str(i)
	print(w, end=" ")


	


