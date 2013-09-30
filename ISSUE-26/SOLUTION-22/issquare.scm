; Olimex Weekend Programming Challenge #26 - September 2013
; Author: wiml
; Language: Scheme
;
; This was written in CHICKEN Scheme, but should run
; in most Schemes.
;
; This program is placed in the public domain.
; It may be used by anyone for any purpose.

(require-extension (srfi 1 11 28))

(define (square a) (* a a))

;; Points are specified as lists, with the X-coordinate in the car,
;; and the Y-coordinate in the cadr.
;; Vectors are represented the same way as points.
(define (pt-x p) (the number (car p)))
(define (pt-y p) (the number (cadr p)))
(define (square-dist a b)
  (fold (lambda (a- b- d) (+ d (square (- a- b-)))) 0 a b))
(define (dot a b)
  (fold (lambda (a- b- d) (+ d (* a- b-))) 0 a b))

(define (order-pts-clockwise pts)
  ; We need the points to be in a consistent order. 
  ; We do this by choosing a point inside the square and then
  ; sorting the vertices by their angle from that point.
  ; The centroid is an easy point to choose.

  (define (centroid pts)
    (define (sum-f f pts)
      (fold (lambda (p n) (+ n (f p))) 0 pts))
    (let ((npoints (length pts)))
      (list
       (/ (sum-f pt-x pts) npoints)
       (/ (sum-f pt-y pts) npoints))))

  (define (sort-by-angle from-pt pts)
    (map cdr
         (sort! (map (lambda (pt)
                       (cons (atan (- (pt-y pt) (pt-y from-pt))
                                   (- (pt-x pt) (pt-x from-pt)))
                             pt))
                     pts)
                (lambda (a b) (> (car a) (car b))))))
  
  (sort-by-angle (centroid pts) pts))

(define (estimate-side1 pts)
  ; If the points are a square, then they can all be expressed
  ; as the first point plus various linear transformations of a
  ; vector describing one side of the square. Here we compute that
  ; vector. We should probably do a least-squares thing, but we
  ; just average the numbers.

  (define (reconstruct vec mtx)
    (map (lambda (prow)
           (map (lambda (pcoord) (dot vec pcoord)) prow))
         mtx))

  (define (total-error pts0 pts1)
    (fold (lambda (a b p) (+ p (square-dist a b))) 0 pts0 pts1))

  (let* ((x0 (pt-x (car pts)))
         (y0 (pt-y (car pts)))
         (deltas (map
                  (lambda (p) (list (- (pt-x p) x0) (- (pt-y p) y0)))
                  (cdr pts)))

         ; Compute the components of the vector
         (vx (/ (+ (pt-x (list-ref deltas 0))
                   (- 0 (pt-y (list-ref deltas 2))))
                2))
         (vy (/ (+ (pt-y (list-ref deltas 0))
                   (pt-x (list-ref deltas 2)))
             2))
         (v (list vx vy))

         ; Compute the sum-squared-error
         (recon (reconstruct v
                             '(((1 0) ( 0 1))
                               ((1 1) (-1 1))
                               ((0 1) (-1 0)))))
         (err (total-error deltas recon)))
          
    (display (format " Values to fit: ~a~% Estimates: ~a ~a ~% Reconstruction: ~a~% Error: ~a~%" deltas vx vy recon err))

    (values v err)))

(for-each (lambda (p)
            (display (format "Points: ~a~%" p))
            (let ((sp (order-pts-clockwise p)))
              (display (format " Sorted points: ~a~%" sp))
              (let-values (((vec err) (estimate-side1 sp)))
                (display
                 (if (= err 0)
                    (format " This is a square! With side length=~a and angle=~a deg.~%~%" (sqrt (dot vec vec)) (* (/ 180 3.1415) (atan (pt-y vec) (pt-x vec))))
                    (format " This is NOT a square.~%~%"))))))
          '(
            ((0 0) (0 1) (1 1) (1 0))   ; normal square
            ((0 0) (2 1) (3 -1) (1 -2)) ; not aligned square
            ((0 0) (1 1) (0 1) (1 0))   ; different order of the points
            ((0 0) (0 2) (3 2) (3 0)) ; rectangle
            ((0 0) (3 4) (8 4) (5 0)) ; rhombus
            ((0 0) (0 0) (1 1) (0 0)) ; three points are same
            ((0 0) (0 0) (1 0) (0 1)) ; two points are same
            ))
