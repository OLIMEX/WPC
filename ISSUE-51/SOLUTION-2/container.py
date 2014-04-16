#!/usr/bin/env python3
#-*- coding:utf-8 -*-

''' 
 2014-04-27 by kantal59
 License: GPL
 OLIMEX WPC#51: Container load
 			Freight company have N parcels with different dimensions to fit in 20 feet containers. 
 			Make code which optimally fill containers inside volume. Assume that there is no limitations to stack the parcels.
 			
 			 There is a "parcel-units" with dimension 1x1. The container dimensions and the parcels ones must be given in units.
			Parcel coordinates are counted from 1. 
			 The free units are stored in a list, in which the order is important. For each parcel, all the free units as beginning point
			 are tested until success. On unsuccess, the parcell will be rotated and the check starts again. If the parcel can not be 
			 placed even after rotations then the initial parcel list will be modified rotating a single parcel, and on a following 
			 unsucces the next parcel.
			 Allocated units for parcells will be removed from the free list. 
			 
 			Not fully tested!
'''

import itertools as it


class Box():

	def __init__( self, width, height, depth, parcels):
	
		self.width= int(abs(width))
		self.height= int(abs(height))
		self.depth= int(abs(depth))
		
		self.B=[]		# Coordinates of the free units (x,y,z), counting from (1,1,1)
		self.R= parcels	# parcels to be placed into the box (width,height,depth)
		self.POS=[]		# placed parcels (x,y,z,width,height,depth), counting from( 1,1,1 , )


	def area_check( self):
		
		print( "Container dimension: {0} x {1} x {2}\nParcels(R)= {3}".format( self.width,self.height, self.depth, self.R) ) 
		lth= len(self.R)
		self.R= [ ( int(abs(dx)), int(abs(dy)), int(abs(dz)) ) for (dx,dy,dz) in self.R ]
		
		dims= sorted( (self.width,self.height,self.depth) )
		rtmp= self.R[:];	self.R=[]
		for r in rtmp:
			rr= sorted( r)
			if rr[0]<=dims[0]  and  rr[1]<=dims[1]	and	 rr[2]<=dims[2] :	self.R.append(r)
		
		if len(self.R) != lth:	 
			print(" - some too large parcels removed")
			lth= len(self.R)
		
		while True:		
			v=0
			for r in self.R:		v+= r[0]*r[1]*r[2]
			if v <= self.width * self.height * self.depth :		break;
			self.R.pop()			
		
		if lth != len(self.R):	print(" - container volume was too small, some parcels are removed")		
		
	


	def create_units( self):
		# from east to west and from south to north and from front to back; the order matters
		self.B= [ (x,y,z) for z in range(1,self.depth+1) for y in range(1, self.height+1) for x in range(1, self.width+1) ]		


	def fit( self, point, parcel):
		# check the sides of the parcel
		px,py,pz = point # counting from (1,1,1) !
		dx,dy,dz = parcel
		
		for x in range( px,px+dx):
			for z in range( pz,pz+dz):
				if (x,py,z) not in self.B:				return( False)	# bottom
				if (x, py+dy-1,z) not in self.B:		return( False)	# top
			for y in range( py,py+dy):
				if (x,y,pz) not in self.B:				return( False)	# front
				if (x,y,pz+dz-1) not in self.B:			return( False)  # back
								
		for	y in range( py, py+dy):
			for z in range(pz,pz+dz):
				if (px,y,z) not in self.B:			return( False)	# left
				if (px+dx-1,y,z) not in self.B:		return( False)	# right
	
		return(True)
	
	
	def alloc( self, point,parcel):
	
		px,py,pz = point
		dx,dy,dz = parcel
	
		for z in range(pz, pz+dz):
			for y in range(py, py+dy):
				for x in range(px, px+dx):
					self.B.remove( (x,y,z) )
	

	def calc( self):
	
		self.R.sort(key=lambda r: r[0]*r[1]*r[2], reverse=True)	# sorting by volume
		lth= len(self.R)
		
		self.area_check()
		if lth != len(self.R):		lth= len(self.R);	print("Parcels(R)=",self.R)
			
		self.create_units() # calc the free units for B and save it into U, too
		U=self.B[:]
		OPT=[]		# store partialy solved result
		RR= self.R[:]	# save R
		
		
		lth= len(self.R)
		dind= [ idx for idx in it.permutations( (0,1,2) ) ]
		ndind= len(dind)
		ltry= lth * ndind
		
		prevrotdim=None
		for n in range( ltry):	# more tries with R, in each try the R will be modified somewhat
		
			p= n // ndind;		ind= n % ndind
			q= RR[p];			qq= ( q[ dind[ind][0]], q[ dind[ind][1]], q[ dind[ind][2]] )		
			if ( p,qq ) == prevrotdim:	continue	# (2,2,1) == (2,2,1)
			prevrotdim= ( p,qq )
			self.R[p]= 	qq  # rotate the p-th parcel at the beginning of the next try
			
			self.B= U[:] # restore the free unit blocks
			self.POS=[]		
			for i in range(lth): # a try

				r= self.R[i]	# get the next parcel
				cp= set([ dim for dim in it.permutations( r) ]) #  permutations of (dx,dy,dz)
				
				for parc in cp:
					success= False
					for point in self.B:	# try to fit the parcel to a point 
						if self.fit( point, parc ):
							self.alloc( point, parc )
							self.POS.append( (point[0],point[1],point[2], parc[0],parc[1],parc[2] ) );	
							success= True
							break
							
					if success:	break

			
			if lth != len(self.POS):	# all the parcels are placed?
				# save a partial solution, it is displayed only if there is no other solution
				# ( you can check the covered area instead of the number of placed parcels)
				if len( self.POS) > len(OPT) :	OPT= self.POS[:]	
			else:
				return(True)			

		self.POS= OPT[:]
		return(False)
		
		



