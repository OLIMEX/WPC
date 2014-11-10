
def printline(words, chline):
    chline -= (sum(len(w) for w in words) + len(words) - 1)
    s = words[0]
    f = 0
    for w in words[1:]:
        if f == 0:
            s += " " + " "*chline + w
            f = 1
        else:
            s += " " + w
    return s

def formatline(words, chline):
    if len(words) < 1:
        return "\n"
    a = 0
    b = 1
    s = words[0]
    ret = ""
    while b < len(words):
        s += " " + words[b]
        if len(s) == chline:
            ret += s + "\n"
            s = words[b+1]
            a = b+1
        elif len(s) > chline:
            ret += printline(words[a:b], chline) + "\n"
            s = words[b]
            a = b
        b += 1
    return ret + s

def formattext(t, chline):
    s = ""
    for p in t:
        s += formatline(p, chline) + "\n"
    return s

f = open("alice-11-h.txt", "r")
listoflines = [word.split() for word in f]
f.close()
#max char per line should more than longest word
#print formattext(listoflines, 25)
print formattext(listoflines, 37)
