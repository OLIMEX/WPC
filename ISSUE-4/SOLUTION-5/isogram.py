#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys

def isIsogram(word):
	for char in word:
		#convert the string to lower case so that, for example, E == e
		if word.lower().count(char) != 1 :
			return False
	return True

def main():
	if len(sys.argv) == 1:
		print("USAGE: "+sys.argv[0]+" <input_file>")
	else:
		#Total isogram words found
		count = 0
		#The first argument contains the file name to read
		txfile = open(sys.argv[1], "r")
		#Will contain the biggest word wich is an isogram
		maxIsogram = ""
		
		#For every line in the input file
		for line in txfile:
			#Read a line and split it into words
			words = line.split()
			#For every word
			for word in words:
				#Check if it is an isogram (removing punctuation marks, etc) (probably not the best way..)
				word = word.strip('\'`,.(){}\"/*-+:-_;')
				if isIsogram(word):
					count = count + 1
					#Always keep the last word found (in case there are more than one with the same number of letters)
					if len(word) >= len(maxIsogram):
						maxIsogram = word
						
		print("Biggest word found:\t"+maxIsogram+" ("+str(len(maxIsogram))+" characters) ")
		print("Total words found:\t"+str(count))

# Standard boilerplate to call the main() function to begin the program.
if __name__ == "__main__":
	main()