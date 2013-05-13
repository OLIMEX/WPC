import sys
import string
import fileinput
import random
import re
from string import maketrans

# file wordlower.txt contains one word in one line
# to filter only lowerletter 
# grep [a-z] < words.txt > wordlower.txt

file = [line for line in fileinput.input("wordlower.txt")]
rand = random.Random()
w1 = file[int(rand.random() * len(file))]
w1 = w1.rstrip('\n')

w2 = '.'*len(w1) # len of w1
count = 10
t1 = 'abcdefghijklmnopqrstuvwxyz'
t2 = '.'*len(t1)
usedletter = []

# maskword() removes char c that must be hidden from t1 
# and returns w only char that must be disclosed
def maskword(w, c):
    global t1
    global t2
    t2 = t2[:-1]
    t1 = t1.replace(c, '')
    trantab = maketrans(t1, t2)
    return str.translate(w, trantab)

while True:
    #print "'%s'" % w1 # debug or real cheat :D
    print "Guess word '%s'. Count remain=%d" % (w2, count)
    print "Used letters %s" % usedletter
    if w1 == w2:
        print "You win"
        break

    l = raw_input('Enter guess letter ')
    l = string.lower(l[:1]) #only 1-st lowercase letter
    if any(l in s for s in usedletter):
        print "%s already choosen" % l
        continue
    else:
        usedletter.append(l)

    if string.find(w1, l) == -1: #letter not found, no need to change w1
        count -= 1
        print "No %s letter in that word."  % l
        if count <= 0:
            print "You lose. Answer is %s" % w1
            break
        
        continue #letter not found -> continue loop

    # w1 contains that guese letter
    # cheating here
    # by changing (if possible) w1 so that it does not contain letter l
    # and does not contain letters that in usedletter
    # and masking still like w2 (the same string len too

    i=30000
    rex = re.compile("^%s$" % w2)
    while i>0:
        w3 = file[int(rand.random() * len(file))]
        w3 = w3.rstrip('\n')
        if len(w3) != len(w1):
            continue

        #print "%d w3=%s" % (i, w3) # debug printing
        i -= 1
        usedletter2 = string.join(usedletter)
        if rex.match(w3) and (re.findall(r'[%s]' % usedletter2,w3) == []):
            w1 = w3 # todo w3 should not contain letter in usedletter 
            break

    #print "'%s' (cheat)" % w1 # debug or real cheat :D
    if string.find(w1, l) == -1: #check again if letter not found
        count -= 1
        print "No %s letter in that word."  % l
        if count <= 0:
            print "You lose. Answer is %s" % w1
            break

    else:
        print "Contains %s" % l
        w2 = maskword(w1, l)

