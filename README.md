##WPC - OLIMEX's WEEKEND PROGRAMMING CHALLENGE


The idea for this Weekend Programming Challenge came as follow up of our Friday Free Board Quiz: http://olimex.wordpress.com/2013/03/22/weekend-programming-challenge/
It's over the weekend competition, where every Friday we post problem on our blog and you have one weekend time to think and come with the best solution.
In Monday we will upload the solutions here and by the end of the day we will analyze and rise winner.

After we post the solutions everyone is welcome to e-mail us at support [at] olimex [dot] com their favourite solution with arguments why they think this solution is best.
This way we will be sure that more eyes will look at the codes and we may not miss something :)


###ISSUES



#####issue1: Distance
In 2D coordinate system we have three points A(x,y) B(x,y) C(x,y) where x,y can be positive and negative integer numbers. If Points A and B define endless line, write function which returns the distance between point C and the line defined by point A, B.
        
        
#####issue2: Sort differences
If A[N] is array of N integers shuffle the elements of A in such way that the differences between each neighbour elements d[i] = A[i]-A[i+1] make row in ascending order.

        For instance:   A[4] = { 10, 2, 7, 4 }
        possible soluions are:       { 2, 7, 10, 4 } because  (2 – 7) < (7 – 10) < (10 – 4)
                                     { 4, 10, 7, 2 } because  (4 – 10) < (10 – 7) < (7 – 2)
                                

#####issue3: Differences of unique words
Let’s have N different strings/words and for each word print the minimum part of it which makes it unique toward others.


#####issue4: The longest isogram word
Scan text and displays the longest isogram word(s) (with all letters different) found in the text.


#####issue5: Calculating Pi using the Buffon’s needle method.
    

#####issue6: PCB CNC drill machine path optimizer

CNC drill machine drills holes in Printed Circuit Boards (PCB) with maximum board size (i.e. maximal coordinates of the drill holes) 999.999 x 999.999mm
The machine head have task to drill between 1 and 2000 holes on the PCB.<br>
To drill the holes the machine takes input file in the following format:<br>
  - first row define drill size:  Txx where xx is the drill size 01 = 0.1 mm , 09 = 0.9 mm, 12 = 1.2 mm etc etc up to 99 = 9.9 mm
  - next rows define X Y coordinates: XaaaaaaYaaaaaa where aaaaaa is the coordinates with fixed point 3.3 arithmetic i.e. 001550 = 1.55 mm
Your code should first do DRC check:<br>
  - if there are drill holes with duplicated coordinates and remove the duplicate
  - if there are overlapping holes, if such overlapping holes are found they have to be reported and code to stop
  - if hole extends behind board dimensions error should be reported i.e. center of the hole is inside the board area but the hole radius exted the hole behind the board border
Then your code should sort the X-Y lines in such order that the machine head to make the optimal (shortest) path 
which starts from 0,0 and ends to 0,0 going through all XY drill positions.
        

#####issue7: Cat jumps
Cat can jump one or two steps on stairs, make code which calculate how many different ways the cat can climb from bottom to top of N-size stairs.
        
        
#####issue8: Unbeatable Hangman game
Make All-winner Hangman game, make the computer unbeatable. Each time the player guess letter, if this letter is in your word you have 
to scan the dictionary for similar word (if possible and do not break the game rules) which have no such letter and replace it, 
so player is always wrong.
        
        
#####issue9: Points and circle
Let have N (3..100) points with X,Y coordinates. Make code which checks if there is circle which to pass through all of them.


#####issue10: 
Let 0 < (a/b) <\ 1 where a and b are positive integers. Make program which enters the numbers a and b
then represent a/b with as sum of numbers 1/n + 1/n2 + 1/n3… and prints the n numbers.
        
        
#####issue11: 
Let's have a maze with size X x Y where X and Y are integer (3..100) .
The maze is defined with strings, where in the string ‘W’ is wall, ‘@’ is obstacle and ‘ ‘ is air.
Make code which finds the largest by area connected obstacles in the maze.
        
        
#####issue12: Similar words
Similar word are these which differs by one character only i.e. one character changed or inserted or deleted.
For example: if using this concept the word “hello” is considered similar to “hella” and to “hell” or “shello”
Make code which enters word then scans: http://fiction.eserver.org/novels/alice_in_wonderland.html and prints all 
similar words to the one which is entered.
        
        
#####issue13: Make code which converts picture to ASCII art.
Hints: This is very easy challenge although seems hard at first sight. Just convert the picture from color to gray scale,
then select font which you will use to print ASCII art and analyze it which letters you could use for gray scale print – every
letter have some coefficient of filling from 0 for the space to 255 for solid bar, use letters which are spread well in the font
size space. Then slice your image at rectangles with the font size, calculate the median grey scale for each rectangle and print
the corresponding ASCII character with same grey scale value. As test image you can use everything – from Olimex logo to Lena above.
        
        
#####issue14: Compute Pi to the maximal precision you can in relatively real time.
Tip: Use Leibniz formula and find way to work with very big numbers like hundreds/thousands of digits.
        

