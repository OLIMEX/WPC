/*
 * wpc3.c
 *
 *  Created on: 06-04-2013
 *      Author: Mateusz Klatecki
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * @brief strndup - returns a pointer to a new string which is a duplicate of the string s, but only copies at most n characters
 * @param s - input string
 * @param n - no of chars
 * @return pointer to a new string
 */
char * strndup(const char *s, size_t n) {
    size_t len = strnlen(s, n);
    char *newstr = malloc(len + 1);

    if (newstr == NULL )
        return NULL ;

    newstr[len] = '\0';
    return memcpy(newstr, s, len);
}

/**
 * @brief strtolower - convert uppercase letter to lowercase
 * @param dest  - destination
 * @param src - source
 * @return pointer to destination
 */
char *strtolower(char *dest, const char *src) {
    char *d = dest;
    while (*src)
        *d++ = tolower(*src++);
    *d = 0;
    return dest;
}

int main(void) {
    unsigned int i, j, n, m;
    unsigned int N;
    char **strings_lower;

    char *strings[] = {
        "A13-OLinuXino",
        "iMX233-OLinuXino",
        "MOD-PULSE",
        "MOD-IO",
        //"new MOD-IO"
    };

    N = sizeof(strings) / sizeof(char*);
    //convert all strings to lowercase
    strings_lower = malloc(N * sizeof(char*));
    for (i = 0; i < N; i++) {
        strings_lower[i] = malloc(strlen(strings[i]) + 1);
        strtolower(strings_lower[i], strings[i]);
    }

    //iterate over all strings
    for (n = 0; n < N; n++) {
        char found = 0;
        //sub string len
        for (j = 1; j <= strlen(strings_lower[n]); j++) {
            //substring start
            for (i = 0; i + j <= strlen(strings_lower[n]); i++) {

                //get substring
                char *test = strndup(strings_lower[n] + i, j);

                found = 0;

                //check if is unique
                for (m = 0; m < N; m++) {
                    //don't check this same string
                    if (m != n) {
                        char *x = strstr(strings_lower[m], test);
                        if (x != NULL ) {
                            //isn't unique
                            found = 1;
                            break;
                        }
                    }
                }

                //print answer if is unique
                if (found == 0) {
                    printf("%s -> %s\n", strings[n], test);
                }

                //free memory
                free(test);

                if (found == 0) {
                    break;
                }
            }
            if (found == 0) {
                break;
            }
        }

        //string isn't unique
        if (found == 1) {
            printf("%s -> isn't unique\n", strings[n]);
        }
    }

    //free memory
    for (i = 0; i < N; i++) {
        free(strings_lower[i]);
    }
    free(strings_lower);

    return 0;
}

