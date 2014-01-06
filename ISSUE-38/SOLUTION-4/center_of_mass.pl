#!/usr/bin/env perl

# Weekend Programming Challenge #38
#
# A Perl 5 solution by Dimitrios - Georgios Kontopoulos.
#
# To execute the script, call it as below:
# $ ./center_of_mass.pl image

use strict;
use warnings;

use Imager;
use Imager::Color;
use Math::Round qw(round);

use feature qw(say);

# Require one argument with a file path.
@ARGV == 1 or die "Usage: $0 image\n";

# Create an Imager object.
my $img = Imager->new( file => $ARGV[0] ) or die Imager->errstr();

# Get the height and the width of the picture.
my $height = $img->getheight();
my $width  = $img->getwidth();

# Initialize the key variables.
my $center_x = 0;
my $center_y = 0;
my $mass     = 0;

# Iterate over rows and columns.
for my $row ( 0 .. $height - 1 )
{
    for my $column ( 0 .. $width - 1 )
    {

        # Get the color of the pixel.
        my $pixel = $img->getpixel( x => $column, y => $row );
        my ( $red, $green, $blue, undef ) = $pixel->rgba();

        # If the pixel is not white ...
        unless ( $red == 255 && $green == 255 && $blue == 255 )
        {

            # Add the coordinates of the pixel.
            $center_x += $column;
            $center_y += $row;
            $mass     += 1;
        }
    }
}

# Calculate the coordinates of the center of mass.
$center_x /= $mass;
$center_y /= $mass;

# Define the red color in RGB format.
my $red = Imager::Color->new( 255, 0, 0 );

# Change the color of the center of mass pixel.
$img->setpixel( x => round($center_x), y => round($center_y), color => $red );

# Add the '_mod' phrase to the original file's name.
my $new_file = q{};
if ( $ARGV[0] =~ /^([^\.]+)[.]/ )
{
    $new_file = $1 . '_mod.' . $';
}

# Save the result to the new file.
$img->write( file => $new_file );

__END__

=head1 NAME

center_of_mass.pl

=head1 AUTHOR

Dimitrios - Georgios Kontopoulos
<dgkontopoulos@member.fsf.org>

=head1 SYNOPSIS

./center_of_mass.pl image.png

=head1 DESCRIPTION

This Perl 5 script solves the L<38th Weekend Programming Challenge 
by Olimex|http://olimex.wordpress.com/2013/12/20/weekend-programming-challenge-week-38-center-of-mass/>.

It requires a path to an image file as input, in order 
to calculate the center of mass. The pixel corresponding to the 
center of mass is then colored red and a new image is produced.

=head1 DEPENDENCIES

-the Perl interpreter, >= 5.10

-Imager, >= 0.97 (Perl module)

-Imager::Color, >= 1.011 (Perl module)

-Math::Round, >= 0.06 (Perl module)

=cut
