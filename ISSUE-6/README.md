ISSUE#6 - PCB CNC drill machine path optimizer
===
Problem:

CNC drill machine drills holes in Printed Circuit Boards (PCB) with maximum board size (i.e. maximal coordinates of the drill holes) 999.999 x 999.999 mm

The machine head have task to drill between 1 and 2000 holes on the PCB.

To drill the holes the machine takes input file in the following format:
- first row define drill size: Txx where xx is the drill size 01 = 0.1 mm , 09 = 0.9 mm, 12 = 1.2 mm etc etc up to 99 = 9.9 mm
- next rows define X Y coordinates: XaaaaaaYaaaaaa where aaaaaa is the coordinates with fixed point 3.3 arithmetic i.e. 001550 = 1.55 mm

Your code should first do DRC check:
- if there are drill holes with duplicated coordinates and remove the duplicate
- if there are overlapping holes, if such overlapping holes are found they have to be reported and code to stop
– if hole extends behind board dimensions error should be reported i.e. center of the hole is inside the board area but the hole radius exted the hole behind the board border

Then your code should sort the X-Y lines in such order that the machine head to make the optimal (shortest) path which starts from 0,0 and ends to 0,0 going through all XY drill positions.

Test input file called drill.txt is on GitHub: https://github.com/OLIMEX/WPC/tree/master/ISSUE-6


Solutions:
==

1. Miller Wang, Visual Basic 

2. Antal Koos, Python 

3. Piotr Gapinski, AWK