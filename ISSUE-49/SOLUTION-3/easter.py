# -*- coding: utf-8 -*-
import math
import sys

## Western Easter in the Gregorian calendar
#
#  Calculation according to Lilius-Clavius
#  Algorithm from Knuth - The Art of Computer Programming
#  Year must be after 1582
def western(year):	
	a = (year % 19) + 1
	b = math.trunc(year / 100) + 1	 
	c = math.trunc((3 * b) / 4) - 12
	d = math.trunc((8 * b + 5) / 25) - 5
	e = math.trunc((year * 5) / 4) - 10 - c
	f = (11 * a + 20 + d - c) % 30

	if f < 0:
		f += 30

	if f == 24 or (f == 25 and a > 11):
		f += 1

	g = 44 - f

	if g < 21:
		g += 30 	 

	month = 3
  	day = g + 7 - ((e + g) % 7) 

	if day > 31:
		month = 4
		day = day - 31

	return (day, month, year)

## Convert Julian date to Gregorian date
#
#  Ref http://home.roadrunner.com/~hinnant/date_algorithms.html
def julian_to_gregorian(day, month, year):
	if month <= 2:
		year -= 1

	if year >= 0:
	 	era = math.trunc(year / 4)
	else:
		era = math.trunc(year - 3 / 4)

	yoe = year - era * 4

	if month > 2:
		doy = math.trunc((153 * (month - 3) + 2) / 5) + day - 1
	else:
		doy = math.trunc((153 * (month + 9) + 2) / 5) + day - 1

	doe = yoe * 365 + doy
	z = era * 1461 + doe - 2

	if z >= 0:
		gera = math.trunc(z / 146097)
	else:
		gera = math.trunc(z - 146096 / 146097)

	gdoe = z - gera * 146097
	gyoe = math.trunc((gdoe - math.trunc(gdoe/1460) + math.trunc(gdoe/36524) - math.trunc(gdoe/146096)) / 365)    
	gy = gyoe + gera * 400
	gdoy = gdoe - (365 * gyoe + math.trunc(gyoe / 4) - math.trunc(gyoe / 100))
	gmp = math.trunc((5 * gdoy + 2) / 153)
	gd = gdoy - math.trunc((153 * gmp + 2) / 5) + 1

	if gmp < 10:
		gm = gmp + 3
	else:
		gm = gmp - 9

	if gm <= 2:
		gy += 1

	return (gd, gm, gy)

## Orthodox Easter, converted to Gregorian calender
#
#  Calculation according to Claus Tøndering (www.tondering.dk), based on Oudin's algorithm
def orthodox(year):
	G = year % 19
	I = (19 * G + 15) % 30
	J = (year + math.trunc(year / 4) + I) % 7
	L = I - J
	month = 3 + math.trunc((L + 40) / 44)
	day = L + 28 - 31 * math.trunc(month / 4)
	return julian_to_gregorian(day, month, year)
	
## Display date of Western and Orthodox Easter for a given year
def process(year):
	if year <= 1582:
		print "Year must be after 1582"
	else:
		western_easter = western(year)
		print "Western Easter is on {0[0]}/{0[1]}/{0[2]} in {0[2]}".format(western_easter)		
		orthodox_easter = orthodox(year)
		print "Orthodox Easter is on {0[0]}/{0[1]}/{0[2]} in {0[2]}".format(orthodox_easter)	

def main(argv=None):
	if argv is None:
		argv = sys.argv
	if len(argv) == 1:
		year = int(raw_input("Enter a year: "))
		process(year)		
	else:
		for year in argv[1:]:
			process(int(year))

if __name__ == "__main__":
    sys.exit(main())

