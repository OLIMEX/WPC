#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Weekend Programming Challenge Issue #4 (Olimex)
# Solution proposed by Francescesco Frassinelli (Frafra)

from string import punctuation
with open("book.txt", "r") as book:
    clean = [' ' if char in punctuation else char for char in book.read()]
for word in sorted("".join(clean).lower().split(), key=len, reverse=True):
    if len(word) == len(set(word)):
        break
print(word)