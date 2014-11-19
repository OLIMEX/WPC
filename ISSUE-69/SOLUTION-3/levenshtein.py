#!/usr/bin/env python

#
# levenshtein.py - Calculates the Levenshtein distance between two words
# Copyright 2014 Benjamin Lutz - http://1id.com/=benjamin.lutz
#
# Written for Olimex Weekend Programming Challenge #69
# http://olimex.wordpress.com/2014/11/14/weekend-programming-challenge-week-69-levenshtein-distance/
#
# Run it like this:
#   python levenshtein.py elephant relevant
#


import math
import sys
import StringIO


def main():
	if len(sys.argv) != 3:
		sys.stderr.write('Syntax: %s <from> <to>\n' % sys.argv[0])
		sys.exit(1)

	levenshtein = Levenshtein(sys.argv[1], sys.argv[2])
	print levenshtein
	print '\n'.join(levenshtein.operations)


class Levenshtein(object):
	def __init__(self, fromString, toString):
		self._from = fromString
		self._to = toString
		self._fromLen = len(fromString)
		self._toLen = len(toString)
		self._levenshteinMatrix = Levenshtein._newMatrix(self._toLen + 1, self._fromLen + 1, 0xFFFFFFFF)
		self._pathMatrix = Levenshtein._newMatrix(self._toLen + 1, self._fromLen + 1, 0)
		self._operations = []
		
		self._calculateMatrix()
		self._findPath(self._fromLen, self._toLen)
		self.operations = tuple(self._operations)
	
	
	def __str__(self):
		buf = StringIO.StringIO()
		self._writeMatrix(buf)
		return buf.getvalue()
	
	
	def _newMatrix(cols, rows, initValue):
		''' Helper method that creates a matrix. '''
		matrix = []
		for y in range(rows):
			matrix.append([initValue] * cols)
		return matrix
	_newMatrix = staticmethod(_newMatrix)
	
	
	def _calculateMatrix(self):
		''' Calculate the Levenshtein distance matrix. '''
		m = self._levenshteinMatrix
		m[0][0] = 0
		for y in range(self._toLen + 1):
			for x in range(self._fromLen + 1):
				values = []
				# calculate (x/y)...
				if x > 0 and y > 0: # coming diagonally
					same = self._from[x - 1] == self._to[y - 1]
					values.append(m[x - 1][y - 1] + (0 if same else 1))
				if x > 0: # coming from the left
					values.append(m[x - 1][y] + 1)
				if y > 0: # coming from above
					values.append(m[x][y - 1] + 1)
				
				# Smallest value is used
				if len(values) > 0: m[x][y] = min(values)
	
	
	def _findPath(self, x, y):
		'''
			Find a path by backtracking through the calculated matrix. A
			description of the steps taken is stored in the list operations,
			and the path is stored in the matrix path.
			
			x and y give the starting position.
		'''
		m = self._levenshteinMatrix
		if x == 0 and y == 0:
			self._pathMatrix[x][y] = 1
			return True
		
		if x > 0 and y > 0 and m[x][y] == m[x - 1][y - 1] and self._from[x - 1] == self._to[y - 1]:
			if self._findPath(x - 1, y - 1):
				self._pathMatrix[x][y] = 1
				self._operations.append("Keep '%c'" % self._from[x - 1])
				return True
			
		if x > 0 and m[x][y] == m[x - 1][y] + 1:
			if self._findPath(x - 1, y):
				self._pathMatrix[x][y] = 1
				self._operations.append("Delete '%c'" % self._from[x - 1])
				return True
			
		if y > 0 and m[x][y] == m[x][y - 1] + 1:
			if self._findPath(x, y - 1):
				self._pathMatrix[x][y] = 1
				self._operations.append("Insert '%c'" % self._to[y - 1])
				return True
			
		if x > 0 and y > 0 and m[x][y] == m[x - 1][y - 1] + 1:
			if self._findPath(x - 1, y - 1):
				self._pathMatrix[x][y] = 1
				self._operations.append("Replace '%c' with '%c'" % (self._from[x - 1], self._to[y - 1]))
				return True
		
		return False
		
		
	def _writeMatrix(self, output):
		'''
			Write the Levenshtein distance matrix to output, which must
			be a file like object.
		'''
		m = self._levenshteinMatrix
		p = self._pathMatrix
		
		ansi = sys.platform != 'win32'
		bold = '\033[1m' if ansi else ''
		reverse = '\033[7m' if ansi else ''
		reset = '\033[0m' if ansi else ''
		width = 1 + int(math.log10(max(reduce(lambda a, b: a + b, m, []))))
		colTempl   = (       '%%%dc '         if ansi else ' %%%dc ') % width
		numTempl   = (       '%%%dd '         if ansi else ' %%%dd ') % width
		hlNumTempl = (bold + '%%%dd ' + reset if ansi else '=%%%dd ') % width
		
		for y in range(-2, self._toLen):
			for x in range(-2, self._fromLen):
				if x == -2: # row header
					output.write(reverse)
					if y == -2: output.write('    ')
					elif y == -1: output.write('   ' + reset + ' ')
					else: output.write(' %c ' % self._to[y] + reset + ' ')
				elif y == -2: # column header
					output.write(reverse + (colTempl % (self._from[x] if x >= 0 else ' ') + reset))
				else: # values
					highlight = p[x + 1][y + 1] == 1
					output.write((hlNumTempl if highlight else numTempl) % m[x + 1][y + 1])
			output.write('\n')
	
	def printOperations(self):
		output.write('\n'.join(self._operations) + '\n')


if __name__ == '__main__':
	try:
		main()
	except KeyboardInterrupt:
		sys.exit(255)