#!/usr/bin/env python3
#-*- coding:utf-8 -*-

'''
 2013-09-01 by kantal59
 License: LGPL
 OLIMEX WPC#22: Plagiarism detector
            Make code which compare two texts and output the % of similarities between the two texts i.e. if they have same words even 
            if the words are in different order. More advanced version may take care for synonyms.       

    The input parameters ( PARAMS ) can be tuned.                            
'''

import re, sys


def compare( srctext, susptext, nline, min_wlength, threshold):
    ''' srctext: lines of the original text;   
        susptext: lines of the suspicious text 
        nline: number of lines in block to compare
        threshold: percent of the matching words in a block to consider plagiarism
        min_wlength: the minimal length of words to be compared
        
        Return: ( m, srcl1, srcl2, suspl1, suspl2 )
        m: counted words in the block
        srcl1, srcl2: line range in the source block
        suspl1, suspl2: line range in the suspicious block
    '''
        
    nsrc= (len(srctext)+ nline-1)//nline 
    nsusp= (len(susptext)+ nline-1)//nline
    
    for nu in range(nsusp):
        lines = ' '.join( susptext[ nu*nline: (nu+1)*nline ])
        suspblock= [ w for w in re.split('\W+',lines) if len(w) >= min_wlength ]
        
        for nr in range(nsrc):
            lines = ' '.join( srctext[ nr*nline: (nr+1)*nline ] ) 
            srcblock= [ w for w in re.split( '\W+', lines) if len(w) >= min_wlength ]
            lthbsrc= len(srcblock)  # The original length must be saved!
            if lthbsrc==0: continue
            match=0
            for wu in suspblock:
                for wr in srcblock:
                    if wu in wr or wr in wu: 
                        match+=1
                        srcblock.remove(wr)
            if  match*100//lthbsrc >= threshold: yield( match, nr*nline, min( (nr+1)*nline,len(srctext) ), nu*nline, min( (nu+1)*nline,len(susptext) ) )                                                        



def read_text():
    if len(sys.argv)==1:
        print("\nUsage: $> plagiarism.py    source.txt    suspicious.txt \n")
        sys.exit(1)
        
    try: 
        handle1= open( sys.argv[1], "r")
        handle2= open( sys.argv[2], "r")                                
        text1= [ s.lower() for s in handle1.read().splitlines() ]
        text2= [ s.lower() for s in handle2.read().splitlines() ]
        handle1.close()
        handle2.close()
    except IOError:
        print(" File access error.\n")
        sys.exit(2)
        
    return( text1, text2)




def print_result( fn1, text1, fn2, text2, matches, nlines, min_wlength, threshold):

    for m in matches:
        print('\n','-'*20,'\n counted words:{0}'.format( m[0] ) )
        print('\n >{0}:\n lines {1}-{2}\n'.format( fn1, m[1]+1,m[2]) )
        for line in range(m[1],m[2]): print( text1[line])
        print('\n >{0}:\n lines {1}-{2}\n'.format( fn2, m[3]+1,m[4]) )
        for line in range(m[3],m[4]): print( text2[line])
        
    print( "\n\nPARAMETERS:\n block length: {0} line(s)\n min length of words to be counted: {1}\n threshold: {2}% (percent of counted words in the source block)\n".format( nlines, min_wlength, threshold ) )
    ms=set()
    for m in matches: ms.add( (m[3],m[4]))
    sblocks= (len(susp)+nlines -1)//nlines
    print( "\nSUMMARY:\n Suspicious text blocks in '{0}' are {1} from {2} [{3}%]\n".format( fn2, len(ms), sblocks, len(ms)*100//sblocks ) )



#------------- T E S T I N G --------------------

src, susp= read_text()

PARAMS=( 2, 4, 10) # lines of block, min length of words to be counted, percent of the matching words in a block to consider plagiarism
#PARAMS=( 5, 3, 40) 

lmatch= [ m for m in compare(src, susp, *PARAMS) ]  # processing
#print( lmatch)

print_result( sys.argv[1], src, sys.argv[2], susp, lmatch, *PARAMS)     








