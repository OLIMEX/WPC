#! /usr/bin/env python3
# -*- coding: utf-8 -*-
'''
 2013-06-08 by kantal59
 License: LGPL
 OLIMEX WPC#12:
    Problem:  Similar words
    Similar word are these which differs by one character only i.e. one character changed or inserted or deleted.
    For example: if using this concept the word “hello” is considered similar to “hella” and to “hell” or “shello”
    Make code which enters word then scans: http://fiction.eserver.org/novels/alice_in_wonderland.html and prints all 
    similar words to the one which is entered.
  
 It works with utf-8 encoded text, too.
 Python 3.x required for correct utf-8 string handling.
'''

from os import sys
import urllib.request  


def find_similar( verbum, words): 

    pata=[   verbum[:i]+  verbum[i+1:] for i in range(len(  verbum)) ]      # case 1: one char removed
    patb=[   verbum[:i]+" "+  verbum[i:] for i in range(len(  verbum)+1) ]  # case 2: one char inserted, which is represented by space
    patc=[   verbum[:i]+" "+  verbum[i+1:] for i in range(len(  verbum)) ]  # case 3: one char changed, which is represented by space
    rslt1=[ w for w in words if w in pata ]
    rslt2=[ w for w in words if len(w)==len(  verbum)+1 and set([ w[:i]+" "+w[i+1:] for i in range(len(  verbum)+1)]) & set(patb) ]
    rslt3=[ w for w in words if len(w)==len(  verbum) and w!=  verbum and set([ w[:i]+" "+w[i+1:] for i in range(len(  verbum))]) & set(patc) ]
    similar= set(rslt1)|set(rslt2)|set(rslt3)   
    if similar:
        print("The similar words are {}".format(similar) )
    else:
        print("No similar word is found")



def normalize( text):
    return( "".join( [ ch.lower() if ch.isalpha() else " " for ch in text ] ) )


def read_text():
    if len(sys.argv)==1:
        print("\nUsage: $> similar_words.py  textfile_or_http_url \n")
        
    resource= sys.argv[1] if len(sys.argv) > 1 else 'http://fiction.eserver.org/novels/alice_in_wonderland.html' 
    print(" -using resource '{}'".format( resource))
           
    if resource.startswith('http'):
        handle = urllib.request.urlopen( resource)  # The html code in the webpage is read, too, and isn't dealt with.
        words= normalize( handle.read().decode('utf-8')).split()     # assume utf-8 encoding
    else:    
         handle= open(resource, 'r')
         words = normalize( handle.read()).split()
    
    handle.close()
    return( words)



def main():       
  words= read_text()
  while True:     
        try:   
            w= input("\nEnter the word (exit ctrl-c):")
        except KeyboardInterrupt:
            print()
            sys.exit(0)     
        find_similar( w.lower().strip(), words )


main()



