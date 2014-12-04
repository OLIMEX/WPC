##WPC - OLIMEX's WEEKEND PROGRAMMING CHALLENGE

###ISSUES 51-100



#####issue51: Container load
Freight company have N parcels with different dimensions to fit in 20 feet containers. Make code which optimally fill containers inside volume. Assume that there is no limitations to stack the parcels.


#####issue52: H-bot
H-bot is simple way to control X-Y CNC table with just two stepper motors and string. More on the subject you can find 
on the net. Make code which moves the CNC table at position X,Y by rotating the two stepper motors. You know the string 
length, motor shaft diameter, etc parameters. Starting from center 0,0 you calculate the rotation angle of both motors 
when new X,Y coordinate is entered. 0,0 is in the center so XY can be positive and negative.
 		 

#####issue53: Random Number Generator
Make your own Random Number Generator.
       
       
#####issue54: FFT
Fourier Transform is basic instrument for spectrum analyze of signals. 
Make Fast Fourier Transform (FFT) implementation in your favourite language, try to compute the spectrum  on sample sound file and to visualize it.


#####issue55: Draw Bot
Today’s challenge was inspired by this article: http://makezine.com/projects/trs-drawbot/ .
Simple draw bot draws continual line without lifting the pen up. From what I see the lines do not cross.


#####issue56: Perfect Numbers
Perfect Number is a positive integer that is equal to the sum of its proper positive divisors.
This weekend try to calculate the largest Perfect Number you can and let us know what result did you got.


#####issue57: Text to HTML ratio calculator
Some people think text to HTML tags ratio on web page is important parameter for Google indexing 
and good sites should have about 20-30% ratio of pure text vs HTML tags.
Make code which calculates Text/HTML ratio on given html page.


#####issue58: Date to Seconds converter
Make code which enters Gregorian calendar date in format: Day/Month/Year and calculates how many seconds passed since the beginning.


#####issue59: Big – Little Endians
Make code which detects on what machine is ran – with Big or Little Endian. Can you do it in other language than C?


#####issue60: PTC linearization
KTY81/110 is non linear resistor which increases it’s value with temperature. 
You can read the datasheet here: http://www.nxp.com/documents/data_sheet/KTY81_SER.pdf
Make code which input KTY81/110 real number of resistance in ohms and output the temperature of the sensor.


#####issue61: Plus-Minus
Insert + and – in the equation below to make it right:

		1 2 3 4 5 6 7 8 9 = 100
		like
		1 + 2 + 3 – 4 + 5 + 6 + 7 8 + 9 = 100
		
Make code which finds all solutions.


#####issue62: One million
One million is good round number :) Your task for the weekend challenge is to write code which check if you can find two numbers X and Y which product makes exactly 1 000 000, the catch is that none of these numbers should contain 0 inside it. How fast is your code?


#####issue63: Braille encoder
Braille is a tactile writing system used by the blind and the visually impaired. It is traditionally written with embossed paper. Generally with three lines of embossed dots either convex either concave. Make Braille encoder which takes string and prints Braille equivalent on 3 lines with “*” for convex and “.” for concave dots. How do you print "helloworld"?


#####issue64: Color to Gray scale converter
To convert color to gray scale image is easy all you have to do is to find function which converts (R,G,B) to gray levels. There are many algorithms, simple is average grayscale = (r+g+b)/3 which works somehow but not quite well as with this algorithm all color R,G,B are translated to same grayscale level (255,0,0) = (0,255,0) = (0,0,255) but human eye have different sensitivity for the different colors, which may be taken into account to make better converter. What can you invent?


#####issue65: PCB resistance calculator
Make PCB track resistance calculator which takes these input parameters:

 - track width  in units: (mm) or (mils)
 - track thickness in units: (mm) or (mils) or (oz per sq.ft)
 - track length in units: (mm) or (mils)
 - number of vias this track goes through
 - vias plating thickness in units (mm) or (mils)
 - vias drill diameter in units (mm) or (mils)

and displays resistance in Ohms.


#####issue66: Christmas Tree ASCII art
Write shortest code which print on the console Christmas tree with ASCII art.


#####issue67: Missing pages in book
There is a book and a number of consecutive pages are missing from this book. All we know is that the sum of the page numbers 
of these pages is 9808. Make code which calculates which are the missing pages and displays the result.


#####issue68: Text Formatting
Input text and width, then format the text in this width to be with no spaces at the end of the line. 
You can use this text to test your code: http://www.gutenberg.org/files/11/


#####issue69: Levenshtein Distance 
Levenshtein Distance  is string metrics for measuring the difference between two sequences. 
Make code which inputs two strings and calculate Levenshtein Distance between them.


#####issue70: Math with words
Make code which enters expression like "3525 + 133 =" and solve it. Easy right? 
Here is the catch is that numbers and operations are replaced by their words equivalents.
Please support numbers up to 1 000 000 and these operators + – * /

		Example:
				input: "three thousands five hundreds and twenty five plus one hundred and thirty three is equal to"
				output: "3658"
		 
		 
