#!/bin/bash

read word

links2 -dump http://fiction.eserver.org/novels/alice_in_wonderland.html | \
tr -dc "[[:alnum:]] " | tr "\n\t" " " | tr -s " " | tr " " "\n" | sort -u | \
egrep `(
len=\`echo $word | tr -dc "[[:alnum:]]" | wc -c\`
echo "^([[:alnum:]]${word}"
for i in \`seq 0 $(($len - 1))\` ; do
	echo "$word" | sed "s/\([[:alnum:]]\{$i\}\).\(.*$\)/\1[[:alnum:]]\2\n\1\2/" ;
done
echo -n "${word}[[:alnum:]])$"
) | tr "\n" "|"` | grep -v "^${word}$"
