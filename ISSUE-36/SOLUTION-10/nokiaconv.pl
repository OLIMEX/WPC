#!/usr/bin/perl

# NOKIA text message converter, v. 0.1.
# This script is in the public domain.
# Dimitar D. Mitov, 2013.
# Created for Olimex Weekend Programming Challenge - Week #36: NOKIA text message converter
# http://olimex.wordpress.com/2013/12/06/weekend-programming-challenge-week-36-nokia-text-message-converter/
# "Problem:
# Make code which takes string and convert it to button push sequence on NOKIA1100 phone keypad which will print same string.
# For instance: HELLO -> 44 33 555 555 666"

use strict;
use warnings;

print <<HEADING;

NOKIA text message converter, v.0.1.
HEADING

my $string;
my $converted_string;

# Numbers and punctuation marks are not accepted and converted because:
# 1. You have to switch manually the input mode when you mix numbers and letters using non-numeric keys;
# 2. Punctuation marks are entered by pressing more than one button, also using non-numeric keys.
if (not defined $ARGV[0]){
	print "\nPlease enter your string (only characters and spaces): ";
	$string = <>;
} else {
	$string = $ARGV[0];
}
chomp $string;

if ($string !~ /\w/ or $string =~ "_" or $string =~ /\d/){
	print "\nInvalid input! You have to enter only letters and spaces. Quiting.\n\n";
	exit;
}

$converted_string = uc $string; # convert all letters to upercase
$converted_string =~ s/A/2/g;
$converted_string =~ s/B/22/g;
$converted_string =~ s/C/222/g;
$converted_string =~ s/D/3/g;
$converted_string =~ s/E/33/g;
$converted_string =~ s/F/333/g;
$converted_string =~ s/G/4/g;
$converted_string =~ s/H/44/g;
$converted_string =~ s/I/444/g;
$converted_string =~ s/J/5/g;
$converted_string =~ s/K/55/g;
$converted_string =~ s/L/555/g;
$converted_string =~ s/M/6/g;
$converted_string =~ s/N/66/g;
$converted_string =~ s/O/666/g;
$converted_string =~ s/P/7/g;
$converted_string =~ s/Q/77/g;
$converted_string =~ s/R/777/g;
$converted_string =~ s/S/7777/g;
$converted_string =~ s/T/8/g;
$converted_string =~ s/U/88/g;
$converted_string =~ s/V/888/g;
$converted_string =~ s/W/9/g;
$converted_string =~ s/X/99/g;
$converted_string =~ s/Y/999/g;
$converted_string =~ s/Z/9999/g;
$converted_string =~ s/\s/0/g;

print "Result: $converted_string\n\n"

__END__
