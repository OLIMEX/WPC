/*
 * OLIMEX WEEKEND PROGRAMMING CHALLENGE ISSUE #4
 * author: Hanspeter <ventosus> Portner
 * language: (F)lex, C
 * filename: isogram.l
 * compilation:
 *  >> flex -o isogram.c isogram.l
 *  >> gcc -o isogram isogram.c
 * usage:
 *  >> ./isogram < alice.txt
 */

%{
#include <stdio.h>
#include <ctype.h>
#include <string.h>

size_t count = 0;
size_t max_len = 0;
char *max_isogram = NULL;

size_t
isogram(char *word)
{
	size_t i, j;
	size_t len = strlen(word);

	for (i=0; i<len-1; i++)
		for (j=i+1; j<len; j++)
			if (word[i] == word[j]) // check for a repeating character in word
				return 0; // immediatley return when a repeating character has been found

	return len; // this is a isogram, return its length
}
%}

%option noyywrap

%%
[[:alpha:]]+	{ // scan for simple ASCII words
	size_t len;
	char *p;

	for (p=yytext; *p; ++p) *p = tolower(*p); // convert to lowercase

	if (strlen(yytext) > max_len) // only consider potential candidate words (long enough...)
		if ( (len = isogram(yytext) ) > max_len ) // check for isogram and its length
		{
			free(max_isogram); // free previous longest isogram
			max_len = len; // set max_len
			max_isogram = strdup(yytext); // store longest isogram
		}
}

[[:blank:]]+	// eat up whitespace

[[:punct:]]+	// eat up punctuation

[\n\r] 				// eat up newlines

.							// ignore all the rest
%%

int
main(int argc, char **argv)
{
  yylex(); // parse stdin

	if (max_isogram)	printf("longest isogram: %s (%i)\n", max_isogram, max_len);
	else							printf("no isogram found\n");

	return 0;
}
