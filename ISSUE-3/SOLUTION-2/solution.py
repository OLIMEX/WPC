#!/usr/bin/python
 
import sys
 
split_lines = [x.strip() for x in sys.stdin.readlines()]
for i in range(len(split_lines)):
    word = split_lines[i]
    word_lower = word.lower()
    others = " ".join(split_lines[:i] + split_lines[i+1:]).lower()
    not_found = True
    l = 1
    while not_found:
        for j in range(len(word_lower) - (l-1)):
            candidate = word_lower[j:j+l]
            if candidate not in others:
                not_found = False
                print "%s -> %s" % (word, candidate)
                break
        l += 1