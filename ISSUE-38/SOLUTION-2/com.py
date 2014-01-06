# http://olimex.wordpress.com/2013/12/20/weekend-programming-challenge-week-38-center-of-mass/
import Image
indices = [i for i, px in enumerate( Image.open('100x100.png').getdata() ) if px == 0]
print  ( float(sum([ x % 100 for x in indices]))/len(indices)  , float(sum([ y // 100 for y in indices]))/len(indices) )

