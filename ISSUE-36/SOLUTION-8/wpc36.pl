#!/bin/perl

# Weekend Programming Challenge – Week #36 NOKIA text message converter
#
# Problem:
# Make code which takes string and convert it to button push sequence on
# NOKIA1100 phone keypad which will print same string.
# For instance: HELLO -> 44 33 555 555 666
#
#> perl olimex_wpc36.pl
#  HELLO
#  44 33 555 555 666

my %tr = (
    '.' => '1', ',' => '11', '?' => '111', '!' => '1111', '1' => '11111'
  , 'a' => '2', 'b' => '22', 'c' => '222', '2' => '2222'
  , 'd' => '3', 'e' => '33', 'f' => '333', '3' => '3333'
  , 'g' => '4', 'h' => '44', 'i' => '444', '4' => '4444'
  , 'j' => '5', 'k' => '55', 'l' => '555', '5' => '5555'
  , 'm' => '6', 'n' => '66', 'o' => '666', '6' => '6666'
  , 'p' => '7', 'q' => '77', 'r' => '777', 's' => '7777', '7' => '77777'
  , 't' => '8', 'u' => '88', 'v' => '888', '8' => '8888'
  , 'w' => '9', 'x' => '99', 'y' => '999', 'z' => '9999', '9' => '99999'
  , ' ' => '0', '0' => '00'
);

chomp($_ = lc <>);
print defined $tr{$_} ? "$tr{$_} " : '* ' for split //;