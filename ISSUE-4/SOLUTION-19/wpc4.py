import re

# Checks if a word is an isogram
def is_isogram(word):
	word = [x for x in word]
	seen = set()
	return not any(i in seen or seen.add(i) for i in word)


# Read the input text from a file
text = open("ALICE", 'r').read()

# sanitize the input text
# (remove non-alphanumeric characters and replace double dashes with spaces)
pattern = re.compile('[^\w -]+')
text = pattern.sub('', text)
pattern = re.compile('--')
text = pattern.sub(' ', text)

# split the text on lowercase words
words = [x.lower() for x in set(text.split(" "))]

# sort the words by length, from longest to shortest
words.sort(key=len, reverse=True)

found = False
showall = True

for word in words:
	if is_isogram(word):
		print "%s is an isogram of length %d" % (word, len(word))
		found = True
		if not showall:
			break

if not found:
	print "No isograms found"