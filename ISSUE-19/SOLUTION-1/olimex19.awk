#
# Olimex Weekend Programming Challenge Issue #19 – Pattern match
#
# Usage (win32 gawk) :
#
# echo | gawk.exe -f olimex.awk -v input_string="The big black cat jumps over the window" pattern_string="*c*"
#
# By Laurent Haas - July 2013
#
BEGIN {
	FS = "['\".,; ]";	# Fields separators as specified
}
{
	$0 = input_string;
	gsub("*", ".*", pattern_string);	# To comply with the RegExp syntax
	gsub("?", ".?", pattern_string);	# To comply with the RegExp syntax
	for (i = 1; i <= NF; i++) {
		if (match($i, pattern_string) > 0) {
			print $i;
		}
	}
}