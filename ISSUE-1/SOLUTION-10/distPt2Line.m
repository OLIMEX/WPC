function myDistance = distPt2Line(A, B, C)
% (c) 2013, Iain Cunningham, inspired by a competition at http://olimex.wordpress.com
% 
% This work is licensed under a:
%	Creative Commons Attribution-ShareAlike 3.0 Unported License.
%
% function myDistance = distPt2Line(A, B, C)
%	Calculate the distance between the point defined by vector C and a straight line 
%	through the points defined by vectors A and B.  All calculations are based on an
%	assumption of Euclidean space.  Requires the function getUnitVector.m
%
%	outputs:
%		myDistance: the distance
%	inputs:
%		A, B, C: n-dimensional vectors (n >=2) of equal size and form (row or column)

	params = inputParser;												% Create object
	params.FunctionName = "distPt2Line";								% Set function name
	validNumber = @(y) isnumeric(y) && ~isnan(y);
	validVector = @(x) isvector(x) && ~isscalar(x) && validNumber(x);	% Require a vector that is >1-D
	params = params.addRequired ("A", validVector);						% Create mandatory argument
	params = params.addRequired ("B", validVector);						% Create mandatory argument
	params = params.addRequired ("C", validVector);						% Create mandatory argument
	
	params.parse(A, B, C);
		
	if(~size_equal(A, B) || ~size_equal(B, C))
		error('distPt2Line: Sizes of A, B and C must match')
	end
	
	myUnitVect = getUnitVector(A, B);
	
	%(A-C)-((A-C)dot N)N
	
	myDistance = norm((A - C) - (dot(A - C, myUnitVect)).*myUnitVect, 2);
	
% Unit tests - input checks
%!error <`A' undefined> distPt2Line()
%!error <`B' undefined> distPt2Line([0 0])
%!error <`C' undefined> distPt2Line([0 0], [0 0])
%!error <'A' failed validation> distPt2Line([0], [1 1], [0 0])
%!error <'A' failed validation> distPt2Line([0 0; 0 0], [1 1], [0 0])
%!error <A, B and C must match> distPt2Line([0 0], [1 1 1], [0 0])
%!error <A, B and C must match> distPt2Line([0 0], [1 1], [0 0 0])
%!error <'A' failed validation> distPt2Line(['NaN' '0'], [1 1], [0 0])
%
% Unit tests - return values
%!assert(distPt2Line([0 0], [0 0], [0 0]), 0) % All points coincident
%!assert(distPt2Line([0 0], [2 2], [1 1]), 0, 2*eps) % Point on line AB
%!assert(distPt2Line([0 0], [1 0], [0 1]), 1, 2*eps) % Point off line AB but inside its 'ends'
%!assert(distPt2Line([0 0 0], [1 0 0], [2 1 0]), 1, 2*eps) % Point off line AB and outside its 'ends'