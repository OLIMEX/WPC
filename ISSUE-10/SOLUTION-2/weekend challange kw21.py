import sys

tmp=0
i=2

a=input("first number: ")
b=input("second number: ")

sol=int(a)/int(b)

while True:
    tmp += 1/i
    if tmp <= sol:
        print(i)
    elif tmp == sol:
        break
    else:
        tmp -= 1/i
    i+=1
    

