#!/usr/bin/env python
#-*- coding:utf-8 -*-

''' 
 2014-09-13 by kantal59
 License: GPL
 OLIMEX WPC#64: Color to Gray scale converter
        To convert color to gray scale image is easy all you have to do is to find function which converts (R,G,B) to gray levels. 
        There are many algorithms, simple is average grayscale = (r+g+b)/3 which works somehow but not quite well as with this algorithm
        all color R,G,B are translated to same grayscale level (255,0,0) = (0,255,0) = (0,0,255) but human eye have different sensitivity
        for the different colors, which may be taken into account to make better converter.
		What can you invent?

		Using Python 2.x, Tkinter and PIL.
		You can open multiple windows for gray scale images and play with the RGB weights.( There is no save option :(
		Usage: $ ./graywpc64 [image_file]
'''


from PIL import Image,ImageColor
import ImageTk
import Tkinter as tk
import sys


rootwin=tk.Tk()
rootwin.title("WPC#64 - RGB color to gray scale converter")
rootwin.resizable(width=False, height=False)

picture= "lena.jpg" if len(sys.argv) == 1	else 	sys.argv[1]
try:
	pil_img= Image.open( picture)
except IOError,e:
	print( e);	exit(1)	
	

basedim= 512	
ratio= float(basedim)/max( pil_img.size)
newsize= ( int( ratio*pil_img.size[0]), int( ratio*pil_img.size[1]) )
pil_img= pil_img.resize( newsize, Image.ANTIALIAS )

if pil_img.mode != "RGB":
	pil_img= pil_img.convert("RGB")

ibuf= pil_img.load()

subwindows=[]		# to keep reference to subwindows


class GrayWindow:
	
	count=0
	
	def __init__(self,win,img,buf):
	
		GrayWindow.count+= 1
		self.parent= win
		self.original_img= img
		self.original_buf= buf
		
		self.pilimg= Image.new( "RGB", img.size, "gray" ) # PIL image object
		self.pilbuf= self.pilimg.load()
		
		self.tw= tk.Toplevel(win)
		#self.tw.transient(win)
		self.tw.resizable(width=False, height=False)
		self.oldlabel= None
		
		self.wr, self.wg, self.wb = 1-0.29, 1-0.59, 1-0.11
		#self.wr, self.wg, self.wb =0.29, 0.59, 0.11
		
		self.btnRefresh= tk.Button( self.tw, text="Press to refresh", command=self.scgray)
		self.btnRefresh.grid( row=0, column=1, sticky=tk.S )
		self.btnRefresh.lower()
		
		self.scRed= tk.Scale( self.tw, orient=tk.HORIZONTAL, relief=tk.RAISED, from_=0, to=1, resolution=0.01, fg="red", command=self.__chg_weights__)
		self.scRed.grid(row=1, column=0, sticky=tk.E+tk.W)
		self.scGreen= tk.Scale( self.tw, orient=tk.HORIZONTAL, relief=tk.RAISED, from_=0, to=1, resolution=0.01, fg="darkgreen", command=self.__chg_weights__)
		self.scGreen.grid(row=1, column=1, sticky=tk.E+tk.W)
		self.scBlue= tk.Scale( self.tw, orient=tk.HORIZONTAL, relief=tk.RAISED, from_=0, to=1, resolution=0.01, fg="blue", command=self.__chg_weights__)
		self.scBlue.grid(row=1, column=2, sticky=tk.E+tk.W)

		self.scRed.set( self.wr)
		self.scGreen.set( self.wg)
		self.scBlue.set( self.wb)
		
		
	def __display__(self):
	
		self.tkimg= ImageTk.PhotoImage( self.pilimg)	# Tkinter image object		
		self.label= tk.Label( self.tw, image= self.tkimg )
		self.label.grid(row=0,column=0, columnspan=3)
		if self.oldlabel:
			self.oldlabel.destroy()
		self.oldlabel= self.label	
		
		self.tw.title("{}:  weights(rgb)= {} / {} / {}".format(self.count,self.wr,self.wg,self.wb))
	
	
	def __chg_weights__( self, value):
	
		news  = self.scRed.get(), self.scGreen.get(), self.scBlue.get()
		if abs(news[0]-self.wr) < 0.005  and  abs(news[1]-self.wg) < 0.005  and  abs( news[2]-self.wb) < 0.005:
			return
		self.btnRefresh.lift()
		self.wr, self.wg, self.wb = news
					
		
	def scgray(self):
		
		self.btnRefresh.lower()
		width,height = self.pilimg.size
		for x in range(width):
			for y in range(height):
				r,g,b = self.original_buf[x,y]
				av= int( ( self.wr*r + self.wg*g + self.wb*b )/3 )
				self.pilbuf[x,y] = ( av,av,av )
	
		self.__display__()					




def callback():
	global rootwin, pil_img,ibuf
	w= GrayWindow( rootwin, pil_img, ibuf)
	w.scgray()
	subwindows.append(w)


tk_img= ImageTk.PhotoImage(pil_img)
label= tk.Label( rootwin,image= tk_img)
label.grid(row=0,column=0)
btnNewWindow= tk.Button( rootwin, text="New grayscale window", command= callback )
btnNewWindow.grid( row=1,column=0)

rootwin.mainloop()


