#!/usr/bin/env python3
#-*- coding:utf-8 -*-

'''
 2013-08-23 by kantal59
 License: LGPL
 OLIMEX WPC#21: Words Puzzle
            Aoccdrnig to a rscheearch at Cmabrigde Uinervtisy, it deosn’t mttaer in waht oredr the ltteers in a wrod are, 
            the olny iprmoetnt tihng is taht the frist and lsat ltteer be at the rghit pclae. The rset can be a toatl mses 
            and you can sitll raed it wouthit porbelm. Tihs is bcuseae the huamn mnid deos not raed ervey lteter by istlef, 
            but the wrod as a wlohe.

            You can see original text here: http://www.mrc-cbu.cam.ac.uk/people/matt.davis/Cmabrigde/
            Write code which takes as input normal text and shuffles the letters inside the words to make text like this one above.

 There is a few 'SHAKE' algorithm :-)            
             
'''


import re, random

text= '''According to a researcher at Cambridge University, it doesn't matter in what order the letters in a word are, the only important 
thing is that the first and last letter be at the right place. The rest can be a total mess and you can still read it without problem. 
This is because the human mind does not read every letter by itself but the word as a whole.'''


def shake1( word):  
    ''' Sorting between the first and last chars'''
    l= list( word[1:-1])
    l.sort()
    return( word[0]+ ''.join(l)+ word[-1] )


def shake2( word):  
    ''' Reversing between the first and last chars'''
    return( word[0]+ word[1:-1][::-1]+ word[-1] )
            

def shake3( word):  
    ''' Doing something :-)'''
    return( word[0]+ word[1:-1][0::2]+  word[1:-1][1::2]+  word[-1] )


def shake4( word):  
    ''' Swapping the neighbours between the first and last chars'''
    z= zip( word[1:-1:2], word[2:-1:2])
    p= word[0]
    for (x,y) in z:
        p+=y+x
    if len(word)%2: p+=word[-2]    
    return( p+word[-1])            
 
    
def shake5( word):     
    ''' Randomizing between the first and last chars'''
    l= list( word[1:-1])
    random.shuffle(l)
    return( word[0]+ ''.join(l)+ word[-1] )



def puzzle( text, shfunc= shake5):
    tokens= re.split('(\W+)', text) 
    rslt=''
    for w in tokens:
        if len(w)<=3 or [ c for c in w if not c.isalpha() ]: 
            rslt+= w         
        else:
            rslt+= shfunc(w)
    return( rslt)            



#------------- Testing --------------------

print('\n<< The original text >>\n{0}\n'.format( text) )

sh=[ shake1, shake2, shake3, shake4, shake5]
for func in sh: print( '\n<<{0}>>\n{1}\n'.format( func.__doc__, puzzle(text, func) ) )   
     



