#! /usr/bin/env python
# -*- coding: utf-8 -*-
'''
 2013-07-26 by kantal59
 License: LGPL
 OLIMEX WPC#19: Pattern match
         Make function match() which takes as input input_string and pattern_string, the input strings may contain any ASCII codes
        there are two special codes for use in the pattern-string: ?-replaces 1 character and * – replaces any character(s)
        The function should print all words from the input-string which match the pattern-string
        words can be separated by any of these characters: ‘ ” . , : ;  
        If the input-string have this content “The big black cat jump over the window”

        if pattern-string is “b*” should print
            big
            black

        if pattern-string is “*c*” should print
            black
            cat

        if pattern-string is “?i*” should print
            big
            window
 
'''

import sys,string

# The algorithm
def compare( word,patt):

    if not word and not patt: return( True)
    if not patt: return( False)
    if not word:
        if patt[0]=='*' and len(patt)==1: return( True)
        return( False);
    if word[0]==patt[0] and compare( word[1:], patt[1:]) : return( True)
    if patt[0]=='?' and compare( word[1:], patt[1:]): return( True)
    if patt[0]=='*' and ( compare( word[1:], patt[:]) or compare( word[1:], patt[1:]) or compare(word[:],patt[1:]) ): return( True)
    return( False)


# The main routine
def match( inp, patt):
    inp= "".join( [ ch if ch not in string.punctuation else " " for ch in inp  ] ).split()
    return( [ w for w in inp if compare(w,patt) ] ) 

    
#------------------------------
#       T E S T I N G
#------------------------------  
  
text= "The,big., black: cat jump over the window!"
patterns=[ "b*", "*c*", "?i?", "?i*", "???", "?", "*", "****", "o?*", "jump", "window?", "window*", "*window*","", ]
if len(sys.argv)==1: print("\nUsage: $> pattmatch.py 'pattern' ['input_string']\n")
if len(sys.argv)>=2: patterns=[ sys.argv[1] ]
if len(sys.argv)==3: text= sys.argv[2]
        
for pa in patterns: print(" input: {0}\n pattern: '{1}'\n matches: {2}\n".format( text, pa, match( text, pa) ) )




