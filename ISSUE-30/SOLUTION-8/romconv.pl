#!/usr/bin/perl

# Decimal to Roman numbers convertor, v. 0.1.
# This script is in the public domain.
# Dimitar D. Mitov, 2013.
# Created for Olimex Weekend Programming Challenge #30: Roman numbers
# http://olimex.wordpress.com/2013/10/25/weekend-programming-challenge-week-30-roman-numbers/

# Some references for the system of Roman numerals:
# http://mathworld.wolfram.com/RomanNumerals.html
# http://en.wikipedia.org/wiki/Roman_numerals

use strict;
use warnings;

print <<HEADING;

Decimal to Roman numbers convertor, v.0.1.
HEADING

my $decimal;
if (not defined $ARGV[0]){
	print "\nPlease enter positive decimal integer number (1-999999, no interval or thousands separator): ";
	$decimal = <>;
} else {
	$decimal = $ARGV[0];
}
chomp $decimal;

if ($decimal !~ /\d/ or $decimal =~ /\D/ or $decimal > 999999){
	print "\nInvalid input! You have to enter positive decimal integer number from 1 to 999999. Quiting.\n\n";
	exit;
}

my @decimal = split (//, $decimal);
# http://alvinalexander.com/perl/perl-reverse-array-perl-reverse-sort-array
my @decimal_reverse = reverse @decimal;

my $ones = "";
my $tens = "";
my $hundreds = "";
my $thousands = "";
my $m_thousands = "";
my $tens_of_thousands = "";
my $hundreds_of_thousands = "";

my $digit_position ;
foreach my $digit (@decimal_reverse) {
	$digit_position++;
	if ($digit_position == 1) {
		if ($digit == 1) {
			$ones = "I";
		}
		if ($digit == 2) {
			$ones = "II";
		}
		if ($digit == 3) {
			$ones = "III";
		}
		if ($digit == 4) {
			$ones = "IV";
		}
		if ($digit == 5) {
			$ones = "V";
		}
		if ($digit == 6) {
			$ones = "VI";
		}
		if ($digit == 7) {
			$ones = "VII";
		}
		if ($digit == 8) {
			$ones = "VIII";
		}
		if ($digit == 9) {
			$ones = "IX";
		}
	}
	if ($digit_position == 2) {
		if ($digit == 1) {
			$tens = "X";
		}
		if ($digit == 2) {
			$tens = "XX";
		}
		if ($digit == 3) {
			$tens = "XXX";
		}
		if ($digit == 4) {
			$tens = "XL";
		}
		if ($digit == 5) {
			$tens = "L";
		}
		if ($digit == 6) {
			$tens = "LX";
		}
		if ($digit == 7) {
			$tens = "LXX";
		}
		if ($digit == 8) {
			$tens = "LXXX";
		}
		if ($digit == 9) {
			$tens = "XC";
		}
	}
	if ($digit_position == 3) {
		if ($digit == 1) {
			$hundreds = "C";
		}
		if ($digit == 2) {
			$hundreds = "CC";
		}
		if ($digit == 3) {
			$hundreds = "CCC";
		}
		if ($digit == 4) {
			$hundreds = "CD";
		}
		if ($digit == 5) {
			$hundreds = "D";
		}
		if ($digit == 6) {
			$hundreds = "DC";
		}
		if ($digit == 7) {
			$hundreds = "DCC";
		}
		if ($digit == 8) {
			$hundreds = "DCCC";
		}
		if ($digit == 9) {
			$hundreds = "CM";
		}
	}

	if ($digit_position == 4) {
		if ($digit == 1) {
			$m_thousands = "M";
			$thousands = "I";
		}
		if ($digit == 2) {
			$m_thousands = "MM";
			$thousands = "II";
		}
		if ($digit == 3) {
			$m_thousands = "MMM";
			$thousands = "III";
		}
		if ($digit == 4) {
			$thousands = "IV";
		}
		if ($digit == 5) {
			$thousands = "V";
		}
		if ($digit == 6) {
			$thousands = "VI";
		}
		if ($digit == 7) {
			$thousands = "VII";
		}
		if ($digit == 8) {
			$thousands = "VIII";
		}
		if ($digit == 9) {
			$thousands = "IX";
		}
	}
	if ($digit_position == 5) {
		if ($digit == 1) {
			$tens_of_thousands = "X";
		}
		if ($digit == 2) {
			$tens_of_thousands ="XX";
		}
		if ($digit == 3) {
			$tens_of_thousands ="XXX";
		}
		if ($digit == 4) {
			$tens_of_thousands ="XL";
		}
		if ($digit == 5) {
			$tens_of_thousands ="L";
		}
		if ($digit == 6) {
			$tens_of_thousands ="LX";
		}
		if ($digit == 7) {
			$tens_of_thousands ="LXX";
		}
		if ($digit == 8) {
			$tens_of_thousands ="LXXX";
		}
		if ($digit == 9) {
			$tens_of_thousands ="XC";
		}
	}
	if ($digit_position == 6) {
		if ($digit == 1) {
			$hundreds_of_thousands = "C";
		}
		if ($digit == 2) {
			$hundreds_of_thousands = "CC";
		}
		if ($digit == 3) {
			$hundreds_of_thousands = "CCC";
		}
		if ($digit == 4) {
			$hundreds_of_thousands = "CD";
		}
		if ($digit == 5) {
			$hundreds_of_thousands = "D";
		}
		if ($digit == 6) {
			$hundreds_of_thousands = "DC";
		}
		if ($digit == 7) {
			$hundreds_of_thousands = "DCC";
		}
		if ($digit == 8) {
			$hundreds_of_thousands = "DCCC";
		}
		if ($digit == 9) {
			$hundreds_of_thousands = "CM";
		}
	}
}

if ($decimal > 999 and $decimal < 3999){
	print "\n$m_thousands$hundreds$tens$ones\n\n";
} else {
	my $all_thousands = join ('', $hundreds_of_thousands, $tens_of_thousands, $thousands);
	my $length_of_all_thousand_signs = length ($all_thousands);
	my $counter = 0;
	until ($counter == $length_of_all_thousand_signs){
		print "_";
		$counter++;
	}
	my $interval = "";
	if ($decimal > 999 ){
		$interval = " ";
	}
	print "\n$hundreds_of_thousands$tens_of_thousands$thousands$interval$hundreds$tens$ones\n\n";
}

__END__
