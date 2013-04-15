REBOL [title: "wpc#4 isogram"]

url: http://fiction.eserver.org/novels/alice_in_wonderland.html
digits: charset [#"0" - #"9"] 
alphanum: union digits charset [#"a" - #"z" #"A" - #"Z" #"'" #"-"]
map: make block! 100

parse/all (read url) [thru <BLOCKQUOTE> copy text to </BLOCKQUOTE> to end]
remove-each word (words: load/markup text) [tag? word]
parse/all (form words) [ some [
	["&" [some alphanum | "#" some digits] ";"] |
	copy word some alphanum (
		all [ equal? word (unique word)
			size: length? word
			any [ if v: select map size [any [(select v word) (append v word)]]
				do [(repend map size) (repend/only map [word])]]]) | skip ]]

print ["result:" sort second (sort/skip/reverse map 2)]
halt
