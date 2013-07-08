; Olimex Weekend Programming Challenge #16 - July 2013
; Author: wiml
; Language: Scheme
;
; This was written in CHICKEN Scheme, but should run
; in any scheme supporting SRFI 6, 23, and 28.
;
; This program is placed in the public domain.
; It may be used by anyone for any purpose.

; Parse an infix expr to an AST
(define (parse-infix s)
  ; Helpers
  (define (endparen? ch) (eqv? #\) ch))
  (define (fail msg saw)
    (error (format "Saw '~A' while looking for ~A" saw msg)))

  ; Operators & Precedence
  (define (char-oper? ch)
    (or (char=? #\+ ch) (char=? #\- ch)
        (char=? #\/ ch) (char=? #\* ch)))
  (define (oper-prec oper)
    (case oper
      ((#\+ #\-) 1)
      ((#\* #\/) 2)))

  ; Parse a term (number, or parenthesized subexpression)
  (define (parse-term)
    (let ((lookahead (read-char s)))
      (cond
       ((char=? #\( lookahead) (parse-expr endparen?))
       ((or (char=? #\- lookahead) (char-numeric? lookahead))
        (let parse-number ((sofar (list lookahead))
                           (lookahead (peek-char s)))
          (if (and (not (eof-object? lookahead)) (char-numeric? lookahead))
              (parse-number (cons (read-char s) sofar) (peek-char s))
              (string->number (list->string (reverse sofar))))))
       ((char-whitespace? lookahead) (parse-term))
       (#t (fail "number or subexpression" lookahead)))))

  ; Parse an expression terminated by ')' or EOF
  (define (parse-expr end?)
    ; Helper to parse portion of expression with operators of higher precedence than lprec
    (define (parse-op-expr-prec> lterm lprec)
      (let ((ch (peek-char s)))
        (cond
         ((not (char? ch)) lterm)
         ((char-whitespace? ch) (begin (read-char s)
                                       (parse-op-expr-prec> lterm lprec)))
         ((and (char-oper? ch) (> (oper-prec ch) lprec))
          (let ((oper (read-char s)))
            (parse-op-expr-prec>
             (list oper lterm (parse-op-expr-prec> (parse-term) (oper-prec oper)))
             lprec)))
         (#t lterm))))
    (let ((expr (parse-op-expr-prec> (parse-term) 0))
          (ch (read-char s)))
      (if (end? ch)
          expr
          (fail "end of expression" ch))))
  (parse-expr eof-object?))

; Write AST in postfix syntax to current-output-port
(define (unparse-postfix e)
  (if (pair? e)
      (begin
        (unparse-postfix (cadr e))    (display #\space)
        (unparse-postfix (caddr e))   (display #\space)
        (display (car e)))
      (display e)))

; Display some examples
(define (showoff s)
  (display s)
  (display " --> ")
  (let ((parsed (parse-infix (open-input-string s))))
    (unparse-postfix parsed)
    (newline)
    parsed))

(for-each showoff 
          '("1"
            "1+2"
            "(10 + 20) / (30 - 40)"
            "1+2*3+4"
            "1*2+3*4"
            "1+-1"
            "1-1"))

