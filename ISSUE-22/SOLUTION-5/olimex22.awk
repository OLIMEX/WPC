# Olimex Weekend Programming Challenge Issue #22 – Plagiarism detector
#
# http://olimex.wordpress.com/2013/08/30/weekend-programming-challenge-week-22-plagiarism-detector/
#
# Usage (tested with win32 gawk 3.1.6) :
#
# gawk -f olimex22.awk file1.txt file2.txt
#
# file1.txt is the reference file
# file2.txt is the examined file
#
# By Laurent Haas - Sept 2013

BEGIN {
	FS = "[^a-zA-Z]"	# Isolate each word as a "field" in awk terminology
}
{
	if (FNR == NR)	# file1 process
		for(i = 1; i <= NF; i++)	# Put all words in an array
			a[tolower($i)]
	else { # file2 process
		n = n + NF	# Total count of words
		for(i = 1; i <= NF; i++)	# Search for each word in the array
			if (tolower($i) in a)
				p++	# Found : Add 1 to p
	}
}
END {
	if (FNR != NR && n)	# file2
		printf("%4.2f% words of file2 are in file1\r\n", p / n * 100)
}