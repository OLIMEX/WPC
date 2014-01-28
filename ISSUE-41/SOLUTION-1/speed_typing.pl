#!/usr/bin/env perl

# Weekend Programming Challenge #41
#
# A Perl 5 GUI program by Dimitrios - Georgios Kontopoulos.
#
# DEPENDENCIES:
# 	HTML::Restrict (Perl module)
#   Gtk2 (Perl module)
#   LWP::Simple (Perl module)
#   String::Approx (Perl module)
#   libgtk2.0-0

use strict;
use warnings;

use HTML::Restrict;
use Gtk2 -init;
use LWP::Simple;
use String::Approx qw(adistr);

use feature qw(say);

# Create the main window.
my $window = Gtk2::Window->new('toplevel');
$window->set_title('Speed Typing test');
$window->set_position('center');
$window->set_size_request( 800, 400 );
$window->signal_connect( destroy => sub { exit; } );

my $vbox = Gtk2::VBox->new( '0', '0' );

my $toolbar = Gtk2::HBox->new( 0, 20 );

###########################
# FETCH NEW TEXT 'BUTTON' #
###########################
my $new_text_button = Gtk2::EventBox->new;

my $new_text_hbox = Gtk2::HBox->new( 0, 20 );
my $new_text =
  Gtk2::Image->new_from_stock( 'gtk-new', 'GTK_ICON_SIZE_LARGE_TOOLBAR' );

$new_text_hbox->add($new_text);
$new_text_hbox->add( Gtk2::Label->new('Fetch new text') );

$new_text_button->add($new_text_hbox);
$new_text_button->signal_connect( 'button_press_event' => \&fetch_wiki_text );

$toolbar->add($new_text_button);
$toolbar->add( Gtk2::VSeparator->new );

##################
# ABOUT 'BUTTON' #
##################

my $about_button = Gtk2::EventBox->new;

my $about_hbox = Gtk2::HBox->new( 0, 20 );
my $about =
  Gtk2::Image->new_from_stock( 'gtk-about', 'GTK_ICON_SIZE_LARGE_TOOLBAR' );

$about_hbox->add($about);
$about_hbox->add( Gtk2::Label->new('About this application') );

$about_button->add($about_hbox);
$about_button->signal_connect( 'button_press_event' => \&about );

$toolbar->add($about_button);
$toolbar->add( Gtk2::VSeparator->new );

#################
# QUIT 'BUTTON' #
#################
my $quit_button = Gtk2::EventBox->new;

my $quit_hbox = Gtk2::HBox->new( 0, 20 );
my $quit =
  Gtk2::Image->new_from_stock( 'gtk-quit', 'GTK_ICON_SIZE_LARGE_TOOLBAR' );

$quit_hbox->add($quit);
$quit_hbox->add( Gtk2::Label->new('Quit') );

$quit_button->add($quit_hbox);
$quit_button->signal_connect( 'button_press_event' => sub { exit; } );

$toolbar->add($quit_button);

$vbox->add($toolbar);

########################
# HORIZONTAL SEPARATOR #
########################
$vbox->add( Gtk2::HSeparator->new );

#################################
# SPACE FOR WIKIPEDIA PARAGRAPH #
#################################
my $label = Gtk2::Label->new;
$label->set_size_request( 780, 200 );
$label->set_line_wrap('TRUE');

$vbox->add($label);

########################
# HORIZONTAL SEPARATOR #
########################
$vbox->add( Gtk2::HSeparator->new );

##########################
# SPACE FOR USER TO TYPE #
##########################
my $textarea = Gtk2::TextView->new;
$textarea->set_size_request( 450, 100 );
$textarea->set_wrap_mode('GTK_WRAP_WORD');
$textarea->set_sensitive(0);

my $buffer = Gtk2::TextBuffer->new;
$textarea->set_buffer($buffer);
$vbox->add($textarea);

########################
# HORIZONTAL SEPARATOR #
########################
$vbox->add( Gtk2::HSeparator->new );

my $hbox = Gtk2::HBox->new( 0, 20 );

############################
# 'GO!' AND 'STOP' BUTTONS #
############################
my $go_button   = Gtk2::Button->new_with_label('Go!');
my $stop_button = Gtk2::Button->new_with_label('Stop!');
$stop_button->set_sensitive(0);

