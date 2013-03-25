Hi,

Please find my "Gnu Octave .m file"-based solution attached for the
distance from a point to a line defined by two other points.  The file
containing the 'solution' is distPt2Line.m, and the file getUnitVector.m is
a utility function to find a unit vector that defines the direction of the
line AB.  The 'solution' has been generalised to n-dimensions (for n >= 2),
but can be restricted to a 2-D form by modifying line 20 of distPt2Line.m:

validVector = @(x) isvector(x) && ~isscalar(x) && validNumber(x); % Require
a vector that is >1-D

To:

validVector = @(x) isvector(x) && length(x)==2 && validNumber(x); % Require
a vector that is 2-D

Note that making this change will break some of the unit tests.

Both files contain unit tests which also demo the code usage, to run them
type:

test distPt2Line verbose

At the Octave prompt.  These files have been tested in Octave 3.6.2 64-bit
under Windows 7 and Octave 3.6.2 32-bit under Windows XP.

Love the programming challenge idea! :-)

Regards,

Iain