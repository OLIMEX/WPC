function myUnitVect = getUnitVector(A, B)
% (c) 2013, Iain Cunningham, inspired by a competition at http://olimex.wordpress.com
% 
% This work is licensed under a:
%	Creative Commons Attribution-ShareAlike 3.0 Unported License.
%
% function myUnitVect = getUnitVector(A, B)
%	Calculate the unit vector between the points defined by vectors A and B based
%	on an assumption of Euclidean space. Starting point for the direction of the 
%	unit vector is 'A'. Returns a zero unit vector if A = B
%
%	outputs:
%		myUnitVect: the unit vector, calculated to match the form of the inputs
%	inputs:
%		A, B: n-dimensional vectors (n >=2) of equal size and form (row or column)

	params = inputParser;												% Create object
	params.FunctionName = "getUnitVector";								% Set function name
	validNumber = @(y) isnumeric(y) && ~isnan(y);
	validVector = @(x) isvector(x) && ~isscalar(x) && validNumber(x);	% Require a vector that is >1-D
	params = params.addRequired ("A", validVector);						% Create mandatory argument
	params = params.addRequired ("B", validVector);						% Create mandatory argument
	
	params.parse(A, B);
		
	if(~size_equal(A, B))
		error('getUnitVector: Sizes of A and B must match')
	end
	
	norm2 = norm(B-A, 2);
	
	if (norm2 ~= 0)
		myUnitVect = (B-A)./norm2;
	else
		myUnitVect = zeros(size(A));
	end
	
% Unit tests - input checks
%!error <`A' undefined> getUnitVector()
%!error <`B' undefined> getUnitVector([0 0])
%!error <'A' failed validation> getUnitVector([0], [1 1])
%!error <'A' failed validation> getUnitVector([0 0; 0 0], [1 1])
%!error <A and B must match> getUnitVector([0 0], [1 1 1])
%!error <'A' failed validation> getUnitVector(['NaN' '0'], [1 1])
%
% Unit tests - return values
%!assert(getUnitVector([0 0], [0 0]), [0 0])
%!assert(getUnitVector([0 0], [1 0]), [1 0])
%!assert(getUnitVector([0 0], [2 2]), sqrt(0.5).*[1 1], eps)