#####issue15: Unformatted C language text file and brackets
Make code which reads not formatted C language text file and format the brackets i.e. 
moves the closing bracket as same column as the corresponding opening bracket, ignoring the comments. 
If the brackets doesn’t match should issue error message.
        
        
#####issue16: Convert Infix Notation to Postfix Notation
Input string which is mathematical statement written in normal Infix Notation and convert it to Postfix Notation.


#####issue17: Skytales
Ancient Greeks and Spartans used Skytales to send encrypted messages, they wound on bar stripe then write on it, 
when the stripe is unwound the letters become shifted and you cant read the message again until you wound it on rod 
with same diameter. Write code which crypt and de-crypt message on Skytale, as input you can take message and diameter of the rod.
        

#####issue18: Minimal console editor to complement BAS-INT
BAS-INT is freeware tiny Basic interpreter with the bare minimum for BASIC scripting language. 
It works with external files only and is with Basic Stamp like syntax.
The Challenge today is to write minimal console editor which to complement BAS-INT and to perform some very basic commands:
  - List – list the program in memory with numbers
  - Delete N(-M) – deletes line N or N to M from memory
  - Insert N – inserts line on number N
  - Run – runs the BASIC program in memory (this code is already available)
If one wants to make it even more advanced he may make also the
  - Edit N – prints the content of line N and allow it to be edited
Remember this is console application and you have just serial in and serial out, no fancy graphics and windows in this editor.
        
        
#####issue19: Pattern match
Make function match() which takes as input input_string and pattern_string, the input strings may contain any ASCII codes.
There are two special codes for use in the pattern-string: ?-replaces 1 character and * – replaces any character(s).
The function should print all words from the input-string which match the pattern-string.
        words can be separated by any of these characters: ‘ ” . , : ;  
        If the input-string have this content “The big black cat jump over the window”

        if pattern-string is “b*” should print
            big
            black

        if pattern-string is “*c*” should print
            black
            cat

        if pattern-string is “?i*” should print
            big
            window
            
                        
#####issue20: Anagrams
An anagram is a type of word play, the result of rearranging the letters of a word or phrase to produce a new word or phrase, 
using all the original letters exactly once; for example 'orchestra' can be rearranged into 'carthorse'. 
Find all anagram words in text file, you can use as word source our well known: http://fiction.eserver.org/novels/alice_in_wonderland.html
        
 
#####issue21: Words Puzzle
        Aoccdrnig to a rscheearch at Cmabrigde Uinervtisy, it deosn’t mttaer in waht oredr the ltteers in a wrod are, 
        the olny iprmoetnt tihng is taht the frist and lsat ltteer be at the rghit pclae. The rset can be a toatl mses 
        and you can sitll raed it wouthit porbelm. Tihs is bcuseae the huamn mnid deos not raed ervey lteter by istlef, 
        but the wrod as a wlohe.

You can see original text here: http://www.mrc-cbu.cam.ac.uk/people/matt.davis/Cmabrigde/
Write code which takes as input normal text and shuffles the letters inside the words to make text like this one above. 
        
               
#####issue22: Plagiarism detector
Make code which compare two texts and output the % of similarities between the two texts i.e. if they have same words even
if the words are in different order. More advanced version may take care for synonyms.
 
 
#####issue23: Something small and evil
Invent something small and evil which to be almost invisible and to cause lot of troubles to catch like:
        #define struct union
        #define double float
        #define floor ceil
        #define true (__LINE__&42) !=42
        #define private public

       
#####issue24: Combinatorics - Integer Partitioning
Write code which calculate the number of ways you can express positive natural number N as sum of positive natural numbers.
        For N=1 we have 1 way;
        for N=3 we have 3 ways: 1+1+1, 1+2, 3;
        etc.        


