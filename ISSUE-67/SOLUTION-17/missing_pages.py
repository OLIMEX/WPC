
index = 0
starter = 0
FALSE = 0
TRUE = 1
starter_found = FALSE

while starter_found == FALSE:
	sum = 0
	starter += 1
	sum = starter
	inc = 0
	while sum <= 9808:
		inc += 1
		sum += inc
		if sum == 9808:
			starter_found = TRUE
			
print "Missing pages are from " + str(starter) + "and " + str((starter + inc))

exit = input("Press button")