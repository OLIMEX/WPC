#!/usr/bin/perl
# Written by Benjamin Lutz <mail@maxlor.com> on 2013-07-14 for Olimex' 17th weekend
# programming challenge:
# http://olimex.wordpress.com/2013/07/12/weekend-programming-challenge-issue-17-skytale/
#
# So, is this a WOW solution? Probably not. Would turning it into a one-liner make it
# a WOW solution? If you think so, just inline the variables. In any case, even though
# it's a simple problem, I've enjoyed thinking about how solutions might look in
# different programming languages. Thanks for the challenge!

use strict;
use POSIX;

my $rodSize = 10;
my @message = split //, 'Ancient Greeks and Spartans used Scytales to send encrypted messages..';
my $windings = POSIX::ceil((@message + 1) / $rodSize);
my $paddedLen = $windings * $rodSize;

my @encodedMessage = map { @message[($_ * $windings) % ($paddedLen - 1 )] or ' ' } (0..$paddedLen - 2);
my @decodedMessage = map { @encodedMessage[($_ * $rodSize ) % (@encodedMessage)] } (0..@encodedMessage - 1);

print "encoded: [", @encodedMessage, "]\ndecoded: [", @decodedMessage, "]\n";