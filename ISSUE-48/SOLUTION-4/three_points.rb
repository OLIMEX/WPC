#!/usr/bin/env ruby
# three_points.rb

=begin

(C) 2014 C. Prelz <fluido@fluido.as>
This file is in the public domain

Receives the coordinates of three 2D points, like this:

X1 Y1 X2 Y2 X3 Y3

and returns whether the third point is in the same line, rotated clockwise or
rotated anticlockwise WRT the first two

=end

raise "Usage: #{$0} X1 Y1 X2 Y2 X3 Y3" unless(ARGV.length==6)

x1,y1,x2,y2,x3,y3=ARGV.map do |s|
  s.to_f
end

v=(x2-x1)*(y3-y2)-(x3-x2)*(y2-y1) # vector product

if(v==0.0)
  puts("The points are on the same line.")
elsif(v<0.0)
  puts("The points are clockwise.")
else  
  puts("The points are anticlockwise.")
end

