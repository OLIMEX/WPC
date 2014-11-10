/*
   *
   * Weekend Programming Challenge – Week #68 Text Formatting
   *
   * Input text and width, then format the text in this width to be with no spaces at the end of the line.
   *
   *  Created: 09.11.2014
   *  Author:  michael koch
   *	email:	 chefkoch.michael@arcor.de
   *
   */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFERSIZE 256

// Sample text for your convenience inlined here... "WITH" sets the disired maximum line width.
#define WIDTH 45
char testtext[] = "\n Alice was beginning to get very tired of sitting by her sister on the bank, and of having nothing to do:"
                  "once or twice she had peeped into the book her sister was reading, but it had no pictures or conversations in it,"
                  "\'and what is the use of a book,\' thought Alice \'without pictures or conversations?\' So she was considering in her own "
                  "mind (as well as she could, for the hot day made her feel very sleepy and stupid), whether the pleasure of making a daisy-chain "
                  "would be worth the trouble of getting up and picking the daisies, when suddenly a White Rabbit with pink eyes ran close by her."
                  "There was nothing so very remarkable in that; nor did Alice think it so very much out of the way to hear the Rabbit say "
                  "to itself, \'Oh dear! Oh dear! I shall be late!\' (when she thought it over afterwards, it occurred to her that she ought "
                  "to have wondered at this, but at the time it all seemed quite natural); but when the Rabbit actually took a watch out of its "
                  "waistcoat-pocket, and looked at it, and then hurried on, Alice started to her feet, for it flashed across her mind that she had "
                  "never before seen a rabbit with either a waistcoat-pocket, or a watch to take out of it, and burning with curiosity, she ran "
                  "across the field after it, and fortunately was just in time to see it pop down a large rabbit-hole under the hedge.";


/* ############################################################### */
int getText( char *s ) {
  // Let user enter some text
  printf("\nPlease enter your text:\n");
  scanf("%s",s);
  return( strlen(s) );
  }

/* ############################################################### */
int getWidth( int *w ) {
  // Ask user about wished line length
  printf("\nPlease enter line length:\n");
  scanf("%i",w);
  return( *w );
  }

/* ############################################################### */
int getToken( char *str) {
  // Find length n of first token in string. Tokens are separeted by
  // NewLines or Space characters.
  // Consider to use 'strtok' and 'strlen' from string.h
  int i;
  i=1;
  while (! ((*str == ' ') || (*str == 0x0d) || (*str == 0x00))) {
    i++;
    str++;
    }
  return(i);
  }

/* ############################################################### */
void insertSpaces( char *line, int lineLength, int width) {
  // Fill string from left to right with spaces
  int spaces;
  char *p;

  if (width == lineLength)
    return;

  for (p=line, spaces = 0; (*p && !spaces); p++ )
    spaces = (*p == ' ');

  if (!spaces)
    return;

  spaces = width -lineLength;

  p = line +1;
  while (spaces) {

    if (!*(p+2))
      p = line +1;

    if (*p == ' ') {
      while ( *p == ' ') p++;
      memmove((p+1), p, lineLength);
      *p = ' ';
      spaces--;
      p++;
      lineLength++;
      }
    p++;
    }
  }

/* ############################################################### */
void processText(char *s, int w) {
  char line[BUFFERSIZE];
  int n, lineLength;

  *line = 0;
  lineLength = 0;

  while (*s) {

    n = getToken(s);

    if (n > w) {
      // Abbort: length of line is to small for this token/word.
      printf("\n\nWord\'s length =%i is longer than line width at %s. Program stopped.", n, s);
      exit(EXIT_FAILURE);
      }
    else if (!n)
      // End-of-data
      break;

    if ((lineLength +n) > w) {
      // Exceeds current line length plus token length allowed line width?
      *(line+lineLength) = 0;
      insertSpaces(line,lineLength,w);
      printf("\n%s", line);

      memcpy(line, s, n);
      s += n;
      lineLength = n;
      }
    else {
      // normal token processing: token fits into recent line
      memcpy(line+lineLength, s, n);
      s += n;
      lineLength += n;
      }
    }

  *(line+lineLength) = 0;
  insertSpaces(line,lineLength,w);
  printf("\n%s", line);
  }


/* ############################################################### */
int main (int argc, char **argv) {

  //  if (!( getText(t) && getWidth(&w) ))
  //    return(EXIT_FAILURE);


  processText(testtext, WIDTH);
  return(EXIT_SUCCESS);
  }


