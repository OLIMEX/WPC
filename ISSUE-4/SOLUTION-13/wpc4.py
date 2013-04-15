import string


checkedWords = set()
longestWordAndSize = ('',0)

def ifIsogram(word):
    wordSet = set()
    for let in word:
        if let in wordSet:
            return False
        wordSet.add(let)
    return True


def testWord(word):
    global longestWordAndSize
    if word not in checkedWords:
        l = len(word)
        checkedWords.add(word)
        l = len(word)
        if l > longestWordAndSize[1]:
            if ifIsogram(word):
                longestWordAndSize = (word, l)
                return longestWordAndSize
    return None

def main():
    result = ''
    with open('alice.txt', 'r') as f:
        for line in f.readlines():
            table = string.maketrans(string.punctuation,'
'*len(string.punctuation))
            for word in line.translate(table).split():
                if testWord(word.lower()):
                    result = word
    print result

if __name__ == '__main__':
    main()

The word is CURTSEYING
