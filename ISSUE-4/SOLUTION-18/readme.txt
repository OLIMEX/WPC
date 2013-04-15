Hi :)

I randomly chanced upon your prog.challenge while googling for openEEG :) -
and (for some reason or other) thought it'd be neat to actually have a
short script like this ready for future use. Because of this usage
constraint, its input/output is very simplistic: it reads text from the
standard input, and prints out the longest isograms (as there may be more
than one 'longest' (in terms of word length) one) sorted alphabetically and
separated by spaces.

So the usage is simply

  $ chmod +x isograms.py
  $ cat my_awesome_poem.txt | ./isograms.py

Or, to parse Alice in Wonderland (from Project Gutenberg, ascii text file
online):

  $ curl -s http://www.gutenberg.org/files/28885/28885.txt | ./isograms.py

Tested (only) on Python 2.7.1.

Also note that the program is rather negligent towards nuances involved in
dealing with hyphenated words. e.g. in Carroll's "Wonderland", there's a
word, "Jack-in-the-box" - should it be treated as four separate words? do
hyphens count towards word length (I say, no)? My (a few lines for a)
script is truly a very lazy one in that regard.

Why it's a neat solution: it's short (the separate function definition is
only for readability sake and could be included in the second filter()), &
it serves my purposes (a simple unixy tool which does one thing and works
with stdin/stdout) ;)

(I've also included an alternative solution (because I was procrastinating
and felt like it - it may be of more use for windoze users (if any of them
feel like writing poems and observing their creative / versatile vocabulary
abilities;), 'alt_isograms.py' (which may be disregarded) - it takes a URI
as a command line argument, which may be a filename or a URL (in which case
it has to start with 'http'). If no cmdline argument is provided, it
defaults to the Gutenberg Alice text URL. It also prints a bit more info.)

cheerio
Kostas.
