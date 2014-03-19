#!/usr/bin/env perl

# Weekend Programming Challenge #46
#
# A Perl 5 solution by Dimitrios - Georgios Kontopoulos.

use strict;
use warnings;

use feature qw(say);

# Define a period of 12 hours.
my $full_time = 12 * 60;

my $crosses = 0;
for ( 0 .. $full_time )
{

    # If the positions match, report the time.
    if ( hour_arrow($_) eq minute_arrow($_) )
    {
        my ( $hour, $minute ) = reformat_time($_);
        say $hour . q{:} . $minute;

        $crosses++;
    }
}

say "The arrows cross $crosses times over a 12 hour period.";

#############################################
# S   U   B   R   O   U   T   I   N   E   S #
#############################################

# Calculate the position of the hour arrow.
sub hour_arrow
{
    my ($time_point) = @_;

    my $position = $time_point / 12;
    return round($position);
}

# Calculate the position of the minute arrow.
sub minute_arrow
{
    my ($time_point) = @_;
    my $position = $time_point;

    if ( $position > 60 )
    {
        $position -= 60 * int( $position / 60 );
    }
    return round($position);
}

# Convert time to hours and minutes.
sub reformat_time
{
    my ($time) = @_;

    if ( $time > 60 )
    {
        my $hours = int $time / 60;
        $time -= $hours * 60;

        return ( sprintf '%02d', int $hours ), ( sprintf '%02d', $time );
    }
    else
    {
        return '00', sprintf '%02d', $time;
    }
}

# Round time.
sub round
{
    my ($number) = @_;
    if ( ( $number - int $number ) > 0.5 )
    {
        return int $number + 1;
    }
    elsif ( ( $number - int $number ) < 0.5 )
    {
        return int $number;
    }
    else
    {
        return $number;
    }
}
