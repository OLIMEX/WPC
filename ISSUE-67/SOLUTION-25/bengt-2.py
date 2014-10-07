#!/usr/bin/env python
# Iterative generation of a list using conditional expressions.
pages = [0]
while sum(pages) != 9808:
    pages = pages + [max(pages) + 1] if sum(pages) < 9808 else pages
    pages = pages[1:] if sum(pages) > 9808 else pages
print("%i = sum(%s)" % (sum(pages), pages))
