# author : st0le (http://lostincompilation.blogspot.com)
# github : https://github.com/st0le/
import sys,re


class Trie:
    
    def __init__(self):
        
        self.children = {}
        self.word = None
    
    def insert(self,word):
        node = self
        for c in word:
            if c not in node.children:
                node.children[c] = Trie()
            node = node.children[c]
        node.word = word

words = set(re.findall("\w+",sys.stdin.read().lower()))
trie = Trie()
for w in words:
    trie.insert(w)

def search( word, root, maxCost ):
    l = len(word)
    s = set()
    def recurse(index,node,maxCost,s):
        
        if index < l:
            if word[index] in node.children:
                recurse(index + 1, node.children[word[index]], maxCost , s  )
            if maxCost > 0:
                for c in node.children:
                    recurse(index + 1, node.children[c], maxCost - 1, s )
        elif node.word and maxCost == 0:
            s.add(node.word)
    recurse(0 , root, maxCost,s)
    return s
for word in sys.argv[1:]:
    if not word: break
    print word,':',','.join(search(word,trie,1))