# NAME

center\_of\_mass.pl

# AUTHOR

Dimitrios - Georgios Kontopoulos
<dgkontopoulos@member.fsf.org>

# SYNOPSIS

./center\_of\_mass.pl image.png

# DESCRIPTION

This Perl 5 script solves the [38th Weekend Programming Challenge by Olimex](http://olimex.wordpress.com/2013/12/20/weekend-programming-challenge-week-38-center-of-mass/).

It requires a path to an image file as input, in order to calculate 
the center of mass. The pixel corresponding to the center of mass is 
then colored red and a new image is produced.

# DEPENDENCIES

\-the Perl interpreter, >= 5.10

\-Imager, >= 0.97 (Perl module)

\-Imager::Color, >= 1.011 (Perl module)

\-Math::Round, >= 0.06 (Perl module)

# EXAMPLE

<center>
<img src="./100x100.png"> ==> <img src="./100x100_mod.png">
</center>
