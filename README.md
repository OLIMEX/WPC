# WPC - OLIMEX’s WEEKEND PROGRAMMING CHALLENGE

From history:

> The idea for this Weekend Programming Challenge came as follow up of
> our [Friday Free Board
> Quiz](http://olimex.wordpress.com/2013/03/22/weekend-programming-challenge).
> It’s over the weekend competition, where every Friday we post problem
> on our blog and you have one weekend time to think and come with the
> best solution. In Monday we will upload the solutions here and by the
> end of the day we will analyze and rise winner.
>
> After we post the solutions everyone is welcome to e-mail us at
> support \[at\] olimex \[dot\] com their favourite solution with
> arguments why they think this solution is best. This way we will be
> sure that more eyes will look at the codes and we may not miss
> something :)

# Table of Contents

## [Issue 01](ISSUE-1/): Distance

In 2D coordinate system we have three points A(x,y) B(x,y) C(x,y) where
x,y can be positive and negative integer numbers. If Points A and B
define endless line, write function which returns the distance between
point C and the line defined by point A, B.

## [Issue 02](ISSUE-2/): Sort differences

If `A[N]` is array of `N` integers shuffle the elements of `A` in such
way that the differences between each neighbour elements `d[i] = A[i] -
A[i+1]` make row in ascending order. For instance: `A[4] = { 10, 2, 7, 4
}`
possible solutions are:

    { 2, 7, 10, 4 } because  (2 – 7) < (7 – 10) < (10 – 4)
    { 4, 10, 7, 2 } because  (4 – 10) < (10 – 7) < (7 – 2)

## [Issue 03](ISSUE-3/): Differences of unique words

Let’s have N different strings/words and for each word print the minimum
part of it which makes it unique toward others.

## [Issue 04](ISSUE-4/): The longest isogram word

Scan text and displays the longest isogram word(s) (with all letters
different) found in the text.

## [Issue 05](ISSUE-05/): Calculating Pi using the Buffon’s needle method.

## [Issue 06](ISSUE-6/): PCB CNC drill machine path optimizer

CNC drill machine drills holes in Printed Circuit Boards (PCB) with
maximum board size (i.e. maximal coordinates of the drill holes) 999.999
x 999.999 mm
The machine head have task to drill between 1 and 2000 holes on the
PCB.
To drill the holes the machine takes input file in the following format:

  - first row define drill size: Txx where xx is the drill size 01 = 0.1
    mm , 09 = 0.9 mm, 12 = 1.2 mm etc etc up to 99 = 9.9 mm
  - next rows define X Y coordinates: XaaaaaaYaaaaaa where aaaaaa is the
    coordinates with fixed point 3.3 arithmetic i.e. 001550 = 1.55 mm

Your code should first do DRC check:

  - if there are drill holes with duplicated coordinates and remove the
    duplicate
  - if there are overlapping holes, if such overlapping holes are found
    they have to be reported and code to stop
  - if hole extends behind board dimensions error should be reported
    i.e. center of the hole is inside the board area but the hole radius
    extend the hole behind the board border

Then your code should sort the X-Y lines in such order that the machine
head to make the optimal (shortest) path which starts from 0,0 and ends
to 0,0 going through all XY drill positions.

## [Issue 07](ISSUE-7/): Cat jumps

Cat can jump one or two steps on stairs, make code which calculate how
many different ways the cat can climb from bottom to top of N-size
stairs.

## [Issue 08](ISSUE-8/): Unbeatable Hangman game

Make All-winner Hangman game, make the computer unbeatable. Each time
the player guess letter, if this letter is in your word you have to scan
the dictionary for similar word (if possible and do not break the game
rules) which have no such letter and replace it, so player is always
wrong.

## [Issue 09](ISSUE-9/): Points and circle

Let have N (3..100) points with X,Y coordinates. Make code which checks
if there is circle which to pass through all of them.

## [Issue 10](ISSUE-10/): Fraction representation

Let 0 \< (a/b) \< 1 where a and b are positive integers. Make program
which enters the numbers a and b then represent a/b with as sum of
numbers 1/n + 1/n2 + 1/n3… and prints the n numbers.

## [Issue 11](ISSUE-11/): Maze and obstacles

Let’s have a maze with size X x Y where X and Y are integer (3..100) .
The maze is defined with strings, where in the string ‘W’ is wall, ‘@’
is obstacle and ‘ ‘ is air. Make code which finds the largest by area
connected obstacles in the maze.

## [Issue 12](ISSUE-12/): Similar words

