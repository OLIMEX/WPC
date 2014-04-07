#!/usr/bin/env perl

# Weekend Programming Challenge #49
#
# A Perl5 solution by Dimitrios - Georgios Kontopoulos.
#
# DEPENDENCIES:
#	- the Perl interpreter, >= 5.10
#	- Date::Calc, >= 6.3 (Perl module)
#
# To execute the script, call it as below:
# $ ./easter.pl 2014

use strict;
use warnings;

use feature qw(say);

use Date::Calc qw(Add_Delta_Days);

@ARGV == 1 or die "Usage: $0 YEAR\n";

say Gregorian_Easter( $ARGV[0] );
say Orthodox_Easter( $ARGV[0] );

sub Gregorian_Easter
{
    my ($year) = @_;

    my $a = $year % 19;
    my $b = int( $year / 100 );
    my $c = ( $b - int( $b / 4 ) - int( ( 8 * $b ) / 25 ) + 19 * $a + 15 ) % 30;
    my $d =
      $c -
      int( $c / 28 ) *
      ( 1 - int( $c / 28 ) * int( 29 / ( $c + 1 ) ) * int( ( 21 - $a ) / 11 ) );
    my $e     = ( $year + int( $year / 4 ) + $d + 2 - $b + int( $b / 4 ) ) % 7;
    my $f     = $d - $e;
    my $month = 3 + int( ( $f + 40 ) / 44 );
    my $day   = $f + 28 - ( 31 * int( $month / 4 ) );

    return "Gregorian Easter: $year-$month-$day";
}

sub Orthodox_Easter
{
    my ($year) = @_;

    my $a     = $year % 4;
    my $b     = $year % 7;
    my $c     = $year % 19;
    my $d     = ( 19 * $c + 15 ) % 30;
    my $e     = ( 2 * $a + 4 * $b - $d + 34 ) % 7;
    my $month = int( ( $d + $e + 114 ) / 31 );
    my $day   = ( ( $d + $e + 114 ) % 31 ) + 1;

    ( $year, $month, $day ) = Add_Delta_Days( $year, $month, $day, 13 );
    return " Orthodox Easter: $year-$month-$day";
}
