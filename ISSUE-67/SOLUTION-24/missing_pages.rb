#
# Olimex Weekend Programming Challenge #67 - Missing Pages in Book
# 
# quick ruby hack, submitted by teqster@gmail.com
#
# So 5. Okt 23:45:05 CEST 2014
#

SUM = 9808

#Gaussian sum
def g(s)
  (s*s + s)/2
end

cnt = 1

# Very poor man's version of finding the ceiling sum
while g(cnt) < SUM
  cnt += 1
end

# g(cnt) now has the ceiling sum - the sum of page numbers for the complete book
MISSING = g(cnt) - SUM

# MISSING now contains the distance between the complete book number sum, and SUM
# probing each possible consequtive pages-combination equaling or below MISSING
MISSING.downto(1).each do |m|
  msum = 0
  cnt = m
  # trying to add up consequitive numbers
  while msum < MISSING and cnt > 0
    msum += cnt
    cnt -= 1
  end
  # matching?
  if msum == MISSING
    puts "possibly missing pages: #{if cnt+1 == m then "#{m}" else "#{cnt+1}..#{m}" end}"
  end
end
