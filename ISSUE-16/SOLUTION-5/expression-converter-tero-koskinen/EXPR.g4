/*
 *
 * Olimex Weekend Programming Challenge Issue 16
 * Infix to Postfix converter 
 *
 * http://olimex.wordpress.com/2013/07/05/weekend-programming-challenge-issue-16-infix-to-postfix-converter/
 *
 * Copyright (c) 2013 Tero Koskinen <tero.koskinen@iki.fi>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

grammar EXPR;

options
{
    language = Java;
}

@header {package expr;}

expr: term termtail*;

termtail: addoperator term;

term: factor factortail*;

factortail: muloperator factor;

factor: number       # factorNUMBER
      | '(' expr ')' # factorEXPR
      ;

addoperator: PLUS | MINUS;

muloperator: MULT | DIV;

number: INT;

fragment DIGIT : '0'..'9' ;

INT   : ('-')?DIGIT+ ;

MINUS : '-' ;
MULT : '*' ;
DIV : '/' ;
PLUS : '+' ;

WS : ( ' ' | '\t' | '\r' | '\n') -> skip;

