# Olimex Weekend Programming Challenge Issue #20 – Anagrams
#
# Usage (tested with win32 gawk 3.1.6) :
#
# gawk -f olimex20.awk alice.txt
#
# By Laurent Haas - August 2013
#
# Notes
# - Require the asort function (may break with some versions of awk or gawk)
# - alice.txt is supposed to be a text version of the content of the html page
#
# v1.1 : Check word length > 1
# v1.0 : Initial version

BEGIN {
	FS = "[^a-zA-Z]"; # Isolate each word as a "field" in awk terminology
}
{
	# For each word, calculate its key composed of
	# all its letters in alphabetical order
	# and concatenate with the value of the index key
	# in the words array if it is not done yet.

	for (i = 1; i <= NF; i++) {
		if ((len = length($i)) > 1) { # Word length must be greater than 1
			$i = tolower($i)
			split($i, letters, "")
			asort(letters)
			key = ""
			for (j = 1; j <= len ; j++)
				key = key letters[j]
			if (words[key] !~ $i)
				words[key] = words[key] $i " "
		}
	}
}
END {
		for (key in words)
			if (words[key] ~ / .* /) # 2 words at least
				print words[key] # Minor glitch : Trailing space at the end of each line
}