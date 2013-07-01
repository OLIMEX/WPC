import fileinput
import sys

cfilename = "picspigot2.c" #change file as you want

#initialize values
prevchar = ' '
incomment1 = False
cstack = []
for line in fileinput.input(cfilename):
    lineoffset = 0
    for char in line:
        if incomment1:
            if prevchar == '*' and char == '/':
                incomment1 = False
            
        else:
            if char == '}':
                if len(cstack) == 0: #to prevent to pop empty stack
                    sys.stderr.write("Error: { < }\n")
                    sys.stderr.flush()
                    
                else:
                    coffset = cstack.pop()
                    if coffset > lineoffset:
                        shiftedoffset = coffset - lineoffset
                        lineoffset += shiftedoffset
                        sys.stdout.write(' '*(shiftedoffset))
                        
                    elif coffset < lineoffset:
                        sys.stdout.write("\n" + ' '*coffset)
                        
            elif char == '{':
                cstack.append(lineoffset)

            elif prevchar == '/' and char == '*':
                incomment1 = True
                
        sys.stdout.write(char)
        sys.stdout.flush()   
        prevchar = char
        lineoffset += 1
     
#if cstack is not empty, print error
if len(cstack) != 0:
    sys.stderr.write("Error: { > }\n")
    sys.stderr.flush()