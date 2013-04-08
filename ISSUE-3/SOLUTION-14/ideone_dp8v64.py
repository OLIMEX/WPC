import sys
def unique(ws):
    # map all substrings to words they are in
    words = {}
    for w in ws:
        lw = w.lower()
        for r in range(1,len(lw)+1):
            for l in range(r):
                substring = lw[l:r]
                if substring in words and words[substring] != w: 
                    words[substring] = None
                else: 
                    words[substring] = w
    # find shortest substring for each word                
    shortest = {}
    for s, w in words.iteritems():
        if w and (not w in shortest or len(s)<len(shortest[w])):
            shortest[w] = s
    return [(w, shortest.get(w, None)) for w in ws]        
    
for w,s in unique([w.rstrip() for w in sys.stdin]):
    print w,s
