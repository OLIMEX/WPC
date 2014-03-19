class Clock:
	def __init__( self ):
		self.h = 0
		self.m = 0
		self.s = 0
		
	def tick( self ):
		self.s += 1
		if self.s > 59:
			self.s = 0
			self.m += 1
			
		if self.m > 59:
			self.m = 0
			self.h += 1
			
		if self.h > 23:
			self.h = 0
			
	def positions(self):
		s = ( self.s * 1/60. )

		m = ( self.m * 1/60. )
		m += ( s * 1/60. )

		h = ( self.h % 12 ) * 1/12.
		h += ( m * 1/60. )
		
		return [ h, m, s ]
		
	def tell(self):
		print '{0:02d}:{1:02d}:{2:02d}'.format( self.h, self.m, self.s )
	
	def run(self):
		while self.h != 12:
			p = self.positions()
		
			self.tick()
		
			n = self.positions()
			if p[ 1 ] <= p[ 0 ] and n[ 1 ] > n[ 0 ]:
				self.tell()
			
clock = Clock()
clock.run()


