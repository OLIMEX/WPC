#!/usr/bin/env perl

# Weekend Programming Challenge #31
#
# A Perl5 solution by Dimitrios - Georgios Kontopoulos.
#
#
# To execute the script, call it as below:
# $ ./rled.pl encode ABBBACS
#             or
# $ ./rled.pl decode 2Z4L11X

use strict;
use warnings;

# Make sure that 2 arguments were provided.
@ARGV == 2 or die "Usage: $0 [encode|decode] string\n";

if ( $ARGV[0] eq 'encode' )    # RLE.
{
    print encode( $ARGV[1] ) . "\n";
}
elsif ( $ARGV[0] eq 'decode' )    # RLD.
{
    print decode( $ARGV[1] ) . "\n";
}
else
{
    die "Usage: $0 [encode|decode] string\n";
}

# Decodes RLE strings and returns the result.
sub decode
{
    my ($input) = @_;

    my $result = q{};

    # While the input string is not empty...
    while ( $input ne q{} )
    {

        # If the string starts with one or more numbers
        # and a non-number character...
        if ( $input =~ /^(\d+)(\D)/ )
        {

            # Return the non-number character as
            # many times as the number one.
            $result .= join q{}, map { $2 } 1 .. $1;

            # Remove these characters from the input string.
            $input = $';
        }
        else
        {
            die "Not a valid run-length encoded string.\n";
        }
    }
    return $result;
}

# Encodes strings to RL and returns the result.
sub encode
{
    my ($input) = @_;

    my @string = split //, $input;

    # If the string only has one letter...
    if ( $#string == 0 )
    {

        # Return '1' and the letter.
        return '1' . $string[0];
    }
    else    # Otherwise...
    {
        my $result = q{};

        # Initialize the count at 1.
        my $running_count = 1;

        # For every character of the string...
        for ( 1 .. $#string )
        {

            # If the character is the same as the previous one...
            if ( $string[$_] eq $string[ $_ - 1 ] )
            {

                # Increment the count.
                $running_count++;
            }
            else
            {

                # Otherwise return the count and the previous character.
                $result .= $running_count . $string[ $_ - 1 ];

                # Reset the count at 1.
                $running_count = 1;
            }

            # If we reached the end of the string...
            if ( $_ == $#string )
            {

                # Return the count and the final character.
                $result .= $running_count . $string[$_];
            }
        }
        return $result;
    }
}
