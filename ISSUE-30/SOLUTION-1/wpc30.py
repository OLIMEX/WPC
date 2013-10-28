R = ((1000, 'M'), (900, 'CM'), (500, 'D'), (400, 'CD'), (100, 'C'), (90, 'XC'),
    (50, 'L'), (40, 'XL'), (10, 'X'), (9, 'IX'), (5, 'V'), (4, 'IV'), (1, 'I'))

def process(number, value, letter, so_far):
    while number >= value:
        number -= value
        so_far += letter
    return (number, so_far)

def roman(number):
    result = ''
    for (value, letter) in R:
        (number, result) = process(number, value, letter, result)
    return result

print roman(1066), roman(1999), roman(2013)

while True:
    inp = raw_input('Enter decimal (X to quit): ')
    if inp == 'X':
        break
    print roman(int(inp))
