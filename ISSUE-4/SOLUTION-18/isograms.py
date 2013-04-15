#!/usr/bin/env python
import string, sys
def isIsogram(word): # returns True if given word is an isogram (has no repeating letters)
  return not [1 for i, letter in enumerate(word) if letter in word[:i]+word[i+1:]]

words = set(filter((lambda char: char in string.letters + '-'), word) for word in sys.stdin.read().lower().split())
isograms = sorted(filter(isIsogram, words), key=len, reverse=True) # get isograms and sort them by length, descending
print ' '.join(sorted([word for word in isograms if len(word) == len(isograms[0])])) # longest ones, alphabetic order
