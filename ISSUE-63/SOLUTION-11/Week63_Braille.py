#Please use Python 3 to run this code.
#This work by 2Cubed is licensed under the Creative Commons Attribution 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by/4.0/.

myInput = input()
print('')
braille = {' ':'      ','a':'*.....','b':'*.*...','c':'**....','d':'**.*..','e':'*..*..','f':'***...','g':'****..','h':'*.**..','i':'.**...','j':'.***..','k':'*...*.','l':'*.*.*.','m':'**..*.','n':'**.**.','o':'*..**.','p':'***.*.','q':'*****.','r':'*.***.','s':'.**.*.','t':'.****.','u':'*...**','v':'*.*.**','w':'.***.*','x':'**..**','y':'**.***','z':'*..***','.':'..**.*',',':'..*...','!':'..***.','?':'..*.**',"'":'....*.','-':'....**','1':'*.....','2':'*.*...','3':'**....','4':'**.*..','5':'*..*..','6':'***...','7':'****..','8':'*.**..','9':'.**...','0':'.***..'}
stuff = []

for letter in myInput:
    if letter.isupper():
        stuff.append('.....*')
    elif letter.isnumeric():
        stuff.append('.*.***')
    stuff.append(braille[letter.lower()])

lineOne=""
lineTwo=""
lineThree=""

for one in stuff:
    lineOne+=one[0]
    lineOne+=one[1]
    lineOne+="  "
    
for two in stuff:
    lineTwo+=two[2]
    lineTwo+=two[3]
    lineTwo+="  "
    
for three in stuff:
    lineThree+=three[4]
    lineThree+=three[5]
    lineThree+="  "
    
print(lineOne)
print(lineTwo)
print(lineThree)