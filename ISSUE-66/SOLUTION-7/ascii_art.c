/*
 *
 *	Weekend Programming Challenge – Week #66 Christmas Tree ASCII art
 *
 *	ascii_art.c
 *
 *  Created on: 27.09.2014
 *  Author: michael koch
 *	email:	chefkoch.michael@arcor.de
 *
 */

#include <stdlib.h>
#include <stdio.h>

#define LINES 15
#define OFFSET 20

typedef struct {
    int ofs;
    char *txt;
    } picT;


picT pic[LINES] = {
        { 10,"."},
        { 8, "_/.\\_"},
        { 7, "\\     /"},
        { 7, "/_' '_\\"},
        { 8, "/-* \\"},
        { 7, "/-'_- \\"},
        { 6, "/ *(_) '\\"},
        { 5, "/* .- '  .\\"},
        { 4, "/._' * ._'  \\"},
        { 3, "/ (_).- (_).-'\\"},
        { 2, "/* .-_'   .-_ * \\"},
        { 1, "/-   (_).-' (_).- \\"},
        { 0, " –-----------------"},
        { 7, "[______]"},
        { 8, "\\____/       1db"}
    };

int main(int argc, char **argv) {
    int i, j;
    for (i=0; i< LINES; i++) {
        for (j=0; j<= (pic[i].ofs +OFFSET); j++)
            printf(" ");
        printf("%s\n",pic[i].txt);
        }
    printf("\n\n");
    return(0);
    }
