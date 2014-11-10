#!/usr/bin/env python3
#-*- coding:utf-8 -*-
''' 
 2014-11-09 by kantal59
 License: GPL
 OLIMEX WPC#68: Text Formatting
		 Input text and width, then format the text in this width to be with no spaces at the end of the line. 
		 You can use this text to test your code: http://www.gutenberg.org/files/11/

		 Usage: $ ./textformat.py [ file_name [ -i indent] [ -w width] [ -t tabsize] ]
			file_name: name of text file;
			tab: tabulator value when the input text is parsed;
			indent: the indentation for the first line of output paragraphs;
			width: the width of the ouput text.
		 E.g.: $ ./textformat.py  AliceI.txt -w120 -i2	
'''

import sys

def pformat( paragraph, width=75, indent=2):
	''' Formatting a text paragraph
	
	Newline and tab characters in the input text will be converted into spaces, and consecutive spaces will be converted into one.
	Input: 
		paragraph: a block of text;
		width: the required line width;
		indent: number of spaces for indentation of the first paragraph line;
	Return: the formatted text as string ending with newline;	
	'''

	output,linecount = '',0
	parlist= paragraph.split() 
	if not parlist:		return("\n")

	while parlist:	
	
		words=[]	# a line of the paragraph
		lth = 0
		ind= indent	if not linecount else 0 	# at the begining of the first line of the paragraph, 'indent' number of space must be inserted
		while parlist:
		
			if words:	# line has already some words
				sp= 1 		# before a new word a space must be inserted after the previous word
				ind= 0
			else:		# a new line begins
				sp= 0 		
			
			if ( ind + lth + len(parlist[0]) + sp ) <= width:
				words.append( ind*" " + parlist.pop(0) )
				lth+= sp + len(words[-1])
			
			else:
				if not words:
					words.append( parlist[0][:width])
					parlist[0]= parlist[0][width:]
					lth=len(words[-1])
				break
		
		
		diff= width-lth
		if diff > 0  and  len(words)>=2	and parlist:
			
			while diff:
				for i in range( 0,len(words)-1):
					if not diff:	break
					words[i]= words[i]+" "
					diff-= 1
			
			
		output+= ' '.join(words) + '\n'	# a line is appended
		linecount+= 1
	
	
		
	return( output)				



def get_paragraph( fname, width= 75, indent= 2, tab=8 ):
	''' Get paragraphs from text file and format them
	
	Generator function. 
	Some of the lines of the input text are formed a 
	paragraph if the next line is an empty one or indented more.
	Input:
		fname: name of text file;
		tab: tabulator value when the input text is parsed;
		indent: the indentation for the first line of output paragraphs;
		width: the width of the output text.
	Return: a formatted paragraph.	
	'''
	f=open( fname,"r")
	paragraph= ""
	linesave= ""
	prev_frontsps=0
	for line in f:
	
		if linesave:
			paragraph= linesave
			linesave= ""
			
		if line.strip():	# non empty line
		
			frontsps= 0;
			for ch in line:
				if ch==' ':
					frontsps+=1
				else:
					if ch=='\t':
						frontsps+= tab
					else:
						break	
			
			if prev_frontsps >= frontsps:
				paragraph+= line
			else:
				linesave= line		# put aside for the next paragraph
				paragraph= paragraph.rstrip()
				if paragraph:
					pblock= pformat( paragraph, width=width, indent= indent)
					yield pblock
					paragraph=''
			
			prev_frontsps= frontsps	
			
		else:	# an empty line
			paragraph= paragraph.rstrip()
			if paragraph:
				pblock= pformat( paragraph, width=width, indent= indent)
				yield pblock
				paragraph=''
			yield "\n"
			
	
	if linesave or paragraph:	# there can be some "remainder" at the end of the text file (before the EOF)
		pblock= pformat( linesave+'\n'+paragraph, width=width, indent=indent) # should be revised !
		yield pblock
	
#---------------------------------------------

def get_option( paramstr, opt):

	pp= paramstr.split( opt)
	if len(pp) ==2:
			return( pp[1].split('-')[0] )
	return(None)
			

#---------------------------------------------

if __name__ == "__main__":

	usage= "\n Usage: $ ./textformat.py [ file_name [ -i indent] [ -w width] [ -t tabsize] ]\n"
	
	fname= "AliceI.txt"
	indent= 2
	width= 75
	tab= 8
	
	if len(sys.argv)>1 :	# read the command line parameters
	
		fname= sys.argv[1]
		s=''
		for i in range( 2,len(sys.argv) ):		s+= sys.argv[i]
			
		tmp= get_option( s,"-i")	
		if tmp:		indent= int(tmp)
		tmp= get_option( s,"-w")	
		if tmp:		width= int(tmp)
		tmp= get_option( s,"-t")	
		if tmp:		tab= int(tmp)
		
		if indent<0	or 	indent>=width:
			print( "Invalid 'indent'" + usage);		exit(1);
		if width<2:
			print( "Invalid 'width'" + usage);		exit(2);
		if tab<0:
			print( "Invalid 'tab'" + usage);		exit(3);	


	#print( " File name: {}, width= {}, indent= {}\n".format( fname,width,indent) )
		
	
	for paragraph in get_paragraph( fname, width= width, indent= indent, tab= tab):
	
		print( paragraph,end='')
		
	
	if len(sys.argv) == 1:
		print( usage)

				
		
		
		
	
		
			
		
