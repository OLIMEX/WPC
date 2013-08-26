#!/usr/bin/ruby

# usage: text_scramble.rb input.txt

# go through each word
ARGF.read.scan(/\W*\w+\W*/).each { |w| 
	# split off last character and punctuation
	post = w.slice!(/(\W*\w\W*)$/)
	# split off punctuation and first character
	pre = w.slice!(/^(\W*\w?)/)
	# jumble the letters
	# and output it
	print pre + w.chars.to_a.shuffle!.join + post
}
