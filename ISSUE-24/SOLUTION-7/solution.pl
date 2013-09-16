#!/usr/bin/env perl

# Weekend Programming Challenge #24
#
# A Perl5 solution by Dimitrios - Georgios Kontopoulos.
#
#
# To execute the script, call it as below:
# $ ./solution.pl NUMBER

use strict;
use warnings;

use Memoize;
use feature qw(say);

# Make sure that an argument was provided. #
@ARGV == 1 or die "No number was provided!\n";

# Make sure that the argument is numeric. #
if ( $ARGV[0] !~ /^\d+$/ )
{
    die "The argument was not a number!\n";
}

# Memoize the function to make it faster, trading space for time. #
memoize('express');

# Call the main function. #
say express( 1, $ARGV[0] );

sub express
{
    my ( $k, $number ) = @_;
    if ( $k > $number )
    {
        0;
    }
    elsif ( $k == $number )
    {
        1;
    }
    else
    {
        express( $k + 1, $number ) + express( $k, $number - $k );
    }
}
