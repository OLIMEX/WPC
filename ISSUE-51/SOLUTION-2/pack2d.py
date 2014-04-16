#!/usr/bin/env python3
#-*- coding:utf-8 -*-

# 2014-04-27, kantal59
# case study in 2D for WPC#51
# Licence: GPL

# ( Note: You can play with obstacles removing some free blocks from B, but not tested yet. )

class Box():

	def __init__( self, width, height, rects):
	
		self.width= int(abs(width))
		self.height= int(abs(height))
		
		self.B=[]		# Coordinates of the free units (x,y), counting from (1,1)
		self.R= rects	# rectangles to be placed into the box (width,height)
		self.POS=[]		# placed rectangles (x,y,width,height), counting from( 1,1, , )
		
		
	def area_check( self):
		
		print( "Box dimension: {0} x {1}\nRects(R)= {2}".format( self.width,self.height, self.R) ) 
		lth= len(self.R)
		self.R= [ ( int(abs(dx)), int(abs(dy)) ) for (dx,dy) in self.R ]
		self.R= [ (dx,dy) for (dx,dy) in self.R 	if 	    ( dx<=self.width and dy<=self.height)  
														or  ( dy<=self.width and dx<=self.height ) ] # rects can be rotated
		
		if len(self.R) != lth:	 
			print(" - some too large rects removed")
			lth= len(self.R)
		
		while True:		
			v=0
			for r in self.R:		v+= r[0]*r[1]
			if v <= self.width * self.height:	break;
			self.R.pop()			
		
		if lth != len(self.R):	print(" - box area was too small, some rects are removed")



	def create_units( self):
		# from east to west and from south to north
		self.B= [ (x,y) for y in range(1, self.height+1) for x in range(1, self.width+1) ]		


	def fit( self, point, rect):

		px,py = point
		rdx,rdy = rect
	
		for x in range( px,px+rdx):
			if (x,py) not in self.B:			return( False)
			if (x, py+rdy-1) not in self.B:		return( False)
		for	y in range( py, py+rdy):
			if (px,	y) not in self.B:		return( False)
			if (px+rdx-1,y) not in self.B:	return( False)
	
		return(True)
	
	
	def alloc( self, point,rect):
	
		px,py = point
		rdx,rdy = rect
	
		for y in range(py, py+rdy):
			for x in range(px, px+rdx):
				self.B.remove( (x,y) )
	
	

	def calc( self):
	
		self.R.sort(key=lambda r: r[0]*r[1], reverse=True)	# sorting by area
		lth= len(self.R);	
		
		self.area_check()
		if lth != len(self.R):		lth= len(self.R);	print("Rects(R)=",self.R)
			
		self.create_units() # calc the free units for B and save it into U, too
		U=self.B[:]
		OPT=[]	# store partialy solved result
		
		
		lth= len(self.R)
		for n in range( lth):	# max lth try with R, in each try the R will be modified somewhat
		
			self.B= U[:]
			self.POS=[]		
			for i in range(lth): # try

				r= self.R[i]	# get the next rect
				rdx,rdy = r
			
				for point in self.B:	# try to fit the rect to a point 
					if self.fit( point,r):
						self.alloc( point,r)
						self.POS.append( (point[0],point[1],rdx,rdy) );	
						break

					if rdx!=rdy: 	# on unsuccess and if the rectangle is not a square, rotate it and try again
						if self.fit( point, (rdy,rdx) ):
							self.alloc( point, (rdy,rdx) )
							self.POS.append( (point[0],point[1], rdy,rdx ) );	
							break

			
			if lth != len(self.POS):	# all the rects are placed?
				q= self.R[n]			# modify R to give chance next try, you can do other mystic things here
				self.R[n]= (q[1],q[0])	
				# save a partial solution, you can check the covered area instead of the number of placed rects
				# it is displayed only if there is no other solution
				if len( self.POS) > len(OPT) :	OPT= self.POS[:]	
			else:
				return(True)			

		self.POS= OPT[:]
		return(False)
		
		
		
	def show(self):
		import tkinter as tk
	
		win= tk.Tk()
		w,h = win.maxsize()
		can= tk.Canvas( win,width= w, height= h)
		can.pack()
		can.update_idletasks()
		w,h = can.winfo_width(), can.winfo_height()
		unit= min( w//self.width, h//self.height )
		can.config( width= self.width * unit);		can.config( height= self.height * unit)	
		
		for r in self.POS:
			x,y,dx,dy = r		# (x,y) counting from (1,1)
			x-=1;	y-=1
			y= self.height - y - dy	# mirror the top left corner (height-y) and calculate the new top left( -dy )
			
			x0, y0, x1, y1 = x*unit, y*unit, (x+dx)*unit, (y+dy)*unit
			can.create_rectangle( x0,y0,x1,y1, width=4, fill='gray' )

		for x in range( self.width):
			can.create_line( x*unit,0, x*unit, self.height*unit, fill='darkblue')
		for y in range( self.height):
			can.create_line( 0,y*unit, self.width*unit, y*unit, fill='darkblue')			

		win.title("Case study in 2D for WPC#51")
		win.resizable(width=False, height=False)
		win.mainloop()			
		


if __name__ == "__main__":		
#----------------- MAIN -----------------
# Rectangles to be placed, (width,height)
#	box= Box( 6,6, [ (1,1),(2,2),(2,2),(2,2),(4,3),(2,2),(3,2),(2,2),(1,5) ] )
#	box= Box( 6,6, [ (1,1),(2,2),(2,2),(2,2),(4,3),(3,2)] )
#	box= Box( 10,6,[ (2,10),(2,6),(4,3),(1,1) ] )
#	box= Box( 4,5, [ (2,3),(1,3),(1,3),(5,1) ] )
#	box= Box( 4,5, [ (3,2),(1,3),(1,3),(5,1) ] )
#	box= Box( 9,12, [ (1,1),(2,2),(2,2),(2,2),(3,4),(2,2),(2,3),(2,2),(1,5),(1,1),(2,2),(2,2),(2,2),(4,3),(2,2),(3,2),(2,2),(5,1) ] )
	box= Box( 20,8, [ (1,1),(2,2),(2,2),(2,2),(3,4),(2,2),(2,3),(2,2),(1,5),(1,1),(2,2),(2,2),(2,2),(4,3),(2,2),(3,2),(2,2),(5,1) ] )
#	box= Box( 5,5, [ (6,1),(3,3),(1,1),(2,2) ] )
#	box= Box( 5,5, [ (2,3), (4,4) ] )  # each rects fits into the box, but not together


	rtcd= box.calc()	# not reentrant (but easy to modify:)
		
	#print("Free units(B)=",box.B)
	
	if rtcd:
		print(" - Success: placed rects(POS)= ",box.POS)		
	else:
		print(" - Failed: partial solution= ", box.POS) 

	box.show()		# not reentrant
	













		
		