#####issue25: Equal Travel Paths
If we have matrix with size M x N and two points A(xa,ya) and B(xb,yb), C obstacles which are entered with their coordinates
and length of path L, make code which:
  - displays all variants (if any) one can move from point A to point B by traveling via L cells;
  - you can step on one cell just once and only if the cell have no obstacle;
  - the valid moves are only up-down-left-right.
        
inputs: 
  - the matrix size M and N;
  - the points A(x,y) and B(x,y) coordinates;
  - the number of obstacles;
  - the obstacles C(x,y) coordinates;
  - the path length L.
                
                
#####issue26: Square
        Write code which check if four points make square.
        input data for squares:
        (0,0),(0,1),(1,1),(1,0)   - normal square
        (0,0),(2,1),(3,-1),(1,-2) - not aligned square
        (0,0),(1,1),(0,1),(1,0)   - different order of the points
        input data for non-squares:
        (0,0),(0,2),(3,2),(3,0) - rectangle
        (0,0),(3,4),(8,4),(5,0) - rhombus
        (0,0),(0,0),(1,1),(0,0) - three points are same
        (0,0),(0,0),(1,0),(0,1) - two points are same
        
        
        
#####issue27: AngryBird    
Write code which calculates the trajectory of Angry-bird with these input parameters: 
  - Angle
  - Initial Force
  - Bird Weight
  - Air resistance
  - Earth Gravity
  
If your tools allow animation great, otherwise even simply ascii art drawing is OK.
       
        
#####issue28: Sudoku
Make code which solves Sudoku in 3×3 configuration.<br>
Input:  enter the initial cells which are initialized with start numbers<br>
Check the input for correctness then print solution(s).
 
 
#####issue29: Make code which scrapes GitHub and extracts all developer’s e-mails.
Note: This is for educational purposes and not to be used for evil! 
  
        
#####issue30: Converter from decimal to roman numbers.


#####issue31: Run Length Encoding/Decoding
RLE/D is the simplest way to compress data http://en.wikipedia.org/wiki/Run-length_encoding
Implement RLE/D in shortest/simplest way possible using your favourite language.


#####issue32: PCB panelization
Let have N PCBs with rectangular form with size X Y. Make code which inputs the number of PCBs and their size Xn Yn and 
the minimal space between the PCB borders on the panel m in millimeters, then arrange the PCBs on panel with minimal area.
        
        
#####issue33: Infinite Output
Write the shortest possible code which will make infinite output.


#####issue34: POV LED display
Persistence of Vision (POV) is made with stripe of LEDs which rotates at 360 degree.
If we assume the stripe is with 100 LEDs you can make square “screen” with size approx 140×140 pixels.
Make code which converts 140×140 pixels picture to array of LED stripe values for each angle 0-360. 
When LED from the stripe are not at exact pixel positions the best way to set their value is to mediate the value 
depend on the closest pixel neighbors.
        

#####issue35: Maze
Maze with 10×10 cells have obstracles placed on random cells marked with the black. 
Make code which finds path which starts from cell (1,1) and moves through all Maze cells 
and returns back to cell(1,1) without stepping on same cell more than once.

        
#####issue36: NOKIA text message converter
Make code which takes string and convert it to button push sequence on NOKIA1100 phone keypad 
which will print same string. For instance: HELLO -> 44 33 555 555 666
         

#####issue37: Snake Retro Game
Make your own snake game! Do you remember the Nokia phones Snake game? You move the snake with 4 keys and it eats apples 
on the screen and gets bigger, collision with walls or snake body ends the game.
           

#####issue38: Center of mass
A picture is 100×100 pixels and have black object on white background. Make code which calculates the center of mass and display it.
        

#####issue39: CRC-16
Cyclic Redundancy Check is error detecting code used in serial devices to detect accidental errors in the input data.
Make code which calculates CRC-16.
        
        
        
#####issue40: Number approximation
Any positive integer number can be presented as 1 and several operations *3 and /2 discarding 
the result after the decimal point when dividing. For instance:
                         4 = 1 *3 *3 /2
                        12 = 1 *3 *3 /2 *3
Make code which enters positive integer N then present it with 1 *3 /2 equation.
         
                  
#####issue41: Speed typing test
Make code which displays text, then measures how fast and correct one would enter this test via the keyboard. 
You can display random text from online book or dictionary. It’s up to you how to make the user interface, 
make something funny and interesting.


        
            


