#!/usr/bin/python


START_A = 10
MAX_A   = 500

START_N = 10
MAX_N   = 500

def calculate_a_and_n(sn, d):
	""" This function calculates the intial term, a and the number of 
	terms in the arithematic sequence given a valid sum, sn and 
	difference term d.
	This it does by brute force, substituting possible values in a
	range of numbers, set by START_A, MAX_A, START_N and MAX_N.
	The formula used here is 
	Sn = n/2*(2*a + (n-1)*d)
	"""
	rhs = 2*sn
	for a in range (START_A, MAX_A):
		for n in range (START_N, MAX_N):
			lhs = n * (2*a + (n - 1) * d)
			if lhs == rhs:
				return (a, n)
	
	#return None if we are not able to find a solution			
	return None
	
def print_the_consecutive_pages(a, n):
	""" Prints the page numbers that are missing. Just have to count 
	from a, a+1, a+2 ..... n trems"""
	
	Sn = []
	print "The missing consecutive pages are: "
	for page in range(0, n):
		Sn.append(a+page)       # for testing
		print "%d " %(a+page),
		if (n % 10) == 0:
			print
			
	return Sn


if __name__ == '__main__':
	Sn = 9808
	d = 1    # For consecutive pages d trem in AP is 1
	
	retVal = calculate_a_and_n(Sn, d)
	if retVal != None:
		series = print_the_consecutive_pages(retVal[0], retVal[1])
		if sum(series) != Sn:
			raise ValueError, "Something has gone horribly wrong :("
		
		
	
	
	
	
