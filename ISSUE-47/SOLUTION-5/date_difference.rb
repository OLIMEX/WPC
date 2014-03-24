#!/usr/bin/env ruby
# date_difference.rb

=begin

(C) 2014 C. Prelz <fluido@fluido.as>
This file is in the public domain

Receives two dates as parameters (format yyyy/mm/dd) and prints out
the difference in years, months and days.

=end

require 'date'

raise "Usage: #{$0} date_1 date_2 (yyyy/mm/dd)" unless(ARGV.length==2)

d1=nil
d2=nil

begin
  d1=Date::parse(ARGV[0])
  d2=Date::parse(ARGV[1])
rescue => err
  puts("Bad parameters! (#{err})")
  exit(1)
end

if(d1>d2)
  puts("Second date older.")
else
  puts("First date older.")
  t=d1
  d1=d2
  d2=t
end

puts("Difference: #{d1.year-d2.year-(d1.yday<d2.yday ? 1 : 0)} years, #{(d1.year*12+d1.mon)-(d2.year*12+d2.mon)-(d1.day<d2.day ? 1 : 0)} months, #{(d1-d2).to_i} days. ")
