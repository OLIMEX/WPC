# author : st0le (http://lostincompilation.blogspot.com)
# github : https://github.com/st0le/

import sys,re

words = set(re.findall("\w+",sys.stdin.read().lower()))

def get_regex(w):
    return "(" + ")|(".join({"^%s[a-z]%s$" % (w[:i],w[i+1:]) for i in xrange(len(w))}) + ")"

for word in sys.argv[1:]:
    if not word: break
    regex = get_regex(word)
    print word,':',','.join(set(filter(lambda w: re.match(regex, w), words)))
