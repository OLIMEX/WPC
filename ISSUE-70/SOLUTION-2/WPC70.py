# -*- coding: utf-8 -*-
"""
Make code which enters expression like '3525 + 133 =' and solve it. Easy right? Here is the catch is that numbers and operations are replaced by their words equivalents.
Please support numbers up to 1 000 000 and these operators + – * /
Example:
    input: 'three thousands five hundreds and twenty five plus one hundred and thirty three is equal to'
    output: 3658
"""
#====================
# This code respects the description, so no '-' between 20-99.
#====================


nums = { "million" : 1000000,
        "millions" : 1000000,
        "thousand" : 1000,
        "thousands" : 1000,
        "hundred" : 100,
        "hundreds" : 100,
        "ten" : 10,
        "eleven" : 11,
        "twelve" : 12,
        "thirteen" : 13,
        "fourteen" : 14,
        "fifteen" : 15,
        "sixteen" : 16,
        "seventeen" : 17,
        "eighteen" : 18,
        "nineteen" : 19,
        "twenty" : 20,
        "thirty" : 30,
        "forty" : 40,
        "fifty" : 50,
        "sixty" : 60,
        "seventy" : 70,
        "eighty" : 80,
        "ninety" : 90,
        "one" : 1,
        "two" : 2,
        "three" : 3,
        "four" : 4,
        "five" : 5,
        "six" : 6,
        "seven" : 7,
        "eight" : 8,
        "nine" : 9,
        "zero" : 0,}



def substract(a, b):
    return (a - b)

def multiply(a, b):
    return (a * b)

def divide(a, b):
    return (a * 1.0 / b)

def add(a, b):
    return (a + b)

ops = { "plus" : add,
        "minus": substract,
        "times": multiply,
        "over": divide,}

def preprocess(text):
    buff = text
    buff = buff.replace("thousands", "thousand")
    buff = buff.replace("hundreds", "hundred")
    buff = buff.replace(" is equal to", "")
    buff = buff.replace(" divided by ", " over ")
    for elem in nums.keys():
        if buff.find(elem) >= 0:
            buff = buff.replace(elem, str(nums[elem]))
    return buff

def conversion(data):
    text = preprocess(data)
    split = text.split()
    current = 0
    op = None
    saved = []
    numbers = [0]*2
    for i in range(0, len(split)):
        if split[i].isdigit():
            temp = int(split[i])
            if temp == 1000000:
                numbers[current] = saved[-1] * 1000000
                saved = []
            elif temp == 1000:
                numbers[current] = saved[-1] * 1000
                saved = []
            elif temp == 100:
                saved[-1] = saved[-1] * 100
            else:
                if len(saved) > 0:
                    saved[-1] = saved[-1] + temp
                else:
                    saved.append(int(temp))
        elif split[i] in ops.keys():
            numbers[current] = numbers[current] + sum(saved)
            current = current + 1
            saved = []
            op = ops[split[i]]
    numbers[current] = numbers[current] + sum(saved)
    #print(numbers[0], numbers[1])
    result = op(numbers[0], numbers[1])
    return result

x = "three thousands five hundreds and twenty five plus one hundred and thirty three is equal to"
f = " four hundred and fifty eight thousand one hundred and forty two plus thirty two thousand four hundred and fifty eight is equal to"
y = " four hundred and fifty eight thousand one hundred and forty two plus one is equal to"
z = " one plus one is equal to"
s = " zero times one million"
a = " one million times one million"
q = "thirty two thousand four hundred and fifty eight divided by five thousand two hundred and sixteen"

test = conversion(x)
print(test)

test = conversion(f)
print(test)

test = conversion(y)
print(test)

test = conversion(z)
print(test)

test = conversion(s)
print(test)

test = conversion(q)
print(test)

test = conversion(a)
print(test)
