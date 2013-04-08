Olimex - WPC#3 - Solution in PureBasic by Joh.Lummel.

Happy Monday!

This time, i go back to my programming roots to get a solution in time. 
WPC#2 in PROLOG is still on my desk to get the latest quirks out of the code... :-))

So... i've included the source, a compiled console version for WIN-XP and a compiled 
console version for linux which may run. Linux is - like english - not my best side.

The compiled linux-version was made under !#-linux on my netbook (-> http://crunchbang.org/) 
and the demoversion of purebasic 5.11 without any problem.

To get the free 800 lines demo version (Win/MacOS X/Linux), please go to: 
http://www.purebasic.com/download.php
If you compile it for yourself, please change the format to CONSOLE at:

 | Compiler | Compiler Options |  Executable Format | 
 

Open question during programming was:
?? how to handle duplicate identical strings
-> inform user and ignore them

?? how to handle duplicate strings if they had different case (hello <-> Hello)
-> inform user, change doOnlyLCaseTest to #False for case sensitive testing
-> can be switched off again with !s

?? empty list
-> ask user and exit

I hope, this match the "competition-rules".

Greetings to your crew and keep on doing the WPC as long all have fun with it,
good luck in your business and always fun with your job!!!

with Greetings from Germany

Johannes Lummel

PS:
Sorry for my english... i hope you can understand it ;-)
