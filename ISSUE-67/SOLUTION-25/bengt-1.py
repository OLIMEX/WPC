#!/usr/bin/env python
# Iterative generation of an object oriented list using functions on iterables.
pages = [0]
while sum(pages) != 9808:
    while sum(pages) < 9808:
        pages.append(max(pages) + 1)
    if sum(pages) > 9808:
        pages.remove(min(pages))
print("%i = sum(%s)" % (sum(pages), pages))
