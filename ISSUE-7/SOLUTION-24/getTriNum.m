function triNum = getTriNum(n)
% (c) 2013, Iain Cunningham, inspired by a competition at http://olimex.wordpress.com
% 
% This work is licensed under a:
%	Creative Commons Attribution-ShareAlike 3.0 Unported License.
%
% function triNum = getTriNum(n)
%	Returns the n^{th} triangular number.  Returns 0 for n = 0.
%
%	outputs:
%		triNum: The triangular number.
%
%	inputs (required):
%		n: The triangular number to calculate.

params = inputParser;												% Create object
params.FunctionName = "getTriNum";									% Set function name

% Required arguments
inRange = @(y) all(y >= 0) && abs(mod(y,1)) == 0 ;
validNum = @(x) isnumeric(x) && ~isnan(x) && isscalar(x) && inRange(x);% Function handle to validate a scalar that is numeric and integer >= 0
params = params.addRequired("n", validNum);							% Create mandatory argument

params = params.parse(n);

triNum = n * (n + 1) / 2;

% Unit tests - input checks
%!error <'n' failed validation> getTriNum([])
%!error <'n' failed validation> getTriNum(NA)
%!error <'n' failed validation> getTriNum([1 1])
%!error <'n' failed validation> getTriNum(-1)
%!error <'n' failed validation> getTriNum(1.5)
%
% Unit test - return values
%!assert(getTriNum(0), 0)
%!assert(getTriNum(3), 6)
