#! /usr/bin/env python3
# -*- coding: utf-8 -*-
#
# 2014-09-06 by kantal59 
# License: LGPL
# OLIMEX WPC#63: Braille encoder
#			Braille is a tactile writing system used by the blind and the visually impaired. It is traditionally written 
#			with embossed paper. Generally with three lines of embossed dots either convex either concave.
#			Make Braille encoder which takes string and prints Braille equivalent on 3 lines with “*” for convex and “.” 
#			for concave dots. How do you print “helloworld”?
#
#			Resource:
#				World Braille Usage ( Third Edition, Perkins, International Council on English Braille,	Library of Congress, UNESCO, 2013)
#
#			Not fully tested and the tables may be incorrect!
#
#--------------------------------------------------------
class Braille:

	def __init__(self, name, simpletbl ):
		self.name= name
		self.simple= simpletbl
		self.number= '3456'
		#self.capital= '6'
		#self.italics= ('46','23')
		#self.bold= ('45','23')
		self.left_quote= '236'	 # "
		self.right_quote= '256'
		self.left_single_quote= ('6','236')  # '
		self.right_single_quote= ('6','356')
		
#--------------------------------------------------------		
UEB= Braille( 'Unified English Braille (UEB)',
			[
			('a','1'),('b','12'),('c','14'),('d','145'),('e','15'),('f','124'),('g','1245'),
			('h','125'),('i','24'),('j','245'),('k','13'),('l','123'),('m','134'),('n','1345'),
			('o','135'),('p','1234'),('q','12345'),('r','1235'),('s','234'),('t','2345'),('u','136'),
			('v','1236'),('w','2456'),('x','1346'),('y','13456'),('z','1356'),
			
			(',','2'),(';','23'),(':','25'),('.','256'),('?','236'),('!','235'),('`','3'),
			('(','5','126'), 	
			(')','5','345'),
			('[','46','126'),
			(']','46','345'),
			('-','36'), 
			('_','46','36'),
			('/','456','34'),
			('*','5','35'),
			(' ',None)
			]
)

Bulgarian= Braille( "Bulgarian Braille",
					[
					('a','1'),('б','12'),('в','2456'),('г','12145'),('д','145'),('е','15'),('ж','245'),('з','1356'),
					('и','24'),('й','13456'),('к','13'),('л','123'),('м','134'),('н','1345'),('о','135'),('п','1234'),
					('р','1235'),('с','234'),('т','2345'),('у','136'),('ф','124'),('х','125'),('ц','14'),('ч','12345'),
					('ш','156'),('щ','1346'),('ъ','12356'),('ь','23456'),('ю','1256'),('я','1246'),
								
					(',','2'),(';','23'),(':','25'),('.','256'),('?','26'),('!','235'),
					('(','2356'), 	
					(')','2356'),
					(' ',None)
					]
)
					
Bulgarian.left_quote= '236'	 # "
Bulgarian.right_quote= '256'
Bulgarian.left_single_quote= '236'  # '
Bulgarian.right_single_quote= '356'
			
#--------------------------------------------------------			
def append_code( res, codes):
	res.extend( codes if type(codes) is tuple else (codes,) )

#convex='*'
convex='⚫'
#concave='.'
concave='⚬'

import sys

#--------------------------------------------------------			

def encode( tbl, textlist):

	rslt=[]
	for text in textlist:

		num= quote= single_quote= False
		for ch in text.lower():
		
			if ch in '1234567890':
				if ch=='0':		ch='10'
				if not num:
					num= True;		
					append_code( rslt, tbl.number )
				
				append_code( rslt, tbl.simple[ int(ch)-1][1:] )
				continue		

			if num and rslt[-1]!=None:	rslt.append(None)
			num= False	
			found= False
			if ch=='"':
				if not quote:
					quote=True
					append_code( rslt, tbl.left_quote )
					continue
				quote=False
				append_code( rslt, tbl.right_quote)	
				continue
			
			if ch=="'":
				if not single_quote:
					single_quote=True
					append_code( rslt, tbl.left_single_quote )
					continue
				single_quote=False
				append_code( rslt, tbl.right_single_quote)
				continue
				
			for seq in tbl.simple:
			
				if seq[0] != ch:	continue
				rslt.extend( seq[1:] )
				found= True
				break
	
		rslt.append(None)				
		if found:	continue	
			
	
	print( textlist)
	print(rslt)

	for (r1,r2) in [ ('1','4'), ('2','5'), ('3','6') ]:
		for code in rslt:
		
			if not code:	# None
				print('  ', end='')
			else:
				print( convex if r1	in code else concave, end='')
				print( convex if r2	in code else concave , end='')
	
		print(' ')
		
	print('');
 				
#--------------------------------------------------------	



task= [ (UEB,["Hello", "World! 12345"]),	(Bulgarian, ["Здравей, свят", "12345"] ) ]
if len(sys.argv) >=2:
	task= [ (UEB, sys.argv[1:] ) ]
else:
	print(" Usage: $./braille.py text1 text2 ...")				

for tbl, textlist in task:
	print("\nTable used: {}\n".format(tbl.name))
	encode( tbl, textlist)
		
	
	
	