Similar word are these which differs by one character only i.e. one
character changed or inserted or deleted. For example: if using this
concept the word “hello” is considered similar to “hella” and to “hell”
or “shello”. Make code which enters word then scans: *Alice’s Adventures in Wonderland*
 and prints all similar words to the one which is entered.

## [Issue 13](ISSUE-13/): Make code which converts picture to ASCII art

Hints: This is very easy challenge although seems hard at first sight.
Just convert the picture from color to gray scale, then select font
which you will use to print ASCII art and analyze it which letters you
could use for gray scale print – every letter have some coefficient of
filling from 0 for the space to 255 for solid bar, use letters which are
spread well in the font size space. Then slice your image at rectangles
with the font size, calculate the median grey scale for each rectangle
and print the corresponding ASCII character with same grey scale value.
As test image you can use everything – from Olimex logo to Lena above.

## [Issue 14](ISSUE-14/): Compute Pi to the maximal precision you can in relatively real time

Tip: Use Leibniz formula and find way to work with very big numbers like
hundred or thousands of digits.

## [Issue 15](ISSUE-15/): Unformatted C language text file and brackets

Make code which reads not formatted C language text file and format the
brackets i.e. moves the closing bracket as same column as the
corresponding opening bracket, ignoring the comments. If the brackets
doesn’t match should issue error message.

## [Issue 16](ISSUE-16/): Convert Infix Notation to Postfix Notation

Input string which is mathematical statement written in normal Infix
Notation and convert it to Postfix Notation.

## [Issue 17](ISSUE-17/): Skytales

Ancient Greeks and Spartans used Skytales to send encrypted messages,
they wound on bar stripe then write on it, when the stripe is unwound
the letters become shifted and you cant read the message again until you
wound it on rod with same diameter. Write code which crypt and de-crypt
message on Skytale, as input you can take message and diameter of the
rod.

## [Issue 18](ISSUE-18/): Minimal console editor to complement BAS-INT

BAS-INT is freeware tiny Basic interpreter with the bare minimum for
BASIC scripting language. It works with external files only and is with
Basic Stamp like syntax.
The Challenge today is to write minimal console editor which to
complement BAS-INT and to perform some very basic commands:

  - List – list the program in memory with numbers
  - Delete N(-M) – deletes line N or N to M from memory
  - Insert N – inserts line on number N
  - Run – runs the BASIC program in memory (this code is already
    available)

If one wants to make it even more advanced he may make also the

  - Edit N – prints the content of line N and allow it to be edited

Remember this is console application and you have just serial in and
serial out, no fancy graphics and windows in this editor.

## [Issue 19](ISSUE-19/): Pattern match

Make function match() which takes as input input\_string and
pattern\_string, the input strings may contain any ASCII codes. There
are two special codes for use in the pattern-string: `?` replaces 1
character and `*` replaces any character(s). The function should print
all words from the input-string which match the pattern-string.
Words can be separated by any of these characters: `‘ ” . , : ;`
If the input-string have this content “The big black cat jump over the
window”:

```
    if pattern-string is “b*” should print
        big
        black

    if pattern-string is “*c*” should print
        black
        cat

    if pattern-string is “?i*” should print
        big
        window
```

## [Issue 20](ISSUE-20/): Anagrams

An anagram is a type of word play, the result of rearranging the letters
of a word or phrase to produce a new word or phrase, using all the
original letters exactly once; for example ‘orchestra’ can be rearranged
into ‘carthorse’.
Find all anagram words in text file, you can use as word source our well
known: *Alice’s Adventures in Wonderland*

## [Issue 21](ISSUE-21/): Words Puzzle

```
    Aoccdrnig to a rscheearch at Cmabrigde Uinervtisy, it deosn’t mttaer in waht oredr the ltteers in a wrod are,
    the olny iprmoetnt tihng is taht the frist and lsat ltteer be at the rghit pclae. The rset can be a toatl mses
    and you can sitll raed it wouthit porbelm. Tihs is bcuseae the huamn mnid deos not raed ervey lteter by istlef,
    but the wrod as a wlohe.
```

