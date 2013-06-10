#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Problem:  Similar words
#
# Similar word are these which differs by one character only i.e. one
# character changed or inserted or deleted.
#
# For example: if useing this concept the word “hello” is considered similar
# to “hella” and to “hell” or “shello”
#
# Make code which enters word then scans:
# http://fiction.eserver.org/novels/alice_in_wonderland.html and prints all
# similar words to the one which is entered.


def debug(*x):
	#print ("%s" % x)
	pass


def is_similar(w1, w2):
	# return True if the two given words are similar, False otherwise

	debug("Evaluating similarity between '%s' and '%s'\n" % (w1, w2))
	lendif = abs(len(w1) - len(w2))
	if lendif > 1:
		return False

	if w1 == w2:
		return False

	setcw1 = set( [ x for x in w1 ] )
	setcw2 = set( [ x for x in w2 ] )
	simdif = setcw1 ^ setcw2

	if ( ( len(simdif) > 2 ) or \
		( (len(simdif) != 1) and ( lendif == 1 ) ) or \
		( (len(simdif) != 2) and ( lendif == 0 ) ) ):
			return False

	debug(" Found promising candidates in pair ('%s', '%s'). Digging deeper...\n" % (w1, w2))

	pos = 0
	stepshort = 1 - lendif
	difcount = 0
	(s1, s2) = (w1, w2) if len(w1) > len(w2) else (w2, w1)
	ls2 = len(s2)
	debug("  Long word: %s\t Short word: %s" % (s1, s2))
	while (difcount < 2) and (pos+difcount < ls2):
		i1 = pos + difcount
		i2 = pos + difcount*stepshort
		debug("    comparing(%d, %d)" % (i1, i2))
		if s1[i1] != s2[i2]:
			debug("  Difference at position %d.\n" % (pos+difcount))
			difcount += 1
			if difcount > 1:
				break
		else:
			pos += 1

	res = (difcount == 1 or (difcount==0 and lendif==1))
	debug(" >>> Result: %s and %s are%s similar\n" % (w1, w2, "" if res else
		" not" ) )

	return res


def get_html_page():
	import urllib

	url = "http://fiction.eserver.org/novels/alice_in_wonderland.html"
	f = urllib.urlopen(url)
	s = f.read()
	f.close()

	return s

def get_story():
	from BeautifulSoup import BeautifulSoup

	page = get_html_page()

	soup = BeautifulSoup(page)
	storylist = [ p.string for p in soup.html.blockquote.findAll('p') if
			p.string is not None ]

	story = " ".join(storylist)

	return story

def get_sanitized_story():
	story = get_story()
	sanstory = sepre.sub(' ', story)

	return sanstory

def get_word_list():
	story = get_sanitized_story()
	words = [ x for x in set(story.split()) ]

	return words

def similar_words_from_AiW(word):

	# process words

	words = get_word_list()

	simlist = [ x for x in words if is_similar(word, x) ]

	return simlist


def get_word():
	while True:
		try:
			ref = unicode(raw_input('Enter word: '))
			sanref = sepre.sub(' ', ref)
			words = sanref.split()
			if len(words) != 1:
				raise ValueError
			else:
				return words[0]
		except ValueError:
			print("That is not a word! You must enter a single valid word.")



import re
sepre = re.compile(r"[-.,:;()+_%&!`#$%^*'<>\[\]?\"]")

refword = get_word()
similars = similar_words_from_AiW(refword)

if len(similars) > 0:
	print("Words similar to '%s':\n" % refword)
	for w in similars:
		print("\t%s" % w)
else:
	print("No words similar to '%s' were found.\n" % refword)


