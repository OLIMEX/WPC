#!/usr/bin/ruby
#
# Olimex Weekend Programming Challenge Issue #20 - Anagrams
#
# Javier Donaire

require 'open-uri'
require 'set'

url = ARGV[0] || 'http://fiction.eserver.org/novels/alice_in_wonderland.html'
text = ''
anagrams = {}

open(url) do |f|
  text = f.read
end

text.downcase.gsub(/[^a-z]/, ' ').split.uniq.sort.each do |w|
  if w.size > 1
    sortedword = w.chars.sort.join
    if anagrams[sortedword]
      anagrams[sortedword] << w
    else
      anagrams[sortedword] = [w].to_set
    end
  end
end

result = anagrams.values.select {|s| s.size > 1}
puts "#{result.size} different anagrams found:"
puts
result.sort_by{|s| -s.first.size}.each do |s|
  puts "length #{s.first.size}, matching #{s.size} words: #{s.to_a.join(' ')}"
end
