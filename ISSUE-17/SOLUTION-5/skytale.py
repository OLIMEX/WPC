#!/usr/bin/python


# Richard Park
# richpk21@gmail.com
#
# http://olimex.wordpress.com/2013/07/12/weekend-programming-challenge-issue-17-skytale/
#

import sys
text="fun stuff!"
nrow=3

text=raw_input("input text:     ")
nrow=int(raw_input("number of rows: "))

########## encryption #########
m=len(text)%nrow
if m != 0:
	text+=' '*(nrow-m)
ncol=len(text)/nrow
col=0
rows=[]
cols=[]
for t in text:
	cols.append(t)
	col +=1 
	if col == ncol:
		col=0
		rows.append(cols)
		cols=[]

ctext=""
for n in range(ncol):
	for c in rows:
		ctext+=c[n]
print "ciphertext:    ",ctext


############# decryption #########
col=0
rows=[]
cols=[]

for i in range(ncol):
	cols=[]
	for j in range(nrow):
		cols.append(ctext[(i*nrow)+j])
	rows.append(cols)

dtext=""
for n in range(nrow):
	for c in rows:
		dtext+=c[n]
dtext=dtext.strip()
print "original text: ",dtext
