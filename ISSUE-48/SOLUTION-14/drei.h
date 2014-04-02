//Maciej Drozd 2014
//for Olimex Challenge
#ifndef DREI_H
#define DREI_H

#include <stdio.h>
#define DREI_MSG_SIZE 40

typedef struct
{
int x;
int y;
} point2d_t;


// Function arguments:
// a, b, c - simple structs of integer pair.
// answer - pointer to at least DREI_MSG_SIZE chars
// answer is returned answer.
void arePointsCW(point2d_t a, point2d_t b, point2d_t c, char *answer);

#endif
