#!/usr/bin/env ruby
#
# Olimex Weekend Programming Challenge Issue #21 - Words Puzzle
#
# Javier Donaire

ARGF.each {|l| puts l.gsub(/\w{3,}/){|w| w[0] + w[1..-2].chars.to_a.shuffle.join + w[-1]}}
