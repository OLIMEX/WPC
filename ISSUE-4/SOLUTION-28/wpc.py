import sys
import string 

text = sys.stdin.read().lower()

""" clear text from punctuation characters & digits """
separators = string.punctuation+string.digits
text = text.translate(string.maketrans(separators, 
                len(separators) * " "))

""" sort all unique words, longer first """
words = sorted(set(text.split()), key = len, reverse = True)

""" find longest isogram """
for n in range(len(words)):
    l = list(words[n])
    if len(l) == len(set(l)):
      print words[n]
      break 
