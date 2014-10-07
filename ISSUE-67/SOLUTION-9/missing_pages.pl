#!/usr/bin/perl -w
use strict;

# Jerry H. Ross
# dittybop@sbcglobal.net


# Problem:
# There is a book and a number of consecutive pages are missing from this book.
# All we know is that the sum of the page numbers of these pages is 9808.
# Make code which calculates which are the missing pages and displays the result.

# The rules:
#You can code the solution in any programming language during the weekend and
# have to submit it to info@olimex.com latest on Sunday October 5th.


my $i;
my $temp_sum;
my $temp_number;

    for( $i = 1; $i < 9808; $i++ )
    {
        $temp_sum = $i;
        $temp_number = $i;
        while ( $temp_sum < 9808 )
        {
            $temp_sum += ++$temp_number;
        }
        if ( $temp_sum == 9808 )
        {
            print "Missing pages run from $i to $temp_number.\n";
        } 
        
    }