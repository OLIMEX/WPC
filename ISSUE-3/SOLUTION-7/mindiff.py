#! /usr/bin/env python3
# -*- coding: utf-8 -*-

'''
 2013-04-06 by kantal59
 License: LGPL
 OLIMEX WPC#3: 
	 Let’s have N different strings/words and for each word print the minimum part of it which makes it unique toward others.	
	
 Python 3.x version required.
 input: the 'testdata' list (see below) or a file with new line separated utf-8 encoded strings
 It can works case sensitive and insensitive.
'''

from os import sys

CASE_SENSITIVE= False
#CASE_SENSITIVE= True
#------------------------------
def mdiff( inp, result):
    for idx in range(0, len(inp)):	# get an input string

	    lth= len(inp[idx])
	    result.append("")
	    for l in range(1, lth+1):	   # pattern's length

		    for pos in range(0, lth):  # pattern's position
			    if pos+l > lth:
				    break;
			    patt= inp[idx][pos:pos+l]
			    found= False
			    for jdx in range(0, len(inp)):
				    if jdx==idx :
					    continue
				    if CASE_SENSITIVE:
					    if patt in inp[jdx]:
						    found=True	# pattern isn't unique
						    break		# get a new pattern from the next position with the current length
				    else:
					    if patt.lower() in inp[jdx].lower():
						    found=True	
						    break					
				
			    if not found:	
				    result[idx]= patt # unique pattern is found for that input string
				    break			  # go to find a unique pattern for the next input string
		    if not found:
			    break	# go to find a unique pattern for the next input string
		    # continue to get a new pattern with increased length


#------------------------------
def rprint( inp, result):
    print("CASE_SENSITIVE: {0}".format(CASE_SENSITIVE))
    for i in range(0, len(inp)):
	    print( "[{0}]-->[{1}]".format( inp[i],result[i]) )

#------------------------------
#       T E S T I N G
#------------------------------
#testdata=["A13-OLinuXino","iMX233-OLinuXino","MOD-PULSE","MOD-IO"] 	
# case insensitive result: 'A', '2', 'P', '-I'
# case sensitive result:   'A', '2', 'P', 'I'

#testdata=[ "Hello World!", "Helló világ!", "здрависване свят!", "Hallo Welt!" ]
#testdata=["Öü óőÚáé","Öü ÉóőÚÁé"]
#testdata=["string1","string2","string2 ", "string3"]
testdata=["12345","54321","12354","A13-OLinuXino","iMX233-OLinuXino","MOD-PULSE","MOD-IO" ]


if len(sys.argv)==1:
    print("\nUsage: $> mindiff file\nThe file contains new line separated utf-8 strings\n")
else:    
    fil= open( sys.argv[1],"r")
    testdata=[]
    for line in fil:
        testdata.append( line.rstrip("\r\n"))
    fil.close()     
        

result=[]
mdiff( testdata, result)
rprint( testdata, result)



