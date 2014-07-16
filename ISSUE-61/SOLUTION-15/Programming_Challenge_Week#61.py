"""
Problem:
insert + and - in the equation below to make it right
1 2 3 4 5 6 7 8 9 = 100
like
1 + 2 + 3 - 4 + 5 + 6 + 7 8 + 9 = 100
make code which  finds all solutions.

This is the Result for the Challange:
All solutions with leading +
Found solution:+1+2+3-4+5+6+78+9 = 100
Found solution:+1+2+34-5+67-8+9 = 100
Found solution:+1+23-4+5+6+78-9 = 100
Found solution:+1+23-4+56+7+8+9 = 100
Found solution:+12+3+4+5-6-7+89 = 100
Found solution:+12+3-4+5+67+8+9 = 100
Found solution:+12-3-4+5-6+7+89 = 100
Found solution:+123+4-5+67-89 = 100
Found solution:+123+45-67+8-9 = 100
Found solution:+123-4-5-6-7+8-9 = 100
Found solution:+123-45-67+89 = 100

This is an aditional Result for a minus befor the equation:
All solutions with leading -
Found solution:-1+2-3+4+5+6+78+9 = 100

There is also the possebility to calculate other target values and other number lengths 

"""


# Calulate one Operator
def proccesnext(result, calcbuffer ,fac , operator, number):
	buf=0
	if(operator=="+"):
		ret=result+(calcbuffer+number)*fac	# Addition
		fac=1
	elif(operator=="-"):				
		ret=result-(calcbuffer+number)*fac	# Subtraction
		fac=1
	else:						# no Opperator
		ret=result				# do not change Result
		buf=(calcbuffer+number)/10.0		# calculate for number with multiple digits
		fac=fac*10				# calulate factor for scaling later
	return (ret,buf,fac)

# Calculates the result of one Possible solution
def checkSolution(pattern):
	res=0
	buf=0
	fac=1
	for n in range(1,len(pattern)+1): #Start from behind because operator is in front.
		i=len(pattern)+1-n
		(res,buf,fac)=proccesnext(res, buf ,fac , pattern[i-1], i)
	return res


# Print Solution in a nice format
def printSolution(pattern,expected):
	string=""
	for n in range(1,len(pattern)+1):
		string=string+pattern[n-1]+str(n)
	print("Found solution:" + string.replace(" ", "")+" = "+str(expected))

# recursive function for cheking all posibilities
def recursiveCheck(pattern,length,expected):
	possibilities = ["+","-"," "]
	if(len(pattern)==length):
		if expected==checkSolution(pattern):
			printSolution(pattern,expected)
	else:
		for i in possibilities:
			recursiveCheck(pattern+i,length,expected)
	
## main
print("This is the Result for the Challange:")
print("All solutions with leading +")
recursiveCheck("+",9,100) # this is the Result for the Challange
print("\nThis is an aditional Result for a minus befor the equation:")
print("All solutions with leading -")
recursiveCheck("-",9,100)

# uncomment Below to prints all solutions for combinations from 7 to 10
# there is mor possible but it is a lot of output
"""
print("\n")
for length in range (7,10):
	print("\nall Solutions for "+str(length)+"with leading +\n")
	recursiveCheck("+",length)
	print("\nall Solutions for "+str(length)+"with leading -\n")
	recursiveCheck("-",length)
"""
