#!/usr/bin/python
import re

# Richard Park
# richpk21@gmail.com
# OLIMEX's Weekend Programming Challenge Issue #19 - Pattern Match

def match(pattern=None, text=""):
	if not pattern:
		print 'ERR: No pattern!'
		return []
	print 'STRING:  %s'%text
	print 'PATTERN: %s'%pattern
	p = pattern
	p=p.strip()
	#print p
	pl=p.split('*')
	p='\w*'.join(pl)
	pl=p.split('?')
	p='\w'.join(pl)
	#print p
	po = re.compile(p)
	m = po.findall(text)
	print m
	print

if __name__=='__main__':
	print
	
	# input text
	text = 'The big black cat jump over the window'
	# pattern
	p = 'b*'
	# function call
	match(p,text)
	
	p = '*c*'
	match(p,text)
	p = '?i*'
	match(p,text)
	p = '?x?'
	match(p,text)
	match()


