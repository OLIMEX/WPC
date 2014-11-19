;;;some sort of Common Lisp implementation of the levenshtein distance
(defun levenshtein ( a b )
  ;some useful indices
  (defvar length-a)
  (defvar length-b)
  (setf length-a (+ (length a) 1 ))
  (setf length-b (+ (length b) 1 ))
  ;the matrix needed for computing the values
  (defvar value-matrix nil)
  (setf value-matrix (make-array (list length-a length-b) :initial-element 0))
  ;initial values
  (do ((i 1 (1+ i)))
      ((>= i length-a))
    (setf (aref value-matrix i 0) i))
  (do ((i 1 (1+ i)))
      ((>= i length-b))
    (setf (aref value-matrix 0 i) i))
  ;iterating our way through the matrix
  (do ((i 1 (1+ i)))
      ((>= i length-a))
    (do ((j 1 (1+ j)))
	((>= j length-b))
      ;here goes the part with the cell values
      (if (char= (aref a (- i 1)) (aref b (- j 1)) )
	  ;characters are equal
	  (setf (aref value-matrix i j) (aref value-matrix (- i 1)(- j 1)))
	  ;characters are not equal
          (progn
	    (defvar min-value)
	    (setf min-value (+ length-a length-b))
	    (if (< (aref value-matrix (- i 1) (- j 1) ) min-value )
                (setf min-value (aref value-matrix (- i 1) (- j 1) )))
	    (if (< (aref value-matrix (- i 1) j) min-value )
		(setf min-value (aref value-matrix (- i 1) j )))
	    (if (< (aref value-matrix i (- j 1)) min-value )
		(setf min-value (aref value-matrix i (- j 1) )))
	    (setf (aref value-matrix i j ) (+ min-value 1))
	  )
	  )
      ))
  (aref value-matrix (- length-a 1)(- length-b 1))
  )


