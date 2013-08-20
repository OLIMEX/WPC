#!env python
#
# Usage: anagram.py <text file>

import sys, re

raw = file(sys.argv[1]).read()

# Step 1: Break the input data into words
raw1 = filter(lambda c: c != "'", raw)
raw2 = ''.join(map(lambda c: (c.isalpha()) and c or ' ', raw1)).lower()
words = set(raw2.split())

# Step 2: Build a dictionay of words, where the keys are letter-sorted
#         string of the original word. All anagrams of a single word will
#         fall under the same key
anagrams = {}
for word in words:
	k = list(word)
	k.sort()
	k = ''.join(k)
	print k
	if k in anagrams:
		anagrams[k].append(word)
	else:
		anagrams[k] = [ word ]

# Step 3: Filter out all the words that occured only once
anagram_keys = filter(lambda k: len(anagrams[k])>1, anagrams)

# Step 4: Print the results
for k in anagram_keys:
	print anagrams[k]



