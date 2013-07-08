#!usr/bin/python

# ply library: http://www.dabeaz.com/ply/


# written by Richard Park
# email: richpk21@gmail.com
#
#
# It took me about 11 hours to finish this project
# including time to study how 'ply' library works
# 







import ply.lex as lex
import ply.yacc as yacc
import sys

######## lex ###################
tokens = (
	'PL',
	'PR',
	'ADD',
	'SUB',
	'MUL',
	'DIV',
	'NUM'
	)

t_PL = (r"[(]")
t_PR = (r"[)]")
t_ADD = (r"[+]")
t_SUB = (r"[-]")
t_MUL = (r"[*]")
t_DIV = (r"[/]")


def t_NUM(t):
	r"\d+"
	t.value = int(t.value)
	return t

def t_error(t):
	raise TypeError("Unknown text '%s'" % (t.value,))

#lex.lex()
####### yacc ################
class Atom(object):

	def __init__(
				self, 
				name="", pl=False, pr=False, 
				add=False, sub=False, mul=False, 
				div=False, num=False, val=0, op=False
				):


		object.__init__(self)
		self.up=None
		self.left=None
		self.right=None
		self.down=None

		self.pl = pl
		self.pr = pr
		self.plpr = False
		self.add = add
		self.sub = sub
		self.mul = mul
		self.div = div
		self.num = num
		self.val = val
		self.op = op

		self.name = name
		
		
		
		
	def copy(self):
		a=Atom()
		a.up=self.up
		a.left=self.left
		a.right=self.right
		a.down=self.down
		a.pl=self.pl
		a.pr=self.pr
		a.plpr=self.plpr
		a.add=self.add
		a.sub=self.sub 
		a.mul=self.mul
		a.div=self.div 
		a.num=self.num 
		a.val=self.val
		a.name=self.name
		a.op=self.op
		return a

	def put(self,a):

		
		while self.right != None:
			self=self.right
			
		if a.pr:
			while self.pl == False and self.up:
				#print "search...", self.name
				self = self.up
			self.pl = False
			self.plpr = True
			self.name = 'plpr'
			self.left = self.right
			self.right = None
			#print  "[%s -- %s]" % (self.name, self.left.name), '(1)'
		
		elif (a.op):
			if self.up:
				if (self.num or self.plpr) and (self.up.add or self.up.sub) and (a.mul or a.div) :
					a.up = self.up
					a.left = self.up.right
					self.up.right = a
				elif (self.num or self.plpr) and (self.up.mul or self.up.div) and (a.add or a.sub) :
					a.up = self.up.up
					self.up.up.right = a
					self.up.up = a
					a.left = self.up
				else:
					self.right = a
					a.up = self
					self.rotate_left()
					#print  "[%s -- %s]" % (a.name, self.name), '(2)'
			else:
				#if (self.num or self.plpr) and (self.up.add or self.up.sub) and (a.mul or a.div) :
				#	a.up = self
				#	a.left = self.right
				#	self.right = a
				#elif (self.num or self.plpr) and (self.up.mul or self.up.div) and (a.add or a.sub) :
				#	a.up = self.up.up
				#	self.up.up.right = a
				#	self.up.up = a
				#	a.left = self.up
				#else:
					self.right = a
					a.up = self
					self.rotate_left()
					#print  "[%s -- %s]" % (a.name, self.name), '(2)'
			
		else:
			self.right=a
			a.up = self
			#print "[%s -- %s]" % (self.name ,a.name), self.right.name, '(3)'


			
				
			
	def remove(self):
		if self.up.right != None:
			self.right.up = self.up
			self.up.right = self.right
			#print 'remove top right'
		elif self.up.left != None :
			self.left.up = self.up
			self.up.left = self.left
			#print 'remove top left'
		else:
			print' wtf removew'
		#print 'rem',self.right.name
			





	def rotate_left(self):
		if self.right:
			self.up.right = self.right
			self.right.up = self.up
			self.up = self.right
			self.right.left = self
			self.right = None
			

			
	def rotate_right(self):
		if self.left:
			temp = self.left
			if self.left.right:
				self.left = temp.right
			temp.up = self.up
			temp.right = self
			self.up = temp
			
	def print_tree(self):
		s = '<%s>' % self.name
		if self.left:
			s+='-l-'+self.left.name
		if self.right:
			s+='-r-'+self.right.name
		if self.up:
			s+='-u-'+self.up.name
		#print s
		
		
		if self.left:
			self.left.print_tree()
		if self.right:
			self.right.print_tree()
			
		if self.name == 'num':
			print self.val
		elif self.name == 'top':
			pass
		else:
			print self.name
			
			
			
	def print_postfix(self):
		s = '<%s>' % self.name
		if self.left:
			s+='-l-'+self.left.name
		if self.right:
			s+='-r-'+self.right.name
		if self.up:
			s+='-u-'+self.up.name
		#print s
		
		
		if self.left:
			self.left.print_postfix()
		if self.right:
			self.right.print_postfix()
			
		if self.name == 'num':
			sys.stdout.write( str(self.val)+' ')
		elif self.name == 'top' or self.plpr:
			pass
		elif self.add:
			sys.stdout.write( '+ ' )
		elif self.sub:
			sys.stdout.write( '- ' )
		elif self.mul:
			sys.stdout.write( '* ' )
		elif self.div:
			sys.stdout.write( '/ ' )
		else:
			sys.stdout.write( self.name+' ')
	

	@staticmethod
	def stack_push(stack, a):
		while stack.up != None:
			stack=stack.up
		stack.up = a
		stack.up.down = stack

	@staticmethod
	def stack_pop(stack):
		while stack.up:
			stack = stack.up
		stack.up.down =  None
		return stack



