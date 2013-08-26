# Olimex Weekend Programming Challenge Issue #21 – Words Puzzle
#
# Usage (tested with win32 gawk 3.1.6) :
#
# gawk -f olimex21.awk cambridge.txt
#
# By Laurent Haas - August 2013

function shuffle(word) {
	if ((len = length(word)) > 3) { # Word length must be greater than 3 to shuffle it
		do {
			word2 = substr(word, 1, 1)	# Keep the first letter
			toMix = substr(word, 2, len - 2);
			while ((len2 = length(toMix)) > 0) {
				k = 1 + int(rand() * len2)	# Take a random letter
				word2 = word2 substr(toMix, k, 1)	# Concatenate it to word2
				toMix = substr(toMix, 1, k - 1) substr(toMix, k + 1)	# and remove it from toMix until toMix is empty
			}
			word2 = word2 substr(word, len, 1)	# Keep the last letter of the word
		} while (word == word2)	# Ensures the word is really shuffled
		return word2
	}
	else
		return word
}

BEGIN {
	srand()	# Ensures rand() will generate different sequences at each run
}
{
	for (i = 1; i <= length($0); i++) {
		if ((letter = substr($0, i, 1)) ~ /[a-zA-Z]/) {	# Build a word composed of letters only
			word = word letter
		}
		else {	# We have a word !
			line = line shuffle(word)
			line = line letter
			word = ""	# Reset word, ready for the next one
		}
	}
	
	if (word != "")	# The last char of the line was a letter.
		line = line shuffle(word)	# Apply the shuffle function to the last word built
		
	print line	# We're done !
	line = ""	# Reset line, read for the next one
}
END {
}