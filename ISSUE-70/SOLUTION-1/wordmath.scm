(import (srfi :1) (srfi :26))

;; identity function
(define (id x) x)

;; Association list of words and lambdas
(define words  
  `((zero      . ,id)
    (one       . ,(cut + 1 <>))
    (two       . ,(cut + 2 <>))
    (three     . ,(cut + 3 <>))
    (four      . ,(cut + 4 <>))
    (five      . ,(cut + 5 <>))
    (six       . ,(cut + 6 <>))
    (seven     . ,(cut + 7 <>))
    (eight     . ,(cut + 8 <>))
    (nine      . ,(cut + 9 <>))
    (ten       . ,(cut + 10 <>))
    (eleven    . ,(cut + 11 <>))
    (twelve    . ,(cut + 12 <>))
    (thirteen  . ,(cut + 13 <>))
    (fourteen  . ,(cut + 14 <>))
    (fifteen   . ,(cut + 15 <>))
    (sixteen   . ,(cut + 16 <>))
    (seventeen . ,(cut + 17 <>))
    (eighteen  . ,(cut + 18 <>))
    (nineteen  . ,(cut + 19 <>))
    (twenty    . ,(cut + 20 <>))
    (thirty    . ,(cut + 30 <>))
    (fourty    . ,(cut + 40 <>))
    (fifty     . ,(cut + 50 <>))
    (sixty     . ,(cut + 60 <>))
    (seventy   . ,(cut + 70 <>))
    (eighty    . ,(cut + 80 <>))
    (ninety    . ,(cut + 90 <>))
    (hundred   . ,(cut * 100 <>))
    (thousand  . ,(cut * 1000 <> ))
    (million   . ,(cut * 1000000 <> ))
    (billion   . ,(cut * 1000000000 <> ))
    (and       . ,id) 
    )
  )

;; Association list of operators
(define operators
  `((plus . ,+) (minus . ,-) (multiply . ,*) (divide . ,/))) 

;; accumulate a word onto a number
(define (acc v word)
  (cond
   [(assoc word words) => (lambda (x) ((cdr x) v))]
   [else v]))

;; Here we do the maths.  A truly horrible hack.
(define (do-math port)
  (let loop ([ops `(,+)] [v 0] [values '()])
    ;; Get the next word from the input stream.  This tokenizes neatly, but we couldn't use
    ;; this if we expected to use bracketed expressions; it uses the scheme reader which, in turn,
    ;; uses brackets to delimit lists
    (let ([word (get-datum port)])
      (cond
       ;; If we have end-of-file, we need to do the actual maths
       [(eof-object? word)
        ;; fold over the lists of operators and values, applying one to the other
        (display (fold-right (lambda (o v a)
                               (o a v))
                             0 ops (cons v values)))
        (newline)]
       ;; If we have an operator, push current value and operator onto stacks, and recurse
       [(assoc word operators) => (lambda (op) (loop (cons (cdr op) ops) 0 (cons v values)))]
       [else (loop ops (acc v word) values)]))))
  

;; Do maths on a per-line basis.
(define (main)
  (let ([line (get-line (current-input-port))])
    (if (not (eof-object? line))
        (begin 
          (do-math (open-string-input-port line))
          (main)))))
      
      
(main)
