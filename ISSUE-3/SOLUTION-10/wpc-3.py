import sys
import explode

unique_tokens = dict()
duplicate_tokens = dict()

all_lines = dict()   
line = sys.stdin.readline()[:-1]

while line:
    tokens = explode.explode(line.lower())
            
    for token in tokens:
       if token not in duplicate_tokens:
        if token in unique_tokens:
          del unique_tokens[token]
          duplicate_tokens[token] = 1
        else:
          unique_tokens[token] = line                 
          
    line = sys.stdin.readline()[:-1]    

""" Find shortest unique token """    
for (token, line) in unique_tokens.iteritems():
  if line in all_lines:
    if all_lines[line][0] > len(token):
      all_lines[line] = (len(token), token)
  else:
      all_lines[line] = (len(token), token)

""" Print results """
for (line, value) in  all_lines.iteritems():
  print "%s -> %s" % (line, value[1])

