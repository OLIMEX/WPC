/*
 * Infix to postfix notation conversion using shunting-yard algorithm.
 * https://en.wikipedia.org/wiki/Shunting-yard_algorithm
 */

/*
Copyright (c) 2013, Stefan Petersen, Ciellt AB (spe@ciellt.se)
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Tokens that string is parsed down to.
 */
enum tokens {
    TOKEN_NONE,
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULT,
    TOKEN_DIV,
    TOKEN_LEFTP,
    TOKEN_RIGHTP,
};

/*
 * Conversion strings from tokens.
 */
const static char token2ascii[] = "  +-*/()";
const static char token2prec[]  = "  223311";

/*
 * Stack and stack operations.
 */
#define STACK_SIZE 16
static enum tokens stack[STACK_SIZE];
static int stack_ptr = 0;

static int
push(enum tokens token)
{
    if (stack_ptr > STACK_SIZE) {
	return -1;
    }

    stack[stack_ptr++] = token;

    return 0;
} /* push */


static enum tokens
pop(void)
{
    if (stack_ptr == 0) {
	return TOKEN_NONE;
    }

    return stack[--stack_ptr];
} /* pop */

static enum tokens
top_of_stack(void)
{
    if (stack_ptr == 0) {
	return TOKEN_NONE;
    }

    return stack[stack_ptr];
} /* top_of_stack */


/*
 * Determine precedence of token and decide wheter to print it
 * or push it onto the stack.
 */
static void
push_or_print(enum tokens token)
{
    if (token2prec[top_of_stack()] > token2prec[token]) {
	printf("%c ", pop());
    } else {
	push(token);
    }
} /* push_or_print */


int
main(int argc, char *argv[])
{
    int i = 0;
    int number = 0;
    enum tokens token = TOKEN_NONE;

    if (argc != 2) {
	fprintf(stderr, "Usage: %s \"<infix string>\"\n", argv[0]);
	exit(0);
    }

    /*
     * Loop thru string and parse every letter in the string
     */
    for (i = 0; i < strlen(argv[1]); i++) {
	switch (argv[1][i]) {
	case ' ':
	    break;
	case '+':
	    if (token == TOKEN_NUMBER) {
		printf("%d ", number);
		number = 0;
	    }
	    push_or_print(TOKEN_PLUS);
	    break;
	case '-':
	    if (token == TOKEN_NUMBER) {
		printf("%d ", number);
		number = 0;
	    }
	    push_or_print(TOKEN_MINUS);
	    break;
	case '*':
	    if (token == TOKEN_NUMBER) {
		printf("%d ", number);
		number = 0;
	    }
	    push_or_print(TOKEN_MULT);
	    break;
	case '/':
	    if (token == TOKEN_NUMBER) {
		printf("%d ", number);
		number = 0;
	    }
	    push_or_print(TOKEN_DIV);
	    break;
	case '(': /* Parenthesis requires special attention */
	    if (token == TOKEN_NUMBER) {
		printf("%d ", number);
		number = 0;
	    }
	    token = TOKEN_LEFTP;
	    push(token);
	    break;
	case ')':
	    if (token == TOKEN_NUMBER) {
		printf("%d ", number);
		number = 0;
	    }
	    while ((token = pop()) != TOKEN_LEFTP) {
		if (token == TOKEN_NONE) {
		    fflush(stdout);
		    fprintf(stderr, "Parenthesis error\n");
		    exit(0);
		}
		printf("%c ", token2ascii[token]);
	    }
	    break;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	    token = TOKEN_NUMBER;
	    number = number * 10 + (argv[1][i] - '0');
	    break;
	default:
	    fprintf(stderr, "Unknown character detected:%c[%d]\n",
		    number, number);
	    number = 0;
	}
    }

    if (token == TOKEN_NUMBER) {
	printf("%d ", number);
	number = 0;
    }

    while ((token = pop()) != TOKEN_NONE) {
	printf("%c ", token2ascii[token]);
    }

    printf("\n");

    return 0;
} /* main */
