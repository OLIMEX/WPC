#!usr/bin/python
#Written by Ricardo M. Prieto Fri, Sep 5 2014 
#richiprieto@crice.org
#Encode String to Braile 

from numpy import *
import sys

j=0

string="helloworld" 

tam=len(string)


class encoder:

    def char(self,nom,i):
        self.nombre=nom
        self.numero=i

    def imprimir(self):
    	
 
	    if self.nombre=="h":
	    	imp = array([['.', ' '], ['.', '.'],[' ', ' ']])#concave

	    elif self.nombre=='e':
	    	imp = array([['.', ' '], [' ', '.'],[' ', ' ']])#concave

	    elif self.nombre=='l':
	    	imp = array([['*', ' '], ['*', ' '],['*', ' ']])#convex

	    elif self.nombre=='o':
	    	imp = array([['.', ' '], [' ', '.'],['.', ' ']])#concav

	    elif self.nombre=='w':
	    	imp = array([[' ', '*'], ['*', '*'],[' ', '*']])#convex

	    elif self.nombre=='r':
	    	imp = array([['.', ' '], ['.', '.'],['.', ' ']])#concave

	    elif self.nombre=='d':
	    	imp = array([['.', '.'], [' ', '.'],[' ', ' ']])#concave

	    elif self.nombre=='a':
	    	imp = array([['.', ' '], [' ', ' '],[' ', ' ']])#concave

	    elif self.nombre=='b':
	    	imp = array([['.', ' '], ['.', ' '],[' ', ' ']])#concave

	    elif self.nombre=='c':
	    	imp = array([['.', '.'], [' ', ' '],[' ', ' ']])#concave

	    elif self.nombre=='f':
	    	imp = array([['.', '.'], ['.', ' '],[' ', ' ']])#concave

	    elif self.nombre=='g':
	    	imp = array([['.', '.'], ['.', '.'],[' ', ' ']])#concave

	    elif self.nombre=='i':
	    	imp = array([[' ', '*'], ['*', ' '],[' ', ' ']])#convex

	    elif self.nombre=='j':
	    	imp = array([[' ', '.'], ['.', '.'],[' ', ' ']])#concave

	    elif self.nombre=='k':
	    	imp = array([['.', ' '], [' ', ' '],['.', ' ']])#concave

	    elif self.nombre=='m':
	    	imp = array([['.', '.'], [' ', ' '],['.', ' ']])#concave

	    elif self.nombre=='n':
	    	imp = array([['.', '.'], [' ', '.'],['.', ' ']])#concave

	    elif self.nombre=='p':
	    	imp = array([['.', '.'], ['.', ' '],['.', ' ']])#concave

	    elif self.nombre=='q':
	    	imp = array([['.', '.'], ['.', '.'],['.', ' ']])#concave

	    elif self.nombre=='s':
	    	imp = array([[' ', '.'], ['.', ' '],['.', ' ']])#concave

	    elif self.nombre=='t':
	    	imp = array([[' ', '.'], ['.', '.'],['.', ' ']])#concave

	    elif self.nombre=='u':
	    	imp = array([['.', ' '], [' ', ' '],['.', '.']])#concave

	    elif self.nombre=='v':
	    	imp = array([['.', ' '], ['.', ' '],['.', '.']])#concave

	    elif self.nombre=='x':
	    	imp = array([['.', '.'], [' ', ' '],['.', '.']])#concave

	    elif self.nombre=='y':
	    	imp = array([['.', '.'], [' ', '.'],['.', '.']])#concave

	    elif self.nombre=='z':
	    	imp = array([['.', ' '], [' ', '.'],['.', '.']])#concave


	    sys.stdout.write(imp[self.numero,0])
	    sys.stdout.write(imp[self.numero,1])
	    sys.stdout.write(" ")


for i in range(3):	
	s = encoder()
	for j in range(tam):
		s.char(string[j],i)
		s.imprimir()
	sys.stdout.write('\r')