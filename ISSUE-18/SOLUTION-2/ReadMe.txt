for compile: gcc -o basic basic.c
for running: ./basic x.bas

note: testing only under linux.
Add command : QUIT , RUN , LIST , INSERT , DELETE ( capital letter only )

Journal ( screen ) from  test.


todorp@dantooine:~/test/tourney/basic$ ./basic x.bas

todorp@dantooine:~/test/tourney/basic$ ./basic x.bas

:LIST
1: print "1234567890. 1 "
2: print "1234567890. 2 "
3: I=5
4: print "1234567890. 3 "
5: print "1234567890. 4 "
6: end

:INSERT 1

:LIST
1:
2: print "1234567890. 1 "
3: print "1234567890. 2 "
4: I=5
5: print "1234567890. 3 "
6: print "1234567890. 4 "
7: end

:INSERT 9

:LIST
1:
2: print "1234567890. 1 "
3: print "1234567890. 2 "
4: I=5
5: print "1234567890. 3 "
6: print "1234567890. 4 "
7: end
8:
9:

:INSERT 4

:LIST
1:
2: print "1234567890. 1 "
3: print "1234567890. 2 "
4:
5: I=5
6: print "1234567890. 3 "
7: print "1234567890. 4 "
8: end
9:
10:

:DELETE 1

:LIST
1: print "1234567890. 1 "
2: print "1234567890. 2 "
3:
4: I=5
5: print "1234567890. 3 "
6: print "1234567890. 4 "
7: end
8:

:DLETE 3-8
unrecognized command

:DELETE 3-8

:LIST
1: print "1234567890. 1 "
2: print "1234567890. 2 "

:DLETE 2
unrecognized command

:DELETE 2

:LIST
1: print "1234567890. 1 "

:INSERT 2

:LIST
1: print "1234567890. 1 "
2:

:RUN
1234567890. 1 syntax error
todorp@dantooine:~/test/tourney/basic$
