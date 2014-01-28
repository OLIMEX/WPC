<center><h1>Speed Typing test</h1></center>

<h2>Description</h2>
Speed Typing test fetches the first paragraph from random Wikipedia articles and tests your writing speed and precision, as you copy them.

This application was written in <a href="http://www.perl.org/">Perl</a>/<a href="http://gtk2-perl.sourceforge.net/">GTK2</a> for the <a href="http://olimex.wordpress.com/2014/01/24/weekend-programming-challenge-week-41-speed-typing-test/">41st Weekend Programming Challenge</a> by Olimex.

<h2>Source Code and Binaries</h2>
The source code file (speed_typing.pl) requires all the dependencies mentioned below, in order to run. For your convenience, two binary files are also provided. These do not require installation of dependencies and should be able to run on relatively recent Ubuntu GNU/Linux systems.

<h2>Usage</h2>
Both scripts and binary files need to be made executable in order to run. One way to do it is with the command line (*chmod 755 path_to_file*).

When the application is launched, it will automatically try to find a suitable Wikipedia article and retrieve its first paragraph. The user can then click the 'Go!' button to start the timer and start copying the text. As soon as the user is done typing, clicking the 'Stop' button will stop the timer and display statistics about the user's precision and speed.

<h2>Dependencies</h2>
-HTML::Restrict (Perl module)

-Gtk2 (Perl module)

-LWP::Simple (Perl module)

-String::Approx (Perl module)

-libgtk2.0-0

<h2>License</h2>
This program is free software; you can redistribute it and/or modify it under the terms of the <a href="http://www.gnu.org/licenses/gpl.html">GNU General Public License, as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version</a>.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

<h2>Author</h2>
Dimitrios - Georgios Kontopoulos
