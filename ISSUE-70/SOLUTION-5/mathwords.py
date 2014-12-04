#!/usr/bin/env python3
#-*- coding:utf-8 -*-
''' 
 2014-11-30 by kantal59
 License: GPL
 OLIMEX WPC#70: Math with words
		 Make code which enters expression like “3525 + 133 =” and solve it. Easy right? Here is the catch is that numbers 
		 and operations are replaced by their words equivalents.
		 Please support numbers up to 1 000 000 and these operators + – * /
		 Example:
		 input: "three thousands five hundreds and twenty five plus one hundred and thirty three is equal to"
		 output: "3658"
		 
		 This module convert text into integer number and doesn't make math.
		 Not thoroughly tested!
'''

import sys


numbers= [ ('zero',0),('one',1),('two',2),('three',3),('four',4),('five',5),('six',6),('seven',7),('eight',8),('nine',9),('ten',10),
 ('eleven',11),('twelve',12),('thirteen',13),('fourteen',14),('fifteen',15),('sixteen',16),('seventeen',17),('eighteen',18),('nineteen',19),
 ('twenty',20),('thirty',30),('forty',40),('fifty',50),('sixty',60),('seventy',70),('eighty',80),('ninety',90) ]
 
_numbers= [ s for (s,n) in numbers ]

powers= [ ('thousand',1000), ('million',int(1e6)), ('billion',int(1e9)) ]


#--------------------------------------
def words2number( numtext):
#--------------------------------------

	# --- Validation:
	tokens= numtext.replace('-',' ').lower().split()		# e.g.: "thirty-nine" -> "thirty nine"
	tokens=[ tok for tok in tokens if tok not in [ 'and','a'] ]
	if not tokens:	return( True,0)
	if "zero" in tokens		and 	len(tokens) != 1:	return( False,' Only a single zero acceptable')
	
	pcount=0
	for i,tok in enumerate(tokens):
		if tok == "hundreds":	tokens[i]= "hundred";	continue
		if tok == "hundred": 	continue
		if tok in _numbers:		continue
		found= False
		for s,n in powers:
			if tok == s:	found=True;	break
			if tok == s+'s':	found=True;	tokens[i]= s;	break
			
		if not found:	return( False, " Invalid token")
	
	for s,n in powers:
		if tokens.count(s) <= 1 :		continue
		return( False, " Only a single occurrence is allowed for powers of ten ")
	
	
	powers.sort(reverse=True, key= lambda p: p[1] )	# important for partitioning order, see <*>
	multiplier= powers[0][1] + 1
	
	sentence= " ".join(tokens)
	
	# --- Calculation:
	summ= 0
	while sentence:
		
		foundpow= False
		for s,n in powers:
						
			part= sentence.partition(s)		# <*>
			part= [ s.strip() for s in part ]
			if not part[1]:		continue
			foundpow= True
			if n >= multiplier:		return( False, " Incorrect order of powers of ten")
			multiplier= n
			if not part[0]:
				summ+= n
			else:
				ok,val= _get_100s( part[0])	
				if not ok:	return( False, val)
				summ+= n*val
			
			sentence= part[2]	
		
		if foundpow:	continue
		
		# get the remainder of the string:
		ok,val = _get_100s( sentence)
		if  not ok:		return( False, val)
		summ+= val
		break
		
	return(True,summ)	
	


#-------------------------------
def _get_10s( text):				# six; thirty two;  fourty
#-------------------------------

	parts= text.split()
	if not parts:		return(True,0)
	if len(parts) > 2:	return( False," Invalid format[1]")
	val=0
	found= False
	for s,n in numbers:
		if s == parts[0]:
			if n < 20  and  len(parts)==2 :		return( False," Invalid format[2]")
			val= n
			found= True
			break
	
	if not found:	return( False," Invalid format[3]")
	if len(parts)==2:
		found= False
		for s,n in numbers:
			if s == parts[1]:
				if n > 9 :	return( False," Invalid format[4]")
				val+= n
				found= True
				break
	
	if not found:	return( False," Invalid format[5]")
	
	return( True,val)


#------------------------------
def _get_100s( text):		# three hundred eleven; one;  fourty nine; one hundred fourty nine; hundred
#------------------------------
	
	if not text:	return(True,0)
	
	part= text.partition("hundred")
	part= [ s.strip() for s in part ]

	v1,v2 = 0,0
		
	if part[0]:
		ok,v1=	_get_10s( part[0])
		if not ok:		return( False, v1)
	
	if part[2]:
		ok,v2=	_get_10s( part[2])
		if not ok:		return( False, v2)	
		
	if part[1]:		# 'hundred' exists
		if not part[0]:
			v1= 100
		else:	
			if v1 > 9:	return( False, " Incorrect format")
			v1*= 100
		
	return( True, v1+v2 )
			
#------------------------------------------------------------------------


if __name__ == "__main__":

	testdata= [ "four hundred and thirty-two million five hundred and ninety eight thousand three hundred and fifteen",
			"one hundred",
			"hundred",
			" a thousand",
			"thousand",
			"thousand hundred",	# 1100
			"hundred thousand", # 100 000
			"hundred one thousand",	# 101 000
			"thirty-two",
			"six",
			"one million and two",
			"seven thousands five hundred",
			"seven thousand and fifty-nine",
			"zero",
		  ]
		  

	if len(sys.argv) >1 :	testdata= [ " ".join( sys.argv[1:]) ]
	else:	print("\n Usage example: $ ./mathwords.py   four hundred thirty-nine\n");


	print()
	for text in testdata:
		ok,v = words2number( text)
		if not ok:
			print(" Error: {} in '{}'".format(v,text) )
		else:
			print(" {}: '{}'".format(v,text))

	print()	
		



