function totalWays = getCatStairs(steps)
% (c) 2013, Iain Cunningham, inspired by a competition at http://olimex.wordpress.com
% 
% This work is licensed under a:
%	Creative Commons Attribution-ShareAlike 3.0 Unported License.
%
% function totalWays = getCatStairs(steps)
%	Find the total number of ways a cat can move up a flight of stairs if
%	limited to moving one or two steps at a time.  Returns NA if steps == 0.
%
%	outputs:
%		totalWays: the total number of permutations.
%
%	inputs (required):
%		steps: total number of step in the flight.

%******************* Input checks - start *******************
params = inputParser;										% Create object
params.FunctionName = "getCatStairs";						% Set function name

% Required arguments
% Function handle to validate a scalar that is numeric and integer >= 0
validFlight = @(x) isnumeric(x) && ~isnan(x) && isscalar(x) && ...
	all(x >= 0) && abs(mod(x, 1)) == 0 ;
params = params.addRequired("steps", validFlight);			% Create mandatory argument

params = params.parse(steps);
%******************** Input checks - end ********************

% Handle trivial cases
if (steps == 0)
	totalWays = NA;
elseif (steps == 1)
	totalWays = 1;
end

if (steps >=2)
	totalWays = 0;										% Initialise return value

	% Find the shortest valid sequence of steps
	loLim = floor(steps/2) + mod(steps, 2);

	for seqLen = loLim:steps								% Loop over all possible sequence lengths
		n1 = 2 * seqLen - steps;							% Calculate the number of ones in the present sequence
		n2 = steps - seqLen;								% Calculate the number of twos in the present sequence
		
		if (n1 == 0 || n2 == 0) 							% Sequence is all ones or all twos
			totalWays = totalWays + 1;
		elseif (n1 == 1 || n2 == 1)							% Sequence contains one one or one two, seqLen permutations
			totalWays = totalWays + seqLen;
		else
			% For all other sequence lengths the number of permutations is the triangular number, T(x)
			% where x = max(n1, n2) + 1
			totalWays = totalWays + getTriNum(max(n1, n2) + 1);
		end
	end
end

% Unit tests - input checks
%!error <'steps' failed validation> getCatStairs([])
%!error <'steps' failed validation> getCatStairs(NA)
%!error <'steps' failed validation> getCatStairs([1 1])
%!error <'steps' failed validation> getCatStairs(-1)
%!error <'steps' failed validation> getCatStairs(1.5)
%
% Unit test - return values
%!assert(getCatStairs(0), NA)
%!assert(getCatStairs(1), 1)
%!assert(getCatStairs(2), 2) % Sequences are {11, 2}
%!assert(getCatStairs(3), 3) % Sequences are {111, 21, 12}
%!assert(getCatStairs(4), 5) % 1 sequence of ones {1111}, 3 with 1 two {211, 121, 112}, 1 with 2 twos {22}
%!assert(getCatStairs(5), 1+4+3) % 1 sequence of ones, 3 with 1 two and 3 with 2 twos
%!assert(getCatStairs(7), 1+6+10+4) % 1 of ones, 6 with 1 two, 10 with 2 twos and 4 with 3 twos