You can see original text here: [MRC Cognition and Brain Sciences
Unit](http://www.mrc-cbu.cam.ac.uk/people/matt.davis/Cmabrigde/)
Write code which takes as input normal text and shuffles the letters
inside the words to make text like this one above.

## [Issue 22](ISSUE-22/): Plagiarism detector

Make code which compare two texts and output the % of similarities
between the two texts i.e. if they have same words even if the words are
in different order. More advanced version may take care for synonyms.

## [Issue 23](ISSUE-23/): Something small and evil

Invent something small and evil which to be almost invisible and to
cause lot of troubles to catch like:

```
    #define struct union
    #define double float
    #define floor ceil
    #define true (__LINE__&42) !=42
    #define private public
```

## [Issue 24](ISSUE-24/): Combinatorics - Integer Partitioning

Write code which calculate the number of ways you can express positive
natural number N as sum of positive natural numbers.

```
    For N=1 we have 1 way;
    for N=3 we have 3 ways: 1+1+1, 1+2, 3;
    etc.
```

## [Issue 25](ISSUE-25/): Equal Travel Paths

If we have matrix with size M x N and two points A(xa,ya) and B(xb,yb),
C obstacles which are entered with their coordinates and length of path
L, make code which:

  - displays all variants (if any) one can move from point A to point B
    by traveling via L cells;
  - you can step on one cell just once and only if the cell have no
    obstacle;
  - the valid moves are only up-down-left-right.

inputs:

  - the matrix size M and N;
  - the points A(x,y) and B(x,y) coordinates;
  - the number of obstacles;
  - the obstacles C(x,y) coordinates;
  - the path length L.

## [Issue 26](ISSUE-26/): Square

Write code which check if four points make square.
Input data for squares:

```
    (0,0),(0,1),(1,1),(1,0)     - normal square
    (0,0),(2,1),(3,-1),(1,-2)   - not aligned square
    (0,0),(1,1),(0,1),(1,0)     - different order of the points
```

input data for non-squares:

```
    (0,0),(0,2),(3,2),(3,0)     - rectangle
    (0,0),(3,4),(8,4),(5,0)     - rhombus
    (0,0),(0,0),(1,1),(0,0)     - three points are same
    (0,0),(0,0),(1,0),(0,1)     - two points are same
```

## [Issue 27](ISSUE-27/): AngryBird

Write code which calculates the trajectory of Angry-bird with these
input parameters:

  - Angle
  - Initial Force
  - Bird Weight
  - Air resistance
  - Earth Gravity

If your tools allow animation great, otherwise even simply ascii art
drawing is OK.

## [Issue 28](ISSUE-28/): Sudoku

Make code which solves Sudoku in 3×3 configuration.
Input: enter the initial cells which are initialized with start
numbers
Check the input for correctness then print solution(s).

## [Issue 29](ISSUE-29/): Make code which scrapes GitHub and extracts all developer’s e-mails.

Note: This is for educational purposes and not to be used for evil\!

## [Issue 30](ISSUE-30/): Converter from decimal to roman numbers.

## [Issue 31](ISSUE-31/): Run Length Encoding/Decoding

RLE/D is the simplest way to compress data
[wiki](http://en.wikipedia.org/wiki/Run-length_encoding)
Implement RLE/D in shortest/simplest way possible using your favourite
language.

## [Issue 32](ISSUE-32/): PCB panelization

Let have N PCBs with rectangular form with size X Y. Make code which
inputs the number of PCBs and their size Xn Yn and the minimal space
between the PCB borders on the panel m in millimeters, then arrange the
PCBs on panel with minimal area.

## [Issue 33](ISSUE-33/): Infinite Output

Write the shortest possible code which will make infinite output.

## [Issue 34](ISSUE-34/): POV LED display

Persistence of Vision (POV) is made with stripe of LEDs which rotates at
360 degree. If we assume the stripe is with 100 LEDs you can make square
“screen” with size approx 140×140 pixels.
Make code which converts 140×140 pixels picture to array of LED stripe
values for each angle 0-360. When LED from the stripe are not at exact
pixel positions the best way to set their value is to mediate the value
depend on the closest pixel neighbors.

## [Issue 35](ISSUE-35/): Maze

Maze with 10×10 cells have obstracles placed on random cells marked with
the black.
Make code which finds path which starts from cell (1,1) and moves
through all Maze cells and returns back to cell(1,1) without stepping on
same cell more than once.

## [Issue 36](ISSUE-36/): NOKIA text message converter

Make code which takes string and convert it to button push sequence on
NOKIA1100 phone keypad which will print same string. For instance: HELLO
-\> 44 33 555 555 666

## [Issue 37](ISSUE-37/): Snake Retro Game

Make your own snake game\! Do you remember the Nokia phones Snake game?
You move the snake with 4 keys and it eats apples on the screen and gets
bigger, collision with walls or snake body ends the game.

## [Issue 38](ISSUE-38/): Center of mass

A picture is 100×100 pixels and have black object on white background.
Make code which calculates the center of mass and display it.

## [Issue 39](ISSUE-39/): CRC-16

Cyclic Redundancy Check is error detecting code used in serial devices
to detect accidental errors in the input data.
Make code which calculates CRC-16.

## [Issue 40](ISSUE-40/): Number approximation

Any positive integer number can be presented as 1 and several operations
\*3 and /2 discarding the result after the decimal point when dividing.
For instance:

```
                     4 = 1 *3 *3 /2
                    12 = 1 *3 *3 /2 *3
```

Make code which enters positive integer N then present it with 1 \*3 /2
equation.

## [Issue 41](ISSUE-41/): Speed typing test

Make code which displays text, then measures how fast and correct one
would enter this test via the keyboard. You can display random text from
online book or dictionary. It’s up to you how to make the user
interface, make something funny and interesting.

## [Issue 42](ISSUE-42/): No-Lift-Pen Drawings

We all know this game where you draw figure on paper without lifting up
your pen and without going through same segment twice.
Write code which enters N segments with their coordinates X1,Y1,X2,Y2
then check if it’s possible to draw all segments without lifting your
pen and if YES write the path sequence.

## [Issue 43](ISSUE-43/): Bank Card validation

Bank card numbers are not random, they carry information for the card
processor (Visa/Mastercard etc), bank which issued the card, the account
and checksum. More on the subject is available at
[wiki](http://en.wikipedia.org/wiki/Bank_card_number)
Make code which enters card number and validate it i.e. writes VALID or
INVALID number has been entered.

## [Issue 44](ISSUE-44/): ECG heart beat detection

We all have seen how ECG looks stylized, in real life there is usually
lot of noise add to this signal. For today’s Challenge I asked one of
our employee – Penko to connect himself to EEG-SMT and to stay calm so
his ECG signal is captured on file. This file is already upload to
GitHub and you can use as input data.
Make code which detect the heart rate using this raw signal info.
Description of the data packages is also upload on Github.

## [Issue 45](ISSUE-45/): Median filter

Median Filter is the simplest way to remove random noise from input
signal. More about it you can read at
[wiki](http://en.wikipedia.org/wiki/Median_filter)
Using the info from the previous [Issue 44](#issue44) challenge, make
Median Filter and experiment with different window sizes to filter the
raw ECG info and to see how it changes the shape of the signal and the
measurements of the pulse rate.

## [Issue 46](ISSUE-46/): Clock arrows

Clock minute and hour arrows cross as they revolve around.
Make code that compute how many times the arrows cross in one twelve
hour period, and print list of those times.

## [Issue 47](ISSUE-47/): Calendar dates substraction

Enter the birthday dates of two persons and display how many
Years/Months/Days one is older than the other.

## [Issue 48](ISSUE-48/): Geometry

Let have three points A(x,y), B(x,y), C(x,y). Make code which prints if
A-\>B-\>C sequence makes clockwise, counter clockwise turn, or A,B,C
stay in one line. In the attached picture ABC makes counter clockwise
turn.

## [Issue 49](ISSUE-49/): Easter date calculator

Make code which enters Year and then calculates the Easter date in both
Western and Orthodox style and display it.

## [Issue 50](ISSUE-50/): Circle find

In window with size 100 x 100 pixels is drawn solid filled circle with
50 pixels diameter at random coordinates X,Y but the circle is
completely inside the window. Make code which finds the circle XY
coordinates.

## [Issue 51](ISSUE-51/): Container load

Freight company have N parcels with different dimensions to fit in 20
feet containers. Make code which optimally fill containers inside
volume. Assume that there is no limitations to stack the parcels.

## [Issue 52](ISSUE-52/): H-bot

H-bot is simple way to control X-Y CNC table with just two stepper
motors and string. More on the subject you can find on the net. Make
code which moves the CNC table at position X,Y by rotating the two
stepper motors. You know the string length, motor shaft diameter, etc
parameters. Starting from center 0,0 you calculate the rotation angle of
both motors when new X,Y coordinate is entered. 0,0 is in the center so
XY can be positive and negative.

## [Issue 53](ISSUE-53/): Random Number Generator

Make your own Random Number Generator.

## [Issue 54](ISSUE-54/): FFT

Fourier Transform is basic instrument for spectrum analyze of signals.
Make Fast Fourier Transform (FFT) implementation in your favourite
language, try to compute the spectrum on sample sound file and to
visualize it.

## [Issue 55](ISSUE-55/): Draw Bot

Today’s challenge was inspired by this article:
[trs-drawbot](http://makezine.com/projects/trs-drawbot/)
Simple draw bot draws continual line without lifting the pen up. From
what I see the lines do not cross.

## [Issue 56](ISSUE-56/): Perfect Numbers

Perfect Number is a positive integer that is equal to the sum of its
proper positive divisors. This weekend try to calculate the largest
Perfect Number you can and let us know what result did you got.

## [Issue 57](ISSUE-57/): Text to HTML ratio calculator

Some people think text to HTML tags ratio on web page is important
parameter for Google indexing and good sites should have about 20-30%
ratio of pure text vs HTML tags.
Make code which calculates Text/HTML ratio on given html page.

## [Issue 58](ISSUE-58/): Date to Seconds converter

Make code which enters Gregorian calendar date in format: Day/Month/Year
and calculates how many seconds passed since the beginning.

## [Issue 59](ISSUE-59/): Big – Little Endians

Make code which detects on what machine is ran – with Big or Little
Endian. Can you do it in other language than C?

## [Issue 60](ISSUE-60/): PTC linearization

KTY81/110 is non linear resistor which increases it’s value with
temperature. You can read the datasheet here:
[KTY81\_SER.pdf](http://www.nxp.com/documents/data_sheet/KTY81_SER.pdf)
Make code which input KTY81/110 real number of resistance in ohms and
output the temperature of the sensor.

## [Issue 61](ISSUE-61/): Plus-Minus

Insert + and – in the equation below to make it right:

    1 2 3 4 5 6 7 8 9 = 100
        like
    1 + 2 + 3 – 4 + 5 + 6 + 7 8 + 9 = 100

Make code which finds all solutions.

## [Issue 62](ISSUE-62/): One million

One million is good round number :) Your task for the weekend challenge
is to write code which check if you can find two numbers X and Y which
product makes exactly 1 000 000, the catch is that none of these numbers
should contain 0 inside it. How fast is your code?

## [Issue 63](ISSUE-63/): Braille encoder

Braille is a tactile writing system used by the blind and the visually
impaired. It is traditionally written with embossed paper. Generally
with three lines of embossed dots either convex either concave. Make
Braille encoder which takes string and prints Braille equivalent on 3
lines with “\*” for convex and “.” for concave dots. How do you print
“helloworld”?

## [Issue 64](ISSUE-64/): Color to Gray scale converter

To convert color to gray scale image is easy all you have to do is to
find function which converts (R,G,B) to gray levels. There are many
algorithms, simple is average grayscale = (r+g+b)/3 which works somehow
but not quite well as with this algorithm all color R,G,B are translated
to same grayscale level (255,0,0) = (0,255,0) = (0,0,255) but human eye
have different sensitivity for the different colors, which may be taken
into account to make better converter. What can you invent?

## [Issue 65](ISSUE-65/): PCB resistance calculator

Make PCB track resistance calculator which takes these input parameters:

  - track width in units: (mm) or (mils)
  - track thickness in units: (mm) or (mils) or (oz per sq.ft)
  - track length in units: (mm) or (mils)
  - number of vias this track goes through
  - vias plating thickness in units (mm) or (mils)
  - vias drill diameter in units (mm) or (mils)

and displays resistance in Ohms.

## [Issue 66](ISSUE-66/): Christmas Tree ASCII art

Write shortest code which print on the console Christmas tree with ASCII
art.

## [Issue 67](ISSUE-67/): Missing pages in book

There is a book and a number of consecutive pages are missing from this
book. All we know is that the sum of the page numbers of these pages is
9808. Make code which calculates which are the missing pages and
displays the result.

## [Issue 68](ISSUE-68/): Text Formatting

Input text and width, then format the text in this width to be with no
spaces at the end of the line. You can use this text to test your code:
[Alice’s Adventures in Wonderland](http://www.gutenberg.org/files/11/)

## [Issue 69](ISSUE-69/): Levenshtein Distance

Levenshtein Distance is string metrics for measuring the difference
between two sequences.
Make code which inputs two strings and calculate Levenshtein Distance
between them.

## [Issue 70](ISSUE-70/): Math with words

Make code which enters expression like `3525 + 133 =` and solve it. Easy
right? Here is the catch is that numbers and operations are replaced by
their words equivalents. Please support numbers up to 1 000 000 and
these operators `+ – * /` Example:

    input: "three thousands five hundreds and twenty five plus one hundred and thirty three is equal to"

    output: "3658"

## [Issue 71](ISSUE-71/): Knock Lock

Make code which implements knock pattern recognition for door
open/close. There must be option to learn knock sequence. Then every
time when this sequence is implemented door lock opens and you signal
this. To simplify the lock we assume between knocks there will be only
two intervals short and long.
For instance your code should be able to “learn” this sequence:

    knock-short-knock-short-knock-long-knock-long-knock-long-knock

i.e. three fast and three slow knocks and this to open the door.
For knock detecting you can use SPACE key press for instance.
