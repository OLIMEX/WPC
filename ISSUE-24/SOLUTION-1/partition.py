import sys

def partition(number):
	answer = set()
	answer.add((number, ))
	for x in range(1, number):
		for y in partition(number - x):
			answer.add(tuple(sorted((x, ) + y)))
	return answer

print partition(int(sys.argv[1]))
