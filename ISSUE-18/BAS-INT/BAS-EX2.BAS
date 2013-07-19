

PRINT "This program demonstrates nested GOSUBs."
INPUT "enter a number: ", I
GOSUB 100

END

100 FOR T = 1 TO I
  X = X + I
  GOSUB 150
NEXT
RETURN

150 PRINT X;
    RETURN


