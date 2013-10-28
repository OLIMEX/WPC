#!/usr/bin/env python3
#-*- coding:utf-8 -*-

''' 
 2013-10-26 by kantal59
 License: LGPL
 OLIMEX WPC#30: Converter from decimal to roman numbers.
 
    It converts from roman number to decimal, too.
'''

roman_numerals= [   [ 'I', 'II', 'III', 'IV',  'V', 'VI', 'VII', 'VIII', 'IX' ], \
                    [ 'X', 'XX', 'XXX', 'XL',  'L', 'LX', 'LXX', 'LXXX', 'XC' ], \
                    [ 'C', 'CC', 'CCC', 'CD',  'D', 'DC', 'DCC', 'DCCC', 'CM' ], \
                    [ 'M', 'MM', 'MMM', 'M|))', '|))', '|))M','|))MM', '|))MMM', 'M((|))'], \
                    [ '((|))'] ]

                
def dec2rom( decv ):
    ''' Conversion from decimal to roman numeral in the range (0-1999).'''   
    if decv == 0: return('N')
    if decv > 19999: return(':-( overflow )-:')
    magnitude=0
    rslt=''
    while decv > 0:
        decv,r = decv//10, decv%10
        if not r: magnitude+=1; continue
        rslt= roman_numerals[magnitude][r-1] + rslt
        magnitude+=1    
    return( rslt)



def rom2dec( romv):
    ''' Conversion from roman numeral to decimal. '''
    if romv=='N': return(0)
    rslt=0
    magnitude= len(roman_numerals)
    
    while romv:
        tokens= [ (tkn,mag,index) for mag,group in  enumerate(roman_numerals)  for index,tkn in enumerate( group) if romv.startswith(tkn)  ]
        if not tokens: 
            return(-1)  #invalid roman numerals
            
        tokens.sort( key= lambda tok: len( tok[0]) )
        tok= tokens[-1] # get the longest token
        #print( tok)
        if tok[1] >= magnitude: # check the magnitude; e.g.: IIII, VIX, DCDC, XD are invalid
            return(-1)
        magnitude= tok[1]          
          
        rslt+= (tok[2]+1)*pow(10,tok[1])
        romv= romv[ len(tok[0]): ]

    return(rslt)        
        
        
        
        

import sys

if __name__ =='__main__':

   
    
    if len(sys.argv)>1:
        for v in sys.argv[1:] : 
            dec=0; rom=''
            if v.isdecimal(): 
                dec= int(v)
                rom= dec2rom( dec)
                print(dec,' ---> ',rom)
            else:
                rom= v.upper()
                dec= rom2dec( rom) 
                print(rom,' ---> ',dec)            
            
        
    else:   
        print('\n Usage: $ roman.py [ roman_numeral | decimal ] ...\n Examples:\n\t roman.py 23 56 xxii 79 CM\n\t roman.py 19548 "((|))" xli\n Test:')
        data=[ 0,1, 4, 9, 14, 549, 999, 1959, 2013, 3999, 5000, 9999, 10000, 15049, 19999, 20000] 
        for v in data: 
            rom= dec2rom(v)
            print( "{0:>6} {1:^21} {2:>6}".format( v, rom, rom2dec(rom) ) )
        
        
     
            
        



