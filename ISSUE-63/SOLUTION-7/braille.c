/*
 * submission from teqster@gmail.com for Olimex Weekend Programming Challenge #63 - Braille encoder
 * compile me with
 *  $ gcc -g -Wall -o braille braille.c
 */
#include <ctype.h>
#include <stdio.h>
#include <string.h>

struct braille_table_s {
  unsigned short map[26];
};

// returns character index relative to 'a'
inline unsigned short
a(unsigned short c)
{
  return c-'a';
}

// fills braille table (see http://en.wikipedia.org/wiki/Braille#Derivation)
void
gen_table(struct braille_table_s *t)
{
 unsigned short init_t[] = {
    0b10000000, 0b10100000, 0b11000000, 0b11010000, 0b10010000, 0b11100000, 0b11110000, 0b10110000, 0b01100000, 0b0111000
  };
  unsigned short i = 0;
  for (i='a'; i<'k'; i++)
  {
    t->map[a(i)] = init_t[a(i)];
    t->map[a(i) + a('k')] = t->map[a(i)] | 0b00001000;
    if (a(i) + a('u') <= a('z'))
      t->map[a(i) + a('u')] = t->map[a(i) + a('k')] | 0b00000100;
  }
  t->map[a('w')] = 0b01110100;
}

// returns braille representation for character
inline unsigned short
b(struct braille_table_s *t, char c)
{
  c = tolower(c);
  if (c >= '1' && c <= '9')
    c -= '1' - 'a';
  else if (c == '0')
    c -= '0' - 'a';
  return t->map[a(c)];
}

// copies embossing string into buffer and returns a pointer to it
char *
pretty(struct braille_table_s *t, char *buf, unsigned short i)
{
  strcpy(buf, "* * ");
  if ((i & 2) == 0)
    buf[0] = '.';
  if ((i & 1) == 0)
    buf[2] = '.';
  return buf;
}

// prints a string in braille
void
braille_print(struct braille_table_s *t, char *s)
{
  char *c;
  unsigned short row;
  char buf[10] = {};
  for(row = 0; row < 3; row++)
  {
    for(c = s; *c != 0; c++)
    {
      printf("%s", pretty(t, buf, (b(t, *c) >> (2 * (2 - row) + 2)) & 0b11));
      
    }
    printf("\n");
  }
}

int
main(int argc, char *argv[])
{
  struct braille_table_s table;
  gen_table(&table);
  braille_print(&table, "helloworld");
  return 0;
}
