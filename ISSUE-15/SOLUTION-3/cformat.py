#! /usr/bin/env python
# -*- coding: utf-8 -*-
'''
 2013-06-30 by kantal59
 License: LGPL
 OLIMEX WPC#15:
    Problem:  Make code which reads not formaтted C language text file and format the brackets i.e. 
    moves the closing bracket as same column as the corresponding opening bracket, ignoring the comments. 
    If the brackets doesn’t match should issue error message.
  
 It puts the opening and closing curly brackets  in the same column.
 It puts every instructions ending with ';' in a new line, except the initialization and condition instructions of 'for'.
 It removes all the comments to ease its work.
 ( It beautifies scrambled 'switch' blocks but not perfect yet.)
'''

import sys


def remove_comments( s):

    cs= s.find("/*")    
    pp= s.find("//")

    if cs!= -1 and ( pp==-1 or pp > cs ):
        ccs= s.find("*/",cs+2)
        if ccs== -1:    return("") # error
        return( remove_comments(s[:cs]+ " "+ s[ccs+2:]))     

    if pp != -1:
        nl= s.find("\n",pp+2)               
        if nl == -1:    return("") # error
        return( remove_comments(s[:pp]+ " "+ s[nl+1:]))

    return( s[:])        
        


blocks=0
switches=[]
def scan_start(s):
    global blocks, switches
    blocks=0
    switches=[]
    scan(s)



def scan( s):
    global blocks, switches
    
    s=s.strip()
    if not s:  return      # empty line
     
    binc= 1 if switches and switches[-1]< blocks else 0
    bcase=0
   
        
    semicolon= s.find(";")
    obrace= s.find("{");
    cbrace= s.find("}");
       
    if s.startswith("switch"):      switches.append(blocks+1)            
           
    if s.startswith("case") or s.startswith("default"):   
        bcase=-1
               
    if s[0:3]=="for":
        ob= s.find("(",3)       
        if ob==-1: 
            print("\n---- ERROR(1): malformed 'for' ----\n")
        count=1
        for i in range(ob+1, len(s)):
            if s[i]==")":   count-=1
            if s[i]=="(":   count+=1
            if count==0: 
                print("{0}{1}".format("\t"*(blocks+binc+bcase), s[:i+1].strip()))
                scan( s[i+1:])
                return; 
        print("\n---- ERROR(2): malformed 'for' ----\n")
        sys.exit(1)
       
    if semicolon!= -1 and (obrace==-1 or semicolon< obrace) and (cbrace==-1 or semicolon< cbrace):
        print("{0}{1}".format("\t"*(blocks+binc+bcase), s[0:semicolon+1].strip() ) )        
        scan( s[semicolon+1: ])
        return
    
    if obrace!=-1 and (cbrace==-1 or obrace < cbrace):
        print("{0}{1}\n{2}{{".format("\t"*(blocks+binc+bcase), s[:obrace].strip(),"\t"*(blocks+binc+bcase)) )
        blocks+=1
        scan( s[obrace+1:])
        return;
    
    if cbrace!=-1 and (obrace==-1 or cbrace<obrace):
        if blocks==0:
            print("\n---- ERROR(3): missing '{' ----\n")
            sys.exit(1)
           
        blocks-=1    
        if switches and switches[-1]==blocks:   
            switches.pop()
            binc=0
            bcase=0
        print("{0}{1}\n{2}}}\n".format("\t"*(blocks+binc+bcase), s[:cbrace].strip(),"\t"*(blocks+binc+bcase)) )      
        scan( s[cbrace+1:])    
        return;           
               
    print( "{0}{1}".format("\t"*(blocks+binc+bcase), s.strip()) )  
    return;               




def main():
    if len(sys.argv)!=2:
        print("Usage: $> cformat.py  C-file [ >output.c ]")
    else:  
        try:      
            f=open(sys.argv[1],"r")
            s= f.read()
            f.close()
        except IOError as err:    
            print("File access error:{0}".format(err) )
            return

        s= remove_comments( s)  #.replace("\n"," ")
        scan_start(s)
        if( blocks!=0):     
            print("\n---- ERROR(4): missing '}' ----\n")   
            sys.exit(1)            
        
    
main()

        
