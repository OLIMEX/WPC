#!/usr/bin/env python
# -*- coding: utf-8 -*-

import time

def main() :
	print "Olimex - WPC#4 - Solution in Python by Joh.Lummel.\n"
	
	ticks = time.clock()

	print "open 'alice.txt'."
	alice = open('alice.txt','r') 

	iso_w =""
	iso_l = len(iso_w)

	print "search for isogram",

	for line in alice :								# get a textline
		a = line.strip().split(' ')					# strip and split textline into list of words
		
		for w in a :								# now get a word form list
			l = len(w)								# get the length of the word
			if l > iso_l : 							# only test if lenght of word greater than isogram found
				if w[-1].isalpha() :				# if last char of string is not an alpha
					noiso = False					# -> failure
					for j in range(0,l-1):
						if w[j].isalpha() :			# only test if char is an alpha
						
							for i in range(j+1,l): 	# compare char with all char's behind it
								noiso = ( w[j].lower()==w[i].lower() )
								if noiso :			# if char w[j] is found elsewhere the word can't be an isogram  
									break			# 
							# -- i
						else : 						# w[j] is not an alpha  
							noiso = True			# -> failure 
											
						if noiso :					# 
							break					#
					# -- j
					if not(noiso) :					# ok, string is iso
						if l>iso_l :				# is it longer than last iso found?
							iso_w = w				# then word w is the new longest isogram
							iso_l = l
							# print "-> new Iso found: %s -> %d char long" % (iso_w,iso_l)
					# endif not(noiso)
			# endif l > iso
		# -- w
	# -- line in alice
	alice.close()	

	ticks = time.clock()-ticks 
	print "take %.5f ms process time..." % (ticks*1000)
	# print "take %.5f s process time..." % (ticks)
	print						
	print "The longest isogram found:"	
	print " %s -> %d char long" % (iso_w, iso_l)
	print
	print "that's all folks..."
  
if __name__=='__main__':
    main()