stack = Atom(name='stack-head')
##############################3
mylist = []


def p_expr(p):
	"""
	expr : factor expr_tail
	"""
	#print 'expr', len(p)

def p_expr_tail(p):
	"""
	expr_tail :
	expr_tail : addop factor expr_tail 
	"""
	#print 'expr-t', len(p)


def p_factor(p):
	"""
	factor : primary factor_tail
	"""
	#print 'factor', len(p)


def p_factor_tail(p):
	"""
	factor_tail :
	factor_tail : mulop primary factor_tail
	"""
	#print 'factor_tail', len(p)




def p_primary(p):
	"""
	primary : pl expr pr
	primary : num
	"""
	#print 'primary', len(p)


def p_addop(p):
	"""
	addop : add
	addop : sub
	"""
	#print 'addop', len(p)


def p_mulop(p):
	"""
	mulop : mul
	mulop : div
	"""
	#print 'mulop', len(p)

def p_num(p):
	"""
	num : NUM
	"""
	Atom.stack_push(stack, Atom( num=True, name = 'num', val=p[1]) )

def p_pl(p):
	"""
	pl : PL
	"""
	Atom.stack_push(stack, Atom( pl=True, name = 'pl'))
	

def p_pr(p):
	"""
	pr : PR
	"""
	Atom.stack_push(stack, Atom( pr=True, name = 'pr'))

def p_add(p):
	"""
	add : ADD
	"""
	Atom.stack_push(stack, Atom( op=True, add=True, name = 'add'))


def p_sub(p):
	"""
	sub : SUB
	"""
	Atom.stack_push(stack, Atom(op=True, sub=True, name = 'sub'))



def p_mul(p):
	"""
	mul : MUL
	"""
	Atom.stack_push(stack, Atom(op=True, mul=True, name = 'mul'))


def p_div(p):
	"""
	div : DIV
	"""
	Atom.stack_push(stack, Atom(op=True, div=True, name ='div'))





def p_error(p):
	print "Syntax error at '%s'" % p.value
	
#yacc.yacc()	


######################3
import collections






lex.lex()
yacc.yacc()	

text = "2-3*4"
text = raw_input("Enter a number: ")



lex.input(text)

for tok in iter(lex.token, None):
	#print repr(tok.type), repr(tok.value)
	pass
#print '1 ***************'
yacc.parse(text)
#print '2 ***************'


s = stack
while s != None:
	#print s.name
	s=s.up



#print '3 ********************'
tree = Atom(name='top')

s=stack
while s != None:
	if s.name != 'stack-head':
		#print s.name
		tree.put(s.copy())
	s=s.up
#print '4 *********************'

tree.print_postfix()
print	
#tree.print_tree()
##print '5 ****************'
