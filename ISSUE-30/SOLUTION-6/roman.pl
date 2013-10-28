#!/usr/bin/perl

# Roman Numerals
#
# Olimex Weekend Programming Challenge
# 
# Date: 10/26/2013
# Author: Michael Shimniok - http://www.bot-thoughts.com/
#

$U = "\x1b[4m";  ## underline on
$N = "\x1b[24m"; ## underline off

if ($#ARGV == 0) {
	print int2roman($ARGV[0]), "\n";
} else {
	printf("usage: roman.pl integer\n");
}
exit;

# Convert decimal to roman numerals. Uses VT100 escape code for underline symbols.
#
# Not hard to count in Roman numerals from 1-3999, but above that I had to do some research.
#
# Notation through 1,000,000 from http://www.legionxxiv.org/numerals/
#  I = 1
#  V = 5
#  X = 10
#  L = 50
#  C = 100
#  D = 500
#  M = 1000
# _V = 5,000
# _X = 10,000
# _L = 50,000
# _C = 100,000
# _D = 500,000
# _M = 1,000,000
#
# We have an exception at 4000:
# quadramilla		  4,000 MMMM ... but I'm going to ignore that.
# At 5000, the underline characters start, but the pattern returns to normal
# quinmilla           5,000 _V
# decem milia        10,000 _X
# quinqua milia      50,000 _L
# centum milia      100,000 _C
# quingenti milia   500,000 _D
# mille milia     1,000,000 _M
# 
# Any number in the millions and above simply repeats _M, e.g., 5e6 = _M_M_M_M_M
#
sub int2roman {
	$n = $_[0];
	$i = 0;
	$roman = "";

	@integers = ( 1000000, 900000, 500000, 400000, 100000, 90000, 50000, 40000, 10000, 9000, 5000, 
				  4000, 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 );
	@numerals = ( $U."M".$N, $U."CM".$N, $U."D".$N, $U."CD".$N, $U."C".$N, $U."XC".$N, $U."L".$N, 
				  $U."XL".$N, $U."X".$N, "M".$U."X".$N, $U."V".$N, "M".$U."V".$N, 
				  "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" );

	while ($i <= $#integers) {	
		while ( $n >= $integers[$i]) {
			$roman .= $numerals[$i];
			$n -= $integers[$i];
		}
		$i++;
	}
	return $roman;
}
