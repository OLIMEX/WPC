words = ["A13", "A13-OLinuXino", "iMX233-OLinuXino", "MOD-PULSE", "MOD-IO", "A-I"]

# Convert words to lowercase
words = [x.lower() for x in words]

# Helper function that returns all substrings of a given length
def substrings(word, length):
    return [word[i:i+length] for i in range(0, len(word)-length+1)]

# Function to count repetitions of substrings of a certain length
def gentable(length):
    count = {}
    for word in words:
        for part in substrings(word, length):
            count[part] = count.get(part, 0) + 1
    return count

missing = list(words)
maxlength = max([len(x) for x in missing])
length = 0

# Try until we solve the problem for all words or the substring
# size becomes longer than the longest word missing
while missing and length <= maxlength:
    length += 1
    count = gentable(length)

    # For each substring on each missing word, we check if it's unique
    for word in list(missing):
        for part in substrings(word, length):
            # if it is indeed unique, we found our solution
            if count[part] == 1:
                print "%s: %s" % (word, part)
                missing.remove(word)
                maxlength = max([len(x) for x in missing])
                break

# Let the user know if we couldn't find some solutions
if missing:
	print "No solution found for the following: %s" % missing