#!/usr/bin/perl
use strict;
use IO::Prompt;
use POSIX qw( ceil );

sub simplify {
    my ($n, $d) = @_;
    for (my $i = 2; $i <= $n && $i <= $d; $i++) {
        next if $n % $i or $d % $i;
        $n /= $i;
        $d /= $i;
        $i = 2;
        redo;
    }
    return ($n, $d);
}

my $n = prompt("a = ");
my $d = prompt("b = ");

print "$n/$d = ";
($n, $d) = simplify($n, $d);
while ($n != 1) {
    my $q = ceil($d / $n);
    ($n, $d) = ($n - $d % $n, $d * $q);
    if ($n == 0) {
        ($n, $d) = (1, $q);
        last;
    }
    print "1/$q + ";
    ($n, $d) = simplify($n, $d);
}
print "1/$d\n";