#!/usr/bin/env perl

# Weekend Programming Challenge #47
#
# A Perl 5 solution by Dimitrios - Georgios Kontopoulos.
#
# DEPENDENCIES:
# - the Perl interpreter, >= 5.10
# - Date::Calc, 6.3 (Perl module)

use strict;
use warnings;

use feature qw(say);

use Date::Calc qw(N_Delta_YMD);

# Get the birthdates for the 2 people.
my ( $year_1, $month_1, $day_1 ) = get_birthdate('1st');
my ( $year_2, $month_2, $day_2 ) = get_birthdate('2nd');

# Display the result.
say display_results(
    N_Delta_YMD( $year_1, $month_1, $day_1, $year_2, $month_2, $day_2 ) );

#############################################
# S   U   B   R   O   U   T   I   N   E   S #
#############################################

sub display_results
{
    my ( $year, $month, $day, $state ) = @_;

    # If the dates are the same, then they were born on the same day.
    if ( $year == 0 && $month == 0 && $day == 0 )
    {
        return 'These people were born on the same day.';
    }

    # If the difference is negative, then the 2nd person is older than the 1st.
    elsif ( $year < 0 or $month < 0 or $day < 0 )
    {
        display_results( $year * (-1), $month * (-1), $day * (-1), 'reverse' );
    }
    else
    {

        my $results;
        if ( $state && $state eq 'reverse' )
        {
            $results = 'The 2nd person is ';
        }
        else
        {
            $results = 'The 1st person is ';
        }
        if ( $year > 0 )
        {
            $results .= $year;
            if ( $year > 1 )
            {
                $results .= ' years ';
            }
            else
            {
                $results .= ' year ';
            }
        }

        if ( $month > 0 )
        {
            $results =~ s/year(s?)/year$1,/;

            $results .= $month;
            if ( $month > 1 )
            {
                $results .= ' months ';
            }
            else
            {
                $results .= ' month ';
            }
        }

        if ( $day > 0 )
        {
            $results =~ s/(month|year)(s?)\s$/$1$2, /;

            $results .= $day;
            if ( $day > 1 )
            {
                $results .= ' days ';
            }
            else
            {
                $results .= ' day ';
            }
        }

        if ( $state && $state eq 'reverse' )
        {
            $results .= 'older than the 1st person.';
        }
        else
        {
            $results .= 'older than the 2nd person.';
        }

        # Turn the last comma into 'and'.
        $results =~ s/,([^,]+)$/ and$1/;

        return $results;
    }
}

# Get a birthdate.
sub get_birthdate
{
    my ($person_id) = @_;

    while ( 1 == 1 )
    {
        print "Enter the birthdate of the $person_id person (yyyy-mm-dd): ";
        my $input = <>;
        chomp $input;

        if ( $input =~ /(\d{4})-(\d{2})-(\d{2})/ )
        {
            return $1, $2, $3;
        }
    }

}
