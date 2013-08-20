import string
from collections import defaultdict

def myezlog2(n):
    i = 0
    k = 1
    while k<n:
        i += 1
        k *= 2
    
    return i

def isanagram(str1, str2):
    str1_list = list(str1)
    str1_list.sort()
    str2_list = list(str2)
    str2_list.sort()
    return (str1_list == str2_list)

def letteronly(w):
    s = ""
    for i in range(0, len(w)):
        if w[i] in string.lowercase:
            s += w[i]
        else:
            s +=' '
    
    return s

def intersectlist(a, b):
     return list(set(a) & set(b))

def minuslist(a, b):
     return list(set(a) - set(b))

# --if we use this instead, it slower
#def intersectlist_slow(a, b):
#    r = [v for v in a if v in b]
#    return r

alice = sorted(set((letteronly(open('alica.txt', 'r').read().lower())).split()))
# --now alice is list that contains distinct words that are converted to all lower letters

# --alice_ilen is index (like index in table of database) for len of words
alice_len = [len(n) for n in alice]
alice_ilen = defaultdict(list) 
for k, v in enumerate(alice_len):
    alice_ilen[v].append(k)

alice_ichar = defaultdict(list)
alice_icharmore = defaultdict(list)
for k, v in enumerate(alice):
    w_chlist = list(v)
    for c in w_chlist:
        alice_ichar[c].append(k)

alice_ichar_countwords = dict((k, len(alice_ichar[k])) for k in alice_ichar)
alice_anagram = defaultdict(list)
alice_size = len(alice)
alice_logasize = myezlog2(alice_size)
usedlist = []
for i in range(0, alice_size):
    # -- find candidate list j to compare list i
    alice_jlist = [j for j in alice_ilen[alice_len[i]] if j>i]
    
    # --if len of alice_jlist still too large (> log2(len(alice))), find way to reduce
    # --concept from "selectivity" in database term
    # -- sort list_of_i_word, order by len of lists of that char (asc)
    list_of_i_word = sorted(set(list(alice[i])), key=lambda x: alice_ichar_countwords[x])
     
    for c in list_of_i_word:
                
        #print "%d: %d-%d %s" % (i, len(alice_jlist), len(alice_ichar[c]), c)
        if alice_logasize >= len(alice_jlist):
            break
        
        alice_jlist = intersectlist(alice_jlist, alice_ichar[c])
    
    alice_jlist = minuslist(alice_jlist, usedlist)
        
    #alice_jlist.sort() #may not need this line of code
    firstmatch = True
    for j in alice_jlist:
        if (isanagram(alice[i], alice[j])):
            #print "%s %s" % (alice[i], alice[j])
            if firstmatch:
                firstmatch = False
                alice_anagram[i].append(alice[i])
                usedlist.append(i)
                
            alice_anagram[i].append(alice[j])
            usedlist.append(j)
            
for l in alice_anagram:
    print alice_anagram[l]          
    
