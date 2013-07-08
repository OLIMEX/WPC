Olimex: Weekend Programming Challenge Issue 16 – Infix to Postfix converter
===========================================================================

A solution made with Antlr4 and Clojure.

Building
--------

Dependencies: Antlr4, Leiningen 2, Clojure

Once you have installed Leiningen:

* Add lein-localrepo plugin.
  Edit ~/.lein/profiles and add line::

   {:user {:plugins [ [ lein-localrepo "0.5.0" ] ] } }

* Download antlr-4.0-complete.jar to $HOME/java/libs from
  http://www.antlr.org/download/antlr-4.0-complete.jar

* Register antlr.jar to Leiningen::

    lein localrepo install $HOME/java/libs/antlr-4.0-complete.jar org.antlr/antlr "4.0"

* Type::

   make
   lein run

Supported operators
-------------------

The converter supports '+', '-', '*', and '/' operators.
In addition, parentheses are supported. Operators '*' and '/'
have higher precedence than '+' and '-'. You can alter the
execution order with parentheses. Expressions inside
parentheses are evaluated first.


Author and License
------------------

This code is written by Tero Koskinen (tero.koskinen@iki.fi>
and it is distributed under ISC license.


