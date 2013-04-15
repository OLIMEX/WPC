!/bin/sh

# Convert to lowercase
# Remove everything which is not a word cahracter + "_" and break words 
to lines
# Delete non isograms
# Sort results to longests first
t2=`cat $1 | tr 'A-Z' 'a-z' | sed -e 's/\W/\n/g' | sed -e '/\(.\).*\1/d' 
| awk '{print length($0), $0}' | sort -nr`

IFS='-'
# Get the longest length
l2=`echo $t2 | head -1 | cut -f 1 -d ' '`

# Select longest lines
r2=`echo $t2 | grep "^$l2 " | cut -f 2 -d ' '`

# Print results
echo $r2