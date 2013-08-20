#!/bin/sh

prev=""
links2 -dump 'http://fiction.eserver.org/novels/alice_in_wonderland.html' | \
tr "\n" " " | tr -s " \t" | tr " \t" "\n" | tr -cd "[[:alnum:]\n]" | sort -u | \
while read line ; do
	echo "$line" | sed "s/\(.\)/\1\n/g" | sort | tr -d "\n"
	echo " $line";
done | sort | while read letters word ; do
	if [ -n "$prev" -a "$prev" = "$letters" ] ; then
		echo -n ",$word"
	else
		echo -n "\n${word}"
	fi
	prev=$letters
done | grep ","
