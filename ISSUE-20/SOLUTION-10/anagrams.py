#!/usr/bin/python

# Richard Park
# richpk21@gmail.com
# Olimex Weekend Challenge #20 Anagrams

import re

class Word:		
	def __init__(self, text=""):
		self.histogram = {}		
		self.text=text
		
		for c in text:
			try:
				c=c.lower()
			except:
				print 'Warning: none-alphabet character exists in the text: %s' % text
				
			try:
				self.histogram[c]+=1
			except:
				self.histogram[c]=1
		
	def compare(self,word):
		if len(self.text) != len(word.text):
			return None
		for k,v in self.histogram.iteritems():
			try:
				if word.histogram[k]!=v:
					#print '%s   Different Histogram' % word.text
					return None
			except:
				return None
		#print '%s  Same Histogram' % word.text
		return word.text
		
			
			

# test ##############################################
input="warned"
text="This 'warned' war-ned andrew wander fun wand-e"

#list of words
words = re.findall('\w+', text)

#filter words by length and make 'Word' object for each word
n=len(input)
wordlist=[]
for w in words:
	if n==len(w):
		wordlist.append( Word(w))

#make 'Word' object with one input word
a=Word(input)

#compare histograms
final_list=[]
for w in wordlist:
	t=a.compare(w)
	if t != None and t not in final_list:
		final_list.append(t)

if final_list:
	print '<-Found->'
	print final_list
else:
	print '<-Not Found->'
	
		