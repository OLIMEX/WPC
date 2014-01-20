#!/usr/bin/perl
use POSIX;
use strict;

print "Enter number \n";
my $input = <>;
$input =~ s/(\r|\n)//g;

die "Invalid number" if ($input !~ m/^[0-9]+$/);
my $number = $input;

print "Please choose\n\t1) Search only for this number\n\t2) Tests all numbers between 1 and your number\n\t3) Print all numbers \n";
my $input = <>;
$input =~ s/(\r|\n)//g;

die "Invalid choice" if ($input !~ m/^(1|2|3)$/);
if ($input == "1") {
	print "Searching for number $number\n";
	my $answer = search ($number);

	print "Answer is $answer";
	my $check = evalo($answer);
	if ($check == $number) {
		print " - Check OK";
	} else {
		print " - BAD !!!!!!!!! - check = $check";
	}
	print "\n";
} elsif ($input == "2") {
	fulltest($number);
} elsif ($input == "3") {
	printall($number);
}



# Evaluate the expression to check if the guessed expression is good
sub evalo($) {
	my ($st) = @_;
	my $res = "";
	for (my $i=0; $i < length($st); $i++) {
		if (substr($st,$i,2) eq "/2") {
			$res = "floor(" . $res . "/2)";
			$i++;
		} else {
			$res .= substr($st,$i,1);
		}
	}
	return (eval($res));
}

# Recursive search
sub search($) {
	my ($n) = @_;
	
	return "1" if ($n == 1);
	# 5 seems needed, otherwise a lot of numbers fall in an infinite loop on 5 and 7
	return "1*3*3*3*3/2/2/2/2" if ($n == 5);
	
	if ( $n % 3 == 0) {
		return search($n/3) . "*3";
	}
	
	if ( ($n * 2) % 3 == 0) {
		return search ( $n * 2 ) . "/2";
	}
	if ( (($n * 2)+1) % 3 == 0) {
		return search ( ($n * 2)+1 ) . "/2";
	}
	if ( (($n * 2 * 2)+1) % 3 == 0) {
		return search ( ($n * 2 * 2)+1) . "/2/2";
	}
	die "Problem - cannot find a path for $n";
}

sub fulltest($) {
	my ($bound) = @_;
	print "Doing a full test for all numbers from 1 to $bound - will print only bad results\n";
	for (my $t = 1; $t <= $bound; $t++) {
		my $answer = search ($t);
		my $check = evalo($answer);
		if ($check != $t) {
			print "BAD for $t !!!!!!!!! - check = $check\n";
		}
	}
	print "Test complete.\n";
}

sub printall($) {
	my ($bound) = @_;
	print "Printing all numbers from 1 to $bound\n";
	for (my $t = 1; $t <= $bound; $t++) {
		my $answer = search ($t);
		my $check = evalo($answer);
		print $t . " -> " . $answer . " ";
		if ($check == $t) {
			print "OK";
		} else {
			print "BAD !!!!!!!!! - check = $check";
		}
		print "\n";
	}
	print "Printing complete.\n";
}
