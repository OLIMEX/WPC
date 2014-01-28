from random import choice
from getch import getch
# https://github.com/joeyespo/py-getch/blob/master/getch/getch.py
import sys
import time

textslist = ["Cat jumps quickly", "Put it into" \
   ,"and from between them", "until there", "Time goes by"]

while True:
    typetext = choice(textslist)
    typetextpos = 0
    typeincorrect = 0
    print typetext
    starttime = time.time()
    while True:
        char = getch()
        if char in [chr(3), chr(0x1B)]: # Ctrl-C or Escape key to exit
            exit()
        elif char == typetext[typetextpos]:
            elapsed = (time.time() - starttime)
            typetextpos += 1
            sys.stdout.write(char)
            if typetextpos >= len(typetext):
                print
                print "--------------------" 
                print "incorrect = ", typeincorrect
                print "elapsed time =", elapsed
                print "--------------------" 
                break
        else:
            typeincorrect += 1