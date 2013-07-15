#!/usr/bin/env python
#-*- coding:utf-8 -*-
'''
 2013-07-13 by kantal59
 License: LGPL
 OLIMEX WPC#17:
    Problem: Ancient Greeks and Spartans used Skytales to send encrypted messages, they wound on bar stripe then write on it, 
    when the stripe is unwound the letters become shifted and you cant read the message again until you wound it on rod 
    with same diameter.
    Write code which crypt and de-crypt message on Skytale, as input you can take message and diameter of the rod.

 Instead of diameter of the rod, the input is the number of characters fit on the rod in a circle, so the diameter is fixed.
 Example: 
    chars fit in one circle= 4
    message= "123456789"
    It needs 2 +1/4 circles to write the message.
    It can be:              
                A)          B)          C)
                129         123         123
                34          456         45   
                56          789         67
                78          __          89
                
    (The minimal strip length: 9, 11, 9)       
    I think B) as the most natural practice.
'''
import sys;
if len(sys.argv)!=3:    print("Usage: $> skytale.py     num_of_chars_fit_in_a_circle   \"message\""); sys.exit(1)
s= sys.argv[2];     chscol= int(sys.argv[1]);    lth=len(s);    ncols= len(s)//chscol 
if lth%chscol:      ncols+=1;   s=s+" "*(chscol-lth%chscol);    lth= len(s)
encrypted= [" "]*lth;   decrypted= [" "]*lth
for i, ch in enumerate( s): encrypted[ (i%ncols)*chscol+ i//ncols ]= decrypted[ (i%chscol)*ncols+ i//chscol]= ch
print("chars/circle=\t{0}\ncircles=\t{1}\ninput=\t\t{2}\nencrypted=\t{3}\ndecrypted=\t{4}".format(chscol,ncols,s, "".join(encrypted), "".join(decrypted) ))
    
  
    
    
    
