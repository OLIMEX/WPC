#!/usr/bin/python
# Convert a colored image to a grayscale representation of its luminance
# Sotirios Vrachas
# http://stackoverflow.com/a/15686412
# http://en.wikipedia.org/wiki/Grayscale#Converting_color_to_grayscale

import sys
from PIL import Image

im = Image.open(sys.argv[1])
pix = im.load()

for x in range(0, im.size[0]):
	for y in range(0, im.size[1]):
		# sRGB color space gamma expansion
		def expand_sRGB_gamma(Csrgb):
			if (f < 0.04045):
				return Csrgb/12.92
			else:
				return pow(((Csrgb+0.055)/1.055),2.4)
				
		# the three gamma-compressed sRGB primaries Rsrgb, Gsrgb, and Bsrgb,
		# in range(0,1)		
		Rsrgb = pix[x,y][0]/255.0
		Gsrgb = pix[x,y][1]/255.0
		Bsrgb = pix[x,y][2]/255.0

		# corresponding linear-intensity value R, G, and B, in range(0,1)
		# gamma compression function removed via gamma expansion
		R = expand_sRGB_gamma(Rsrgb)
		G = expand_sRGB_gamma(Gsrgb)
		B = expand_sRGB_gamma(Bsrgb)

		# Luminance is calculated as a weighted sum of the three
		# linear-intensity values. The sRGB color space is defined in terms 
		# of the CIE 1931 linear luminance Y.
		# The coefficients represent the measured intensity perception of 
		# typical trichromat humans, depending on the primaries being used; 
		# in particular, human vision is most sensitive to green and least
		# sensitive to blue.
		Y = 0.2126 * R + 0.7125 * G + 0.0722 * B

		# To encode grayscale intensity in linear RGB, each of the three 
		# primaries can be set to equal the calculated linear luminance Y
		# (replacing R,G,B by Y,Y,Y to get this linear grayscale).
		# Linear luminance typically needs to be gamma compressed to get 
		# back to a conventional non-linear representation. For sRGB, each 
		# of its three primaries is then set to the same gamma-compressed 
		# Ysrgb given by the inverse of the gamma expansion

		# sRGB gamma compressed linear luminance
		def compress_sRGB_gamma(Y):
			if (f <= 0.0031308):
				return 12.92 * Y
			else:
				return 1.055 * pow(Y, 1/2.4) - 0.055

		Ysrgb = int(compress_sRGB_gamma(Y) * 255)

		pix[x,y] = (Ysrgb, Ysrgb, Ysrgb)

im.save(sys.argv[2])

