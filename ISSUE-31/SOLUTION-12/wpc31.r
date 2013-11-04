REBOL [file: %wpc31.r]

comment {
>> rle "ooollimeexxx"
== "3o2l1i1m2e3x"
>> rle/shrink "ooollimeexxx"
== "3o2lim2e3x"
>> rld "3o2l1i1m2e3x"
== "ooollimeexxx"
}

rle: func [input [string!] /shrink /local hash here there c nc] [
  bag: make block! reduce [0 (first input)]
  parse/all input [
    here: any [there: skip (
        if (c: first here) <> (nc: first there) [(here: there) (c: nc) (append bag reduce [0 c])]
        change (n: back find/last bag c) (first n) + 1
    )]]
  if shrink [remove-each item bag [item = 1]]
  rejoin bag
]

rld: func [input [string!] /local digits char bag n c] [
  digits: charset [#"0" - #"9"] char: complement digits
  bag: make string! 1000
  parse/all input [any [(n: 1) opt [copy n [some digits]] copy c char (insert/dup (tail bag) c (to-integer n))]]
  head bag
]
