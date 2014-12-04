#!/usr/bin/env python3
#-*- coding:utf-8 -*-

''' 
 2014-11-30 by kantal59
 License: GPL
 OLIMEX WPC#70: Math with words
		
		 It uses integer numbers as input.
		 Operators allowed: 'plus', 'minus', 'divided by', 'times' .
		 Parenthesis not allowed.
		 My mathwords.py module must be imported.
		 Usage example: $ ./startmath.py  thirty-two plus five hundred divided by two
		 Not thoroughly tested!
'''
import sys
import mathwords as mw


operators= [ ('plus','+'), ('minus','-'), ('times','*'), ('divided','/') ]
drops= [ 'by', 'is','equal','to' ]

def do_math( text):

	tokens= text.split()
	tokens= [ tok for tok in tokens if tok not in drops ]
	
	inp=[]
	start=0
	for i,tok in enumerate( tokens):
		for ops,op in operators:
			if tok == ops:
				ok,num= mw.words2number( ' '.join(tokens[start:i]) )
				if not ok:		return( False, num)
				inp.append( str(num))
				inp.append( op)
				start= i+1
				break
	
	if start < (len(tokens)):
		ok,num= mw.words2number( ' '.join(tokens[start:]) )
		if not ok:		return( False, num)
		inp.append( str(num))
		
	inp= ' '.join(inp)
	#print(inp)	
	try:
		val= eval( inp )
	except:
		return( False, " Evaluation error")
			
	return( True, val )				





if __name__ == "__main__":

	testdata= [ "three thousands five hundreds and twenty five plus one hundred and thirty three is equal to",
				" six hundred divided     by fifteen " ,
				"two times two plus four ",
				"forty-two divided by two plus ten times ten"]

	if len(sys.argv) > 1:	testdata= [ " ".join( sys.argv[1:]) ]
	else:	print("\n Usage example: $ ./startmath.py  thirty-two plus five hundred divided by 2\n")

	for s in testdata:
		ok,val= do_math(s)
		if not ok:
			print(" Error: {} in '{}'".format(val,s) )
		else:
			print(" {}: '{}'".format(val,s))
		
		
		

