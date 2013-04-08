#!/usr/bin/env python
import sys

# global variable with a cache of shared substring that have already 
# been found (used to speed up the check)
failed_subs=set()

# generator that enumerates every substring of 's', short first
def subs(s):
    # i = len of substring
    for i in range(1,len(s)+1):
        for j in range(len(s)-i+1):
            yield s[j:j+i]

# check if 's' is a substring of any word in the set 'words'
def is_a_subs(words, s):    
    for i in words:
        if s in i:
          return True      
    return False
            
def usage():
    print sys.argv[0]+""": wrong number of parameter

usage:"""+sys.argv[0]+ """  <file>
  where <file> is a text file containg the words, one for every line
"""

def main():

    if len(sys.argv)!=2:
        usage()
        return False
    
    # words are converted in lower case, because searches should be case insensitive    
    words=set(( x[:-1].lower() for x in file(sys.argv[1],'r').readlines() ))

    # for every word
    for w in words:
        found=False
        # for every possible substring of the current word
        for subw in subs(w):
            if subw in failed_subs:
                # already found in some other words
                continue
            # check that it's not a substring in other words
            if is_a_subs(words-set((w,)), subw):
                failed_subs.add(subw)
            else:
                print w, "->",subw
                found=True
                break
        if not found:            
            print w, "-> Nothing!"
      
if __name__=='__main__':
    main()
