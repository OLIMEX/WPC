# wpc week 67 missing book pages

def book(n):  
	"""sum of natural numbers from 1 to n, where n is number od pages (not cutted book)"""
	s=n*(n+1)/2
	return s

def missing(start,stop):	
	"""
	sum of natural numbers from start to stop 
	"""
	missing=sum([i for i in range(start,stop+1)])
	return missing

# number of book pages
# start from pages=140	# max number of pages to satisfy sum of missing pages==9808
# book should have 140 or more pages

for pgs in range(140,2000):	# last book is with 2000 pages
	diff=9808
	start=1;stop=1                  # let's start with first page missing?
	while stop<=pgs:				# we have to stop at last page!
		razlika=missing(start,stop)
		if razlika>diff:
			start=start+1
		elif razlika<diff:
			stop=stop+1
		elif razlika==diff:
			print "book pages ",pgs
			print "missing pages from ",start,"to ",stop
			print "check sum of missing pages ",missing(start,stop)
			start=start+1      # let's find another range
			#break #in case of only one solutions per book

