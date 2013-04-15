Hello.

This time solution is written in Rebol language designed by Carl Sassenrath.

http://en.wikipedia.org/wiki/REBOL
http://www.rebol.com
http://www.rebol.com/download-core.html

Rebol/Core interpreter is only 300kb binary file (no install is needed).
Setup procedure:
- run rebol-core-278-3-1.exe (or download & run any other version of
Rebol/Core or Rebol/View)
- at command prompt ">>" type: do %olimex.r
- to end session and close interpreter type: quit

Script reads text from website, removes html tags and entities and
searches for longest isogram (word consist of unique ASCII letters, '
and - chars). This is a little unfair since Rebol has built-in
unique-function, but this functions and powerful parse-function are
good tools for this task.

Hope I understand challenge correctly ;)

Piotr.
