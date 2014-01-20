#!/usr/bin/env perl

# Weekend Programming Challenge #40
#
# A Perl 5 solution by Dimitrios - Georgios Kontopoulos.
#
# DEPENDENCIES:
# 	List::MoreUtils (Perl module)
#
# To execute the script, call it as below:
# $ ./three_and_two.pl number

use strict;
use warnings;

use feature qw(say);

use List::MoreUtils qw(uniq);

# Require 1 numeric argument.
@ARGV == 1 or die "Usage: $0 number\n";

my $equation;
my @equations;

# Get 300 equations of '*3' and '/2' that produce this number.
for ( 0 .. 300 )
{
    while ( 1 == 1 )
    {
        $equation = find_equation( $ARGV[0] );

        # Exit the loop if an equation was found.
        last unless ( $equation eq '-1' );
    }

    # If the input number is 2, add '/2' at the end of the equation.
    # This is the only number that gets "special treatment".
    if ( $ARGV[0] == 2 )
    {
        $equation .= ' / 2';
    }

    # Store the equation in an array.
    push @equations, $equation;
}

# Filter duplicate equations from the array.
@equations = uniq(@equations);

# Get the shortest equation found and print it.
say $ARGV[0] . q{ = } . shortest_equation( \@equations );

# Find an equation of '*3' and '/2' that produces this number.
sub find_equation
{
    my ($number) = @_;

    # Initialize the equation.
    my $result   = 1;
    my $equation = '1';

    # If the input number is 2, change it for 4 (see lines 37-38).
    if ( $number == 2 )
    {
        $number = 4;
    }

    while ( 1 == 1 )
    {

        # If the resulting number -as integer- is equal to the input one,
        # return the equation.
        if ( int $result == $number )
        {
            return $equation;
        }

        # If the resulting number -as integer- is greater than the input
        # one and integer multiple of it, then ...
        elsif ( int $result > $number && int $result % $number == 0 )
        {
            $result = int $result;

            # ... keep dividing by 2, until the resulting number is equal
            # to the input one.
            do
            {
                $result /= 2;
                $equation .= ' / 2';
            } while ( $result > $number );
        }

        # If the resulting number is 0, then the function failed and exits.
        elsif ( int $result == 0 )
        {
            return '-1';
        }

        # Otherwise, randomly multiply with 3 and divide by 2.
        else
        {
            $result = int $result;
            if ( ( int rand 2 ) == 0 )
            {
                $result *= 3;
                $equation .= ' * 3';
            }
            else
            {
                $result /= 2;
                $equation .= ' / 2';
            }
        }
    }
}

# Get the shortest equation that produces the input number.
sub shortest_equation
{
    my ($array) = @_;

    # Initialize the minimum length as a huge number.
    my $min_length = 999_999_999;

    my $shortest;

    # For every equation found...
    for ( 0 .. @{$array} - 1 )
    {

        # If the equation is shorter than the minimum one, keep it and
        # set its length as the minimum length.
        if ( length $array->[$_] < $min_length )
        {
            $shortest   = $array->[$_];
            $min_length = length $array->[$_];
        }
    }

    # Finally, return the shortest equation found.
    return $shortest;
}
