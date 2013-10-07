;
; /* Copyright (c) 2013 Richard Y. Park */
;
;
; NOTE: 
;        use DrRacket (http://racket-lang.org)
;
; Usage: racket -b trajectory.rkt
;
; INPUT:  trajectory.rkt
; OUTPUT: trajectory.png


#lang racket
(require racket/math)
(require racket/draw)


(display "TRAJECTORY\n")

(define HEIGHT 500)
(define WIDTH 1500)
(define target (make-bitmap WIDTH HEIGHT))
(define dc (new bitmap-dc% [bitmap target]))

;; INITIAL VALUES
(define angle 45) ; degree
(define v-init 100.0)  ;; initial velocity
(define weight 0) ; weight has nothing to do with trajectory
(define airforce 0.0)     ; <- negative | zero | positive -> 
(define g -9.8000) ;; gravity
(define dt 0.01)   ;; delta time
(define t 0.0)       ;; time
(define vx 0.0)    ;; velocity x
(define vy 0.0)    ;; velocity y
(define xi 0.0)    ;; initial position x
(define yi 10.0)    ;; initial position y
(define x 0.0)     ;; position x
(define y 10.0)    ;; position y
(define ax airforce) ;; acceleration x
(define ay g)        ;; acceleration y


;; INITIAL VELOCITY
(define a (degrees->radians angle)) ;; conversion from degrees to radians
(displayln a)
(set! vx (* v-init (cos a)))
(set! vy (* v-init (sin a)))

(display "vx ")
(display vx)
(display ", vy ")
(displayln vy)

;; SUB-FUNCTIONS
(define (update-x x vx ax dt)
  (+ x (* vx dt) (/ (* ax (* dt dt)) 2)))
(define (update-y y vy ay dt)
  (+ y (* vy dt) (/ (* ay (* dt dt)) 2)))
(define (update-vx vx ax dt)
  (+ vx (* ax dt)))
(define (update-vy vy ay dt)
  (+ vy (* ay dt)))

;; MAIN-FUNCTION
(define (update t t-max dt x y vx vy ax ay)
  (if (<= y 0)
      0
      (when (<= t t-max)
        (display x)
        (display ", ")
        (display y)
        (display " : ")
        (display vy)
        (display ", ")
        (displayln vy)
        (define yy  (update-y y vy ay dt))
        (define vyy (update-vy vy ay dt))
        (define xx  (update-x x vx ax dt))
        (define vxx (update-vx vx ax dt))
        (send dc draw-line
              x (- HEIGHT  y)
              xx (- HEIGHT yy))
        (update (+ t dt) t-max dt xx yy vxx vyy ax ay))))



;; MAIN
(print (update t 100 dt x y vx vy ax ay)) 
;; SAVE
(send target save-file "trajectory.png" 'png)
 
