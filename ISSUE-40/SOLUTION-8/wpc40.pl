#!/usr/bin/perl

# wpc40.pl
#
# Weekend Programming Challenge #40
#
#  Author: Michael Shimniok - www.bot-thoughts.com
# Created: Jan 18, 2013
#
# http://olimex.wordpress.com/2014/01/17/weekend-prorgamming-challenge-week-40-numbers/
#
# Any positive integer number can be presented as 1 and several operations *3 and /2 discarding
# the result after the decimal point when dividing.
#
# for instance:
# 4 = 1 *3 *3 /2
# 12 = 1 *3 *3 /2 *3
#
# make code which enters positive integer N then present it with 1 *3 /2 equation.
#
# Usage: wpc40.pl n
#   where n is an integer > 0
#
my $n = $ARGV[0];
my $x = 1;
my $y = 1;
my $mul = "1";
my $div = "";

while (int($x/$y) != $n) {
    if (int($x/$y) < $n) {
        $x *= 3;
        $mul .= "*3";
    }
    while (int($x/$y) > $n) {
        $y *= 2;
        $div .= "/2";
    }
}
printf $mul.$div."\n";


