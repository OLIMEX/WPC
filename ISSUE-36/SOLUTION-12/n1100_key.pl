#!/usr/bin/env perl

# Weekend Programming Challenge #36
#
# A Perl 5 solution by Dimitrios - Georgios Kontopoulos.
#
# To execute the script, call it as below:
# $ ./n1100_key.pl STRING

use strict;
use warnings;

use feature qw(say);

# Require a string as an argument.
@ARGV == 1 or die "Usage: $0 string\n";

# Print the result.
say keypad_convert( $ARGV[0] );

# Convert from string to Nokia 1100 button push sequence.
sub keypad_convert
{
    my ($string) = @_;

    # Remove non-letter characters.
    $string =~ s/[^\s|\w]|\d//g;

    # Substitute space with 0 and then space.
    $string =~ s/ /0/g;
    $string =~ s/0(\S)/0 $1/g;

    $string =~ s/A/2 /ig;
    $string =~ s/B/22 /ig;
    $string =~ s/C/222 /ig;

    $string =~ s/D/3 /ig;
    $string =~ s/E/33 /ig;
    $string =~ s/F/333 /ig;

    $string =~ s/G/4 /ig;
    $string =~ s/H/44 /ig;
    $string =~ s/I/444 /ig;

    $string =~ s/J/5 /ig;
    $string =~ s/K/55 /ig;
    $string =~ s/L/555 /ig;

    $string =~ s/M/6 /ig;
    $string =~ s/N/66 /ig;
    $string =~ s/O/666 /ig;

    $string =~ s/P/7 /ig;
    $string =~ s/Q/77 /ig;
    $string =~ s/R/777 /ig;
    $string =~ s/S/7777 /ig;

    $string =~ s/T/8 /ig;
    $string =~ s/U/88 /ig;
    $string =~ s/V/888 /ig;

    $string =~ s/W/9 /ig;
    $string =~ s/X/99 /ig;
    $string =~ s/Y/999 /ig;
    $string =~ s/Z/9999 /ig;

    return $string;
}
