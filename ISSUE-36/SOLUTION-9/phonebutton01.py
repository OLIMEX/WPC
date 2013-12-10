translatedict = {"a":"2 ", "b":"22 ", "c":"222 ", \
    "d":"3 ", "e":"33 ", "f":"333 ", \
    "g":"4 ", "h":"44 ", "i":"444 ", \
    "j":"5 ", "k":"55 ", "l":"555 ", \
    "m":"6 ", "n":"66 ", "o":"666 ", \
    "p":"7 ", "q":"77 ", "r":"777 ", \
    "t":"8 ", "u":"88 ", "v":"888 ", \
    "w":"9 ", "x":"99 ", "y":"999 ", "z":"9999 "}
    
def trans1(str):
    sr = ""
    for c in str.lower():
        if c in translatedict: # O(1) or O(n)
            sr += translatedict[c]
        else:
            sr += c
    return sr

str2 = "hEllo, WoLrd. 0123456789"
print trans1(str2)