my ( $starting_time, $stopping_time );

# When the 'Go!' button is clicked, the text area activates
# and time starts counting.
$go_button->signal_connect(
    'clicked' => sub {
        $textarea->set_sensitive(1);

        $starting_time = time;
        $textarea->grab_focus();

        $go_button->set_sensitive(0);
        $stop_button->set_sensitive(1);
    }
);
$hbox->add($go_button);

# When the 'Stop' button is clicked, time stops counting and
# stats are shown.
$stop_button->signal_connect( 'clicked' => \&stop_and_show_stats );
$hbox->add($stop_button);

$vbox->add($hbox);
$window->add($vbox);

fetch_wiki_text();

$window->show_all;
Gtk2->main;

# Create a popup 'About this app' window.
sub about
{
    my $about_window = Gtk2::Window->new('toplevel');
    $about_window->set_title('About this application');
    $about_window->signal_connect( destroy => sub { $about_window->destroy } );
    $about_window->set_resizable(0);

    my $top_info = <<'ABOUT';
			<b>Speed Typing test</b>
(C) 2014 Dimitrios - Georgios Kontopoulos
ABOUT
    chomp $top_info;

    my $second_info = <<'ABOUT';
<span size="small"><b>Speed Typing test</b> fetches the first paragraph from
random Wikipedia articles and tests your writing 
speed and precision, as you copy them.

This application was written in +
<a href="http://www.perl.org/">Perl</a>/+
<a href="http://gtk2-perl.sourceforge.net/">GTK2</a> for the +
<a href="http://olimex.wordpress.com/2014/01/24/weekend-programming-challenge-week-41-speed-typing-test/">
41st Weekend Programming Challenge</a> by Olimex.</span>+
ABOUT
    $second_info =~ s/[+]\n//g;
    my $license = <<'ABOUT';
<span size="small"><b><u>License:</u></b>
<i>This program is free software; you can redistribute it
and/or modify it under the terms of the <a href="http://www.gnu.org/licenses/gpl.html">GNU General
Public License, as published by the Free Software
Foundation; either version 3 of the License, or (at your
option) any later version</a>.

This program is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.</i></span>
ABOUT
    chomp $license;
    my $vbox = Gtk2::VBox->new( '0', '10' );
    my $label1 = Gtk2::Label->new();
    $label1->set_markup($top_info);
    my $separator1 = Gtk2::HSeparator->new;
    my $label2     = Gtk2::Label->new();
    $label2->set_markup($second_info);
    my $separator2 = Gtk2::HSeparator->new;

    my $license_button = Gtk2::ToggleButton->new_with_label('License');

    # Clicking the License button toggles between the license
    # and the default text.
    my $license_counter = 0;
    $license_button->signal_connect(
        toggled => sub {
            if ( $license_counter == 0 )
            {
                $license_counter = 1;
                $label2->set_markup($license);
                $about_window->show_all;
            }
            else
            {
                $license_counter = 0;
                $license_button->set_active(0);
                $label2->set_markup($second_info);
                $about_window->show_all;
            }
        }
    );

    my $quit_button = Gtk2::Button->new_from_stock('gtk-quit');
    $quit_button->signal_connect( 'clicked' => sub { $about_window->destroy } );

    $vbox->add($label1);
    $vbox->add($separator1);
    $vbox->add($label2);
    $vbox->add($separator2);

    my $buttons_hbox = Gtk2::HBox->new( 0, 20 );
    $buttons_hbox->add($license_button);
    $buttons_hbox->add($quit_button);

    $vbox->add($buttons_hbox);
    $about_window->set_position('center');
    $about_window->set_border_width(15);
    $about_window->add($vbox);

    $about_window->show_all;
    Gtk2->main;
    return 0;
}

# Count the number of words in the typed text.
sub count_words
{
    my ($phrase) = @_;
    return 1 + ( $phrase =~ tr{ }{ } );
}

