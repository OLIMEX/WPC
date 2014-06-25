-- Date to seconds since 0 AD calculator

print "Enter the date in a Day/Month/Year format as such 21/06/2014"

date = io.read()

days = string.sub(date, 1, 2)

months = string.sub(date, 4, 5)

year = string.sub(date, 7, string.len(date))

if (year % 4 == 0)
  then
  leap = true
else
  leap = false
end

year = year - 1 -- current year only partial

nonLeapExtra = year % 4
year = (year - (year % 4))

days = (days + ((year/4) * ((365 * 3) + 366))) -- add groupings of four years to days
days = days + (nonLeapExtra * 365)

daysPerMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}

if leap
  then
  daysPerMonth[2] = 29
else
  ;
end

for i=1, (months - 1) --current month partial
  do
    days = days + daysPerMonth[i]
  end
  
  seconds = days * 24 * 60 * 60
  
  print(seconds, "seconds since 0 AD")