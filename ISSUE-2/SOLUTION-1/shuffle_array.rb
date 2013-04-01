# Author:: Vassil Kalkov

n = 10
max_random = 100

arr = n.times.map { rand(max_random) }

shuffled = arr.each_cons(2).collect { |a,b| a-b }
sorted = shuffled.sort { |x,y| x <=> y }

puts "Given: an array of #{n} random integers from 0 to #{max_random}"
puts "Result: shuffle the integers with their neighbours a[n]-a[n+1] and sort them in ascending order"

puts "\nGiven:"
puts arr.inspect

puts "\nShuffled:"
puts shuffled.inspect

puts "\nResult:"
puts sorted.inspect 




