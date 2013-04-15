As 1-liner:

awk 'BEGIN { RS="[^A-Za-z]" } $0 { word=tolower($0) ; if(word in WordSeen) next ; WordSeen[word]=1 ; split(word,Letters,"") ; delete CharSeen ; for(char in Letters) if(++CharSeen[Letters[char]]>1) next ; len=length(word) ; if(len>maxlen) { maxword=word ; maxlen=len } } END { print maxword}' pg11.txt

My test data was downloaded from the Gutenberg Project:

http://www.gutenberg.org/cache/epub/11/pg11.txt

