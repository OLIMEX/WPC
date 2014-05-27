#!/usr/bin/env python3
#-*- coding:utf-8 -*-

''' 
 2014-06-15 by kantal59
 License: LGPL
 OLIMEX WPC#57: Text to HTML ratio calculator
 			Some people think text to HTML tags ratio on web page is important parameter for Google indexing 
 			and good sites should have about 20-30% ratio of pure text vs HTML tags.
			Make code which calculates Text/HTML ratio on given html page.
		
			It uses BeautifulSoup:	 http://www.crummy.com/software/BeautifulSoup/bs4/doc/
			On Ubuntu:  apt-get install  python-bs4
'''

import bs4 as bs
import urllib.request 
import sys


resource= "http://olimex.wordpress.com/2014/06/13/weekend-programming-challenge-week-57-text-to-html-ratio-calculator"
if len(sys.argv) !=2:
	print( "\n Usage: $ ./htmlratio.py  url | local_html_file\n" )
else:
	resource= sys.argv[1]	
	
if  resource.startswith('http'):
		handle= urllib.request.urlopen( resource)  
else:
		handle= open(resource, 'r')
        
        
istr= handle.read()
soup = bs.BeautifulSoup(istr)

print( "\n Resource {0}".format(resource)  )
lth_total= len(istr); 				print("- length: {0}".format(lth_total) )
lth_text= len( soup.get_text()); 	print("- length of extracted text: {0}".format(lth_text) )

lth_script= 0
for tag in soup.find_all("script"):
	lth_script+= len( str(tag.string))
print("- length of scripts: {0}".format(lth_script) )

lth_style= 0
for tag in soup.find_all("style"):
	lth_style+= len( str(tag.string))
print("- length of styles: {0}".format(lth_style) )

# Not an exact ratio but it will do.
print( "- the 'interesting' content/total ratio is about {0:3.1f}%\n".format( (lth_text-lth_script-lth_style)*100/lth_total )  )



