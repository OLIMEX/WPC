import string
from collections import Counter

synlist = {"buy":"purchase"}

def insert_to_list(element, list_element):
    if element in synlist:
        element = synlist[element]
    try:
        index_element = list_element.index(element)
        return index_element
    except ValueError:
        list_element.append(element)
        index_element = list_element.index(element)
        return index_element
        
def letteronly(w):
    s = ""
    for i in range(0, len(w)):
        if w[i] in string.lowercase:
            s += w[i]
        else:
            s +=' '
    return s
        
file1 = (letteronly(open('alica20.txt', 'r').read().lower())).split()
file2 = (letteronly(open('alica30.txt', 'r').read().lower())).split()
listofwords = []
file1aslowno = [insert_to_list(w, listofwords) for w in file1]
file2aslowno = [insert_to_list(w, listofwords) for w in file2]
cnt1 = Counter(file1aslowno)
cnt2 = Counter(file2aslowno)

cnt1_allwordscount = 0
cnt1_wordsfoundin2 = 0
for k in cnt1:
    cnt1_allwordscount += cnt1[k]
    cnt1_wordsfoundin2 += cnt2[k]

cnt2_allwordscount = 0
cnt2_wordsnotfoundin1 = 0
for k in cnt2:
    cnt2_allwordscount += cnt2[k]
    cnt2_wordsnotfoundin1 += (cnt2[k] - cnt1[k])

print "%f percent of words in text1 also found in text2" % (100.00 * cnt1_wordsfoundin2 / cnt1_allwordscount)
print "%f percent of words in text2 not found in text1" % (100.00 * cnt2_wordsnotfoundin1 / cnt2_allwordscount)
