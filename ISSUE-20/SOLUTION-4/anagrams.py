#!/usr/bin/env python3
#-*- coding:utf-8 -*-

'''
 2013-08-03 by kantal59
 License: LGPL
 OLIMEX WPC#20: Anagrams
            An anagram is a type of word play, the result of rearranging the letters of a word or phrase to produce a new word or phrase, 
            using all the original letters exactly once; for example 'orchestra' can be rearranged into 'carthorse'. 
            Find all anagram words in text file, you can use as word source our well known: http://fiction.eserver.org/novels/alice_in_wonderland.html

 It works with utf-8 encoded text with Python 3.x, too.
'''
from os import sys

def anagrams( ws): 
    
    for w in ws:
        if len(w)<=1: 
            ws.remove(w)
            continue
            
        wana= set()        
        wd= dict( [ (c, w.count(c)) for c in w ] )
        ws.remove(w)
        
        for v in ws:
            if len(v)!=len(w): continue
            if v==w:  ws.remove(v);  continue
            if wd != dict( [ (c, v.count(c)) for c in v ] ): continue
            wana.add(v)
            ws.remove(v)
            
        if wana:  wana.add(w);  print( wana)
                
   


def normalize( text):
    return( "".join( [ ch.lower() if ch.isalpha() else " " for ch in text ] ) )


def read_text():
    if len(sys.argv)==1:
        print("\nUsage: $> anagrams.py  textfile\n")
        
    try: 
        resource= sys.argv[1] if len(sys.argv) > 1 else "alice.txt"
        print(" -using file: {0}\n".format(resource))
        handle= open( resource, "r")   
        words = normalize( handle.read()).split()
        handle.close()
    except IOError:
        print(" -file access error\n")
        return([])
        
    return( words)




anagrams( read_text())
  
  

  

