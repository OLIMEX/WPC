import matplotlib.pyplot as plt
from math import cos, sin
import wave
import struct

# http://matplotlib.org/1.3.1/api/pyplot_api.html
# http://rosettacode.org/wiki/Fast_Fourier_transform#Python
# https://docs.python.org/2/library/wave.html
# https://docs.python.org/2/library/struct.html

# e**jz = cos(z) + jsin(z) ; Euler's identity
def expj(z): 
    return cos(z) + 1.0j * sin(z)

def fft(x):
    pi = 3.14159265359
    N = len(x)
    if N <= 1: 
        return x
    #butterfly, this means it computes only power of two size of list
    even = fft(x[0::2]) 
    odd =  fft(x[1::2])
    return [even[k] + expj(-2.0*pi*k/N)*odd[k] for k in xrange(N/2)] + \
           [even[k] - expj(-2.0*pi*k/N)*odd[k] for k in xrange(N/2)]

def readwav(s):
    if s == '':
        return 0
    if len(s) == 2:
        ssize = "<H"
    elif len(s) == 4:
        ssize = "<L"
    else:
        ssize = ""
    return struct.unpack(ssize, s)[0]
    
fig = plt.figure()
ax1 = fig.add_subplot(211)

fw = wave.open("sqr1000Hz.wav", "r")
#Unfortunatey, ploting in 2D only real part of complex numbers
#This means ploting DCT instead of FFT ? :D
window_size = 8 #You can change this number, power of two too.
loops = 1 + fw.getnframes() / window_size
if True and loops > 80: #you can limit loops
    loops = 80

x = range(window_size)
while loops>0:
    w = [readwav(fw.readframes(1)) for k in range(window_size)]
    y = fft(w)
    ax1.stem(x, y) 
    x = [k+window_size for k in x]
    loops -= 1

fw.close()
ax1.grid(True)
plt.show()
