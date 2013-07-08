;
; Olimex Weekend Programming Challenge Issue 16
; Infix to Postfix converter 
;
; http://olimex.wordpress.com/2013/07/05/weekend-programming-challenge-issue-16-infix-to-postfix-converter/
;
; Copyright (c) 2013 Tero Koskinen <tero.koskinen@iki.fi>
;
; Permission to use, copy, modify, and distribute this software for any
; purpose with or without fee is hereby granted, provided that the above
; copyright notice and this permission notice appear in all copies.
;
; THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
; WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
; MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
; ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
; WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
; ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
; OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
;

(ns convert.core
  (:require [expr.CustomVisitor])
  (:import
    (expr CustomVisitor EXPRLexer EXPRParser EXPRBaseVisitor)
    (org.antlr.v4.runtime ANTLRInputStream CommonTokenStream)
  )
  (:gen-class)
)

(declare conv-expr)

(defn print-factor [f]
  {:pre [(:type f)]}

  (case (:type f)
    :number (:value f)
    :expr #(conv-expr (:value f))
  )
)

(defn conv-factors [factor other-factors]
  (list
    (trampoline print-factor factor)
    (map
      (fn [t] (list (trampoline print-factor (:factor t)) (:op t)))
      other-factors
    )
  )
)

; A function for converting syntax tree (in infix notation)
; to postfix notation
;
; The function returns a list, which has many sublists
; and you are expected to flatten it.
(defn conv-expr [tree]
  {:pre [(:term tree)]}

  (list 
    (conv-factors (:factor (:term tree)) (:tail (:term tree)))

    ; This looks more complex than it actually is.
    ;
    ; We are basically looping through (:tail tree) list
    ; and calling "conv-expr" for every item.
    ;
    ; Non-tail-recursive version:
    ; (map (fn [x] (list (conv-expr x) (:op x))) (:tail tree))
    ;
    (loop [current-tree (:tail tree)
           result []]
      (if (or (nil? current-tree) (empty? current-tree))
        result
        (recur (rest current-tree)
               (concat result
                       (conv-factors (:factor (:term (first current-tree)))
                                     (:tail (:term (first current-tree))))
                       [(:op (first current-tree))])
        )
      )
    )
  )
)

; Initialize all Antlr stuff, and send the syntax tree
; to the conv-expr function.
(defn- converter-main [input-file]
  (let [input
        (ANTLRInputStream. (slurp input-file))
        lexer (expr.EXPRLexer. input)
        tokens (CommonTokenStream. lexer)
        parser (expr.EXPRParser. tokens)]
    (.setBuildParseTree parser true)
    (let [tree (.expr parser)
          visitor (CustomVisitor.)
          result (.visit visitor tree)]
      (if (= (.getNumberOfSyntaxErrors parser) 0)
        (do
          (doseq [r (flatten (conv-expr result))] (print r) (print " "))
          (println)
        )
      )
    )
  )
)

; use "examples/add1.expr" as default input if none given
(defn -main [& args]
  (if (> (count args) 0)
    (converter-main (first args))
    (do
      (println "Reading expression from examples/add1.expr")
      (converter-main "examples/add1.expr")
    )
  )
)

