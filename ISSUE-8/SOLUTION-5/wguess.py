#! /usr/bin/env python3
# -*- coding: utf-8 -*-

'''
 2013-05-12 by kantal59
 License: LGPL
 OLIMEX WPC#8:  Make All-winner Hangman game, make the computer unbeatable.
    Each time the player guess letter, if this letter is in your word you have to scan the dictionary 
    for similar word (if possible and do not break the game rules) which have no such letter and replace it, 
    so player is always wrong.
 
 Python3 required for correct utf-8 handling!
 Usage: $> wguess.py  directory
 The 'directory' will be walked and the words will be read from the files. 
 The files must contain utf-8 encoded words, one for each line.
 Some parameters can be set here in the source.     
'''

#--- PARAMETERS
# the length of the word to be guessed
# WLENGTH= 2; ATTEMPTS= 22    # good parameters for testing with the text at http://dreamsteep.com/projects/the-english-open-word-list.html
WLENGTH= 2; ATTEMPTS= 10
DEBUG= True
#------------------

from os import sys,walk
from os.path import join
from re import match


def cheating_algorithm( wguessed, index, words):
    ''' The main algorithm.
    
    Input: 
        wguessed: the guessed word, it contains '_' at positions with unrevealed chars.
        index:  the last time challenged position.
        words: the dictionary of words as Python list object, it contains words with the same length ('WLENGTH').
    Return:         
        wguessed: returns with char '_' at position 'index' if there is no match in the dictionary or the cheating is successful,
                  otherwise returns with the original char guessed by the player.
    Cheating:  
        Preserving the already guessed character matching, it finds the words that contains the new char at position 'index'
        and removes them from the dictionary. 
    '''

    count=0     # number of words not containing the char 'ch' at position 'index'
    ch= wguessed[index]
    for w in words:
        if w[index] != ch:
            count+=1      
     
    if count == 0 :             # all the words has 'ch' at position 'index'                 
        return( wguessed[:])    # the guessed char must be accepted !
    else:
        words[:]= [ w for w in words if w[index] != ch ]        # preserving words not containing 'ch' at that position
        return( wguessed[:index] + '_' + wguessed[index+1:] )   # the char at 'index' is unrevealed



def load_words( wlength, dirpath):
    ''' It reads the words from the files in.
    
    Input: 
        wlength: the length of the words to be read.  
        dirpath: the directory with files containing the words; the subdirectories will be walked, too.  
    Return:
        words: the dictionary    
    '''       
       
    words=[]
    chars=set() # statistics only
    maxwfile=0  # statistics only: the max length of the words read from the files
    count=0     # statistics only: total number of words in files
    for root, dirs, files in walk( dirpath): 
    
        for ff in files: 
            fn= join(root,ff)  
            if DEBUG:
                print(fn)
            fd= open(fn,'r')
            for line in fd:    
                ws= line.split()
                for w in ws:
                    count+=1       # statistics only             
                    w= w.strip()     
                    if not w:       # empty line
                        continue                   
                    l= len(w)
                    maxwfile= max( maxwfile,l) # statistics only
                    if l != wlength:    # longer or shorter words are omitted
                        continue
                    w= w.upper()                        
                    words.append( w) 
                    for c in w:     # statistics only
                        chars.add(c) 
        fd.close()  
        
    if DEBUG:
        print("\nCharacters read from the files: ", end="")
        for i in chars:
            print("{0}".format(i), end="")                                         
        print("\nTotal number of words read: {0}; max length: {1}\nNumber of words accepted with length {2}: {3}\n\n".format( count,maxwfile,wlength,len(words)) )                            
        
    return( words)                                                                               
        


def game( wguessed, words, attempt):
    ''' The main loop.
    
    Input:
        wguessed: the initial word frame, filled with chars '_' .
        words:  the dictionary
        attempt: the allowed number of unsuccessful attempts.
    '''
    
    print("You can try a character in the following format: digit(s) <space> character.\n"
          "E.g.: 2 b  where 2 is the position of the 'b' in the word.\n"
          "Exit: Ctrl-C\n")
    
    wlth= len(wguessed)    
    while attempt:     
        try:   
            if DEBUG:
                print( words)
            w= input("attempts:{0}  {1}".format(attempt, " "+wguessed+": ")).upper()
        except KeyboardInterrupt:
            print()
            sys.exit(0)
         
        w= w.split()    
        try:
            pos=int(w[0])
        except ValueError:
            print(" -Invalid parameter")
            continue  
                              
        pos-=1 
        if pos <0 or pos >= wlth or len(w)!=2 or len(w[1]) != 1 or wguessed[pos]!='_' :
            print(" -Invalid parameter")
            continue
         
        ch=w[1]         
        w= wguessed[:pos] + ch + wguessed[pos+1:]  
        v= cheating_algorithm( w, pos, words) 

        if '_' not in v:    # all the chars guessed
            break 
        if v!=w :
            attempt-=1
        wguessed= v                                              
    
    #------ GAME OVER
    if attempt:   
        print("The word is '{0}'. You win!".format(v) )
        
    else:
        print("Sorry, I won.")  
        wguessed= wguessed.replace('_','.')     # count the solutions
        sol=[]
        for w in words:
            if  match( wguessed, w):
                sol.append(w)
                if not DEBUG:
                    break   # if not in debug mode, only one solution is printed
                    
        if DEBUG:                
            print("Number of solutions: {0}".format( len(sol)))
            num=0
            for x in sol:
                num+=1
                if num > 10:
                    break
                print(x)                                                      
            if len(sol) > 10:
                print("  and more\n")
                
        else:
            print("The word is '{0}'".format( sol[0]))
 
 
        
def main():
    ''' The start point 
    
    Input:
        sys.argv[1]: the directory with files containing the words.
    ''' 
    
    if len(sys.argv)!=2:
        print("\nUsage: $> wguess.py  directory_with_utf8_word_file(s)\n")
        return
        
    if DEBUG:
        print("DEBUG ON")
    wlength= WLENGTH    
    words= load_words( wlength, sys.argv[1] )
    if words:
        game( '_'*wlength, words, ATTEMPTS )
    
        
main()        

        