if __name__ == "__main__":		
#----------------- MAIN -----------------
# Rectangles to be placed, (width,height,depth)
# A case from pack2d.py can be tested if all the z-values set to 1, eg.: Box( w,h,1, (dx1,dy1,1),(dx2,dy2,1) ...)

#	box= Box( 2,2,2, [ (1,1,1),(1,1,1),(2,2,1),(1,1,1),(1,1,1) ] )
#	box= Box( 2,2,2, [ (2,2,1),(2,1,2)] )	
#	box= Box( 5,5,1, [ (6,1,1),(3,3,1),(1,1,1),(2,2,1) ] )
#	box= Box( 4,1,16, [ (1,1,1)]*64  )
#	box= Box( 5,5,1, [ (2,3,1), (4,4,1) ] ) # each parcel fits into the box, but not together
#	box= Box( 4,5,1, [ (2,3,1),(1,3,1),(1,3,1),(5,1,1) ] )
#	box= Box( 4,5,1, [ (3,2,1),(1,3,1),(1,3,1),(5,1,1) ] )
#	box= Box( 3,2,1, [(2,1,1) ] )	
#	box= Box( 20,8,1, [ (1,1,1),(2,2,1),(2,2,1),(2,2,1),(3,4,1),(2,2,1),(2,3,1),(2,2,1),(1,5,1),(1,1,1),(2,2,1),(2,2,1),(2,2,1),(4,3,1),(2,2,1),(3,2,1),(2,2,1),(5,1,1) ] )	
#	box= Box( 20,8,8, [ (1,1,1),(2,2,1),(2,2,1),(2,2,1),(3,4,1),(2,2,1),(2,3,1),(2,2,1),(1,5,1),(1,1,1),(2,2,1),(2,2,1),(2,2,1),(4,3,1),(2,2,1),(3,2,1),(2,2,1),(5,1,1) ] )	
	box= Box( 20,8,8, [ (2,2,1) ]*64 + [ (5,5,2)]*10 + [(10,4,3)]  )


	
	print(" - calculating...")
	rtcd= box.calc()	# not reentrant (but easy to modify :-)
	
	#print("Free units(B)=",box.B)
	if rtcd:
		print(" - Success: placed parcels(POS)= ",box.POS)		
	else:
		print(" - Failed: partial solution= ", box.POS) 













		
		
