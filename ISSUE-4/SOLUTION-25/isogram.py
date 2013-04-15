#! /usr/bin/env python3
# -*- coding: utf-8 -*-

'''
 2013-04-14 by kantal59
 License: LGPL
 OLIMEX WPC#4:
    It scans text and displays the longest isogram word(s) (with all letters different) found in the text.
    
 Python 3.x required for correct utf-8 string handling.
'''
from os import sys

'''
 isogram( text, rlist)
 text: utf-8 encoded string
 rlist: a list for isogram words have the same length, can be empty or contains the result of a previous call to the routine.
'''
def isogram(  text, rlist):

    if len(rlist) :
        length= len( rlist[0])
    else:
        length=0
    
    txt= normalize( text)    
    for word in  txt.split():   # splits into words
        if len(word) < length or word in rlist:    
            continue            # does not check shorter words than the one(s) found, and the repeated words
        flag=True
        for pos in range(len(word)):
            if word[pos] in word[pos+1:]:
                flag=False                    
                break    
    
        if flag:                # an isogram word found
            if len(word) > length:
                del rlist[:]   # a longer one found
                length= len(word)                    
                
            rlist.append(word)
                
    return                

 
 
def normalize( text):    
    sl=[]
    for i in range( len(text)):            
        if text[i].isalnum():
            sl.append( text[i].lower())     # converts alphanumeric chars into lower case
        else:
             sl.append(" ")                 # converts non alphanumeric char into space (preserves the word separation role too)
    return( "".join(sl))                           

    
#------------------------------
#       T E S T I N G
#------------------------------                

if len(sys.argv)!=2:
    print("\nUsage: $> isogram.py  utf8_or_plain_text_file\n")
else:    
    ftext= open( sys.argv[1],"r")
    result= []
    for line in ftext:   # save memory with splitting the file into lines
        isogram( line, result)
    ftext.close()     
    print("{0} isogram word(s) found with length {1}\n{2}\n".format( len(result), len(result[0]), result) )
       
        
        

