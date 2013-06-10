#!/bin/sh

# Builds a regex for similar words
# Executes it against a file

# - NotZed

if [ ${#*} -lt 2 ] ; then
    echo "Usage $0 file.txt word ..."
    exit 1
fi

# input
file=$1
shift

# build regex
regex=""
while [ ${#*} -gt 0 ] ; do
    word=`echo $1 | tr '[:upper:]' '[:lower:]'`
    shift

    # include 'word' and 'word.'
    regex="${regex:+${regex}\|}${word}\|${word}."

    i=0
    while [ $i -lt ${#word} ] ; do
	j=`expr $i + 1`
 	# one letter changes
	regex="${regex}\|${word:0:$i}.${word:$j}"
	# one letter inserted
	regex="${regex}\|${word:0:$i}.${word:$i}"
	# one letter deleted
	regex="${regex}\|${word:0:$i}${word:$j}"
	i=$j
    done
done
# need to match fully
regex="^\(${regex}\)\$"

echo Using pattern ${regex} >&2
echo Processing file ${file} >&2

# split the file into words | convert to lower case | convert to sorted, unique set | perform search
tr -cs '[:alnum:]' '[\n*]' < ${file} | tr '[:upper:]' '[:lower:]' | sort -u | grep -e "${regex}"
