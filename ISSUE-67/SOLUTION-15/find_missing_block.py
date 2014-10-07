#!/usr/bin/python
# -*- coding: utf-8 -*-
# Week #67: Find missing consecutive pages in book
# by Danny Milosavljevic. This work is in the public domain.
from math import sqrt

pageno_sum = 9808

"""
Pages: ############      ########
                   ^    ^
                   |    +-- last_pageno
                   +------- first_pageno

pageno_sum = (first_pageno + last_pageno)*(last_pageno - first_pageno + 1)/2  [Gauß]
last_pageno = first_pageno + page_count - 1
pageno_sum = (first_pageno + first_pageno + page_count - 1)*page_count/2
2*pageno_sum = (first_pageno + first_pageno + page_count - 1)*page_count
"""
# assumption: book is less than 9808 pages (otherwise a solution is obvious: starting from the first page, an appropriate amount of pages are missing).
for first_pageno in range(1, pageno_sum):
	"""
	(2*first_pageno + page_count - 1)*page_count == 2*pageno_sum
	page_count**2 + (2*first_pageno - 1)*page_count == 2*pageno_sum
	page_count**2 + (2*first_pageno - 1)*page_count - 2*pageno_sum == 0
	page_count = (-(2*first_pageno - 1) + sqrt((2*first_pageno - 1)**2 - 4*1*(-2*pageno_sum)))/2  [Vieta]
	"""
	maximal_page_count = (-(2*first_pageno - 1) + sqrt((2*first_pageno - 1)**2 - 4*1*(-2*pageno_sum)))/2
	minimal_page_count = (-(2*first_pageno - 1) - sqrt((2*first_pageno - 1)**2 - 4*1*(-2*pageno_sum)))/2 # [Vieta]
	assert pageno_sum > 0 and maximal_page_count != minimal_page_count and minimal_page_count < 0
	if maximal_page_count == int(maximal_page_count):
		print({"first_pageno": first_pageno, "page_count": int(maximal_page_count)})
	"""
	SLOW but does the same:
	for page_count in range(pageno_sum):
		if (2*first_pageno + page_count - 1)*page_count == 2*pageno_sum:
			print({"first_pageno": first_pageno, "page_count": page_count})
		# SLOWER: if sum([i for i in range(first_pageno, first_pageno + page_count)]) == pageno_sum:
	"""