# Fetch the first paragraph of a random Wikipedia article.
sub fetch_wiki_text
{
    while ( 1 == 1 )
    {

        # Get a random Wikipedia article.
        my $wikipedia_text =
          get('https://en.wikipedia.org/wiki/Special:Random');

        # Get the first paragraph of the article.
        if ( $wikipedia_text =~ /class="mw-content-ltr"><p>(.*?)<\/p>/ )
        {

            # Discard this article if it contains coordinates (for ease).
            if ( $1 !~ /Coordinates/i )
            {

                # Remove HTML tags from the paragraph.
                my $hr = HTML::Restrict->new;
                if ( my $first_par = $hr->process($1) )
                {

                    # Remove non-ASCII characters from the paragraph.
                    $first_par =~ s/[^[:ascii:]]//g;

                    $label->set_text($first_par);
                    last;
                }
            }
        }
    }

    # Prepare the buttons and the text area.
    $go_button->set_sensitive(1);
    $stop_button->set_sensitive(0);
    $buffer->set_text(q{});
    return 0;
}

# Stop the time and show statistics.
sub stop_and_show_stats
{
    $stopping_time = time;
    $textarea->set_sensitive(0);
    $stop_button->set_sensitive(0);

    # Create a popup window with statistics.
    my $result_window = Gtk2::Window->new('popup');
    $result_window->set_position('center');

    my $result_vbox = Gtk2::VBox->new( '0', '10' );

    my $message_hbox = Gtk2::HBox->new( 0, 20 );

    # Compute the similarity between the Wikipedia text
    # and the text typed by the user.
    #
    # A similarity of 0 indicates perfect match, whereas
    # a similarity of -1 indicates totally different text.
    my $wiki_text = $label->get_text;
    my ( $text_start, $text_end ) = $buffer->get_bounds;
    my $typed_text = $buffer->get_text( $text_start, $text_end, 1 );

    my $similarity;
    if ( length $wiki_text >= length $typed_text )
    {
        $similarity = adistr( $wiki_text, $typed_text );
    }
    elsif ( length $typed_text > length $wiki_text )
    {
        $similarity = adistr( $typed_text, $wiki_text );
    }

    # If the similarity is bigger than 0, set it to 0.
    if ( $similarity > 0 )
    {
        $similarity = 0;
    }

    # If the similarity is smaller than -1, set it to -1.
    elsif ( $similarity < -1 )
    {
        $similarity = -1;
    }

    # Transform similarity into precision as a percentage.
    my $precision = sprintf( q{%.2f}, ( ( $similarity + 1 ) * 100 ) ) . '%';

    # If similarity is less than -0.3, show the failure icon.
    if ( $similarity < -0.3 )
    {
        $message_hbox->add(
            Gtk2::Image->new_from_stock( 'gtk-cancel', 'GTK_ICON_SIZE_DIALOG' )
        );
    }

    # Otherwise, show the success icon.
    else
    {
        $message_hbox->add(
            Gtk2::Image->new_from_stock( 'gtk-apply', 'GTK_ICON_SIZE_DIALOG' )
        );
    }

    # Compute the total time it took for the user to type.
    my $final_time = $stopping_time - $starting_time;

    # Calculate words per minute.
    my $words_per_min;

    # If the user didn't type anything, set WPM to 0.
    if ( count_words($typed_text) == 0 or $final_time == 0 )
    {
        $words_per_min = 0;
    }
    else
    {
        $words_per_min = sprintf q{%d},
          ( 60 * count_words($typed_text) / $final_time );
    }

    # Display the results.
    my $message = << "END";
It took you <b>$final_time sec.</b> to complete this paragraph!

<b>Precision:</b> $precision
<b>Words per minute:</b> $words_per_min
END

    my $stats = Gtk2::Label->new();
    $stats->set_markup($message);

    $message_hbox->add($stats);
    $result_vbox->add($message_hbox);

    my $button_hbox = Gtk2::HBox->new( 0, 20 );

    #########################
    # NEW PARAGRAPH BUTTON. #
    #########################
    my $new_par_button = Gtk2::Button->new_with_label('Do another one!');
    $new_par_button->signal_connect(
        'clicked' => sub {
            fetch_wiki_text();
            $result_window->destroy;
        }
    );
    $button_hbox->add($new_par_button);

    ################
    # QUIT BUTTON. #
    ################
    my $quit_button = Gtk2::Button->new_from_stock('gtk-quit');
    $quit_button->signal_connect( 'clicked' => sub { exit; } );
    $button_hbox->add($quit_button);

    $result_vbox->add($button_hbox);

    $result_window->add($result_vbox);
    $result_window->set_border_width(15);
    $result_window->show_all;
    return 0;
}
