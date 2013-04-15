#!/usr/bin/env python
import string, urllib2, sys

def isIsogram(word):
  return not [1 for i, letter in enumerate(word) if letter in word[:i]+word[i+1:]]

resource = sys.argv[1] if len(sys.argv) > 1 else 'http://www.gutenberg.org/files/28885/28885.txt' # "Alice in Wonderland" @ Gutenberg
handle = urllib2.urlopen(resource) if resource.startswith('http') else open(resource, 'r')
words = handle.read().lower().split() or "(Couldn't get any data.)"; handle.close()

words = [filter((lambda char: char in string.letters + '-'), word) for word in words] # leave only letters and hyphens
isograms = sorted(set(word for word in words if isIsogram(word)), key=len, reverse=True) # isIsogram? + unique + sort by word length
longest = sorted([word for word in isograms if len(word) == len(isograms[0])]) # get the ones matching the length of the longest one

print 'Number of isograms: %d.' % len(isograms)
plurals = dict(s='s' if len(longest)>1 else '', have='have' if len(longest)>1 else 'has', are='are' if len(longest)>1 else 'is')
print 'The longest one%s %s %d characters.' % (plurals['s'], plurals['have'], len(longest[0])) # being pedantic and stuff
print 'The longest one%s %s %s.' % (plurals['s'], plurals['are'], ', '.join(longest))
