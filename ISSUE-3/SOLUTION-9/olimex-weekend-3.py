#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Weekend Programming Challenge Issue #3 (Olimex)
# Solution proposed by Francescesco Frassinelli (Frafra)
#
# Identical words will be treated as one

words = set("""
A13-OLinuXino
iMX233-OLinuXino
MOD-PULSE
MOD-IO
""".upper().split())

def part(word, lenght):
    result = set()
    for index in range(len(word)-lenght+1):
        result.add(word[index:index+lenght])
    return result

lenght = 1
remaining = words.copy()
while remaining:
    sets = {word:part(word, lenght) for word in words}
    for w1 in remaining.copy():
        result = sets[w1]
        for w2, other in sets.iteritems():
            if w1 != w2:
                result = result-other
                if not result:
                    break
        if result:
            print("%s -> %s" % (w1, result.pop()))
            remaining.remove(w1)
    lenght += 1
    for word in remaining.copy():
        if len(word) < lenght:
            print(word + " is contained in another word!")
            remaining.remove(word)