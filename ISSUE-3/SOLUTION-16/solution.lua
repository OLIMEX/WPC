--[[

The problem
--------------------------------------------------------------------------------
Let’s have N different strings/words for each word print the minimum part of it which makes it unique toward others, for example:

input:
A13-OLinuXino
iMX233-OLinuXino
MOD-PULSE
MOD-IO
<end>

result:
A13-OLinuXino -> a
iMX233-OLinuXino -> 2
MOD-PULSE -> p
MOD-IO -> -i

The solution
--------------------------------------------------------------------------------
We look for all possible substrings, but we do it smartly. Instead of comparing
strings all the time, we compare numbers and we resort to comparing strings only
when the numbers match. In other words, for each string, we keep an array called
"sum". The function that looks for the smallest unique substring starts with
strings of size 1. At this point, "sum" simply contains the ASCII values of each
char in the string. For example, if the string was "0123", "sum" will contain this:

{48, 49, 50, 51}

(side note: I really hope you're not doing UNICODE. But that's OK, since standard
Lua can't handle UNICODE anyway :) ).

Each string given as input has such a "sum" array. The algorithm will search for each
element in "sum" of the target string in all the "sum" arrays of the other strings, 
stopping as soon as it finds an unique sum. If this doesn't work for single chars,
the algorithm will start looking for solutions of size 2 and this is where things get
interesting. The "sum" array will be updated to contain the sums of two consecutive
elemnts of the string, in other words:

{ 48 + 49, 49 + 50, 50 + 51 }

If 2 chars don't work either, we get to 3 chars:

{ 48 + 49 + 50, 49 + 50 + 51 }

And finally 4 chars:

{ 48 + 49 + 50 + 51 }

In order words, the element sum[ i ] for a solution of size "s" contains the sum
of the ASCII chars of the first "s" chars in the string, starting from position "i".
It's immediately obvious that sum[ i ] for solution size "s" can be computed from the
value of sum[ i ] for solution size "s-1" by simply adding another ASCII value. The
nice part about this is that we are searching for these sums instead of comparing 
strings; only when two sums match we actually compare the strings (since having two
equal sums doesn't guarantee that the strings are indeed equal (take for example
"04" and "12")).

As another optimization, we compute the "sum" array only on demand and we cache
all the already computed sums in "all_sums" (both of these are handled by the 
"get_sums" function below). Caching is important, since succesive calls of 
"solve" will definitely try to use the same sums we computed before while searching
for unique strings.

NOTE: the program is optimized for speed, not space. With all the memoization of the
"sums" array, it can probably take quite a bit of memory. 
--]]

local args = { ... }
local sf = string.format

-- Memoization for sum array in 'all_sums' below
local all_sums = {}
local function get_sums( str2a, idx, slen )
  if all_sums[ idx ][ slen ] then return all_sums[ idx ][ slen ] end
  local prev = all_sums[ idx ][ slen - 1 ]
  local new = {}
  for i = 1, #prev - 1 do
    new[ #new + 1 ] = prev[ i ] + str2a[ idx ][ i + slen - 1 ]
  end
  all_sums[ idx ][ slen ] = new
  return new
end

local function solve( idx, strs, str2a )
  if #strs[ idx ] == 0 then return "" end
  -- "slen" is the length of the solution
  local found, slen = false, 1
  -- "ts" : "the string", the one we're currently processing
  local nstrs, ts, ts_str, crt = #strs
  while true do
    ts = get_sums( str2a, idx, slen )
    for i = 1, #ts - slen + 1 do
      s = ts[ i ] -- we look for "s" in all other strings
      ts_str, found = strs[ idx ]:sub( i, i + slen - 1 ), false
      for j = 1, nstrs do -- loop through all strings
        if j ~= idx then
          crt = get_sums( str2a, j, slen )
          for k = 1, #crt - slen + 1 do -- iterate through this string only
            if s == crt[ k ] and ts_str == strs[ j ]:sub( k, k + slen - 1 ) then
              found = true
              break
            end
          end
          if found then break end
        end
      end
      if not found then return ts_str end
    end
    -- Solution of length 'slen' not found, must increment solution size
    if slen == #strs[ idx ] then break end
    slen = slen + 1
   end
  -- No solution found
  return ""
end

-- Read input
if not args[ 1 ] then
  print( "Usage: lua solution.lua <input data>" )
  return 1
end

local f = assert( io.open( args[ 1 ], "r" ) )
local strs, maxs = {}, 0
while true do
  l = f:read( "*l" )
  if not l then break end
  strs[ #strs + 1 ] = l:lower()
  if #l > maxs then maxs = #l end
end
f:close()

if #strs == 0 then
  print "Empty input, nothing to compute. I love it when that happens."
  return 1
end

if maxs == 0 then
  print "Only empty strings on input. Everybody wins."
  return 1
end

-- Transform each string into an array of ASCII values
str2a = {}
for _, s in pairs( strs ) do
  a = {}
  for i = 1, #s do
    a[ #a + 1 ] = s:byte( i, i )
  end
  str2a[ #str2a + 1 ] = a
end

-- Deep copy the above str2a array into the all_sums array
for i = 1, #strs do
  all_sums[ i ] = {}
  all_sums[ i ][ 1 ] = {}
  for j = 1, #str2a[ i ] do
    all_sums[ i ][ 1 ][ #all_sums[ i ][ 1 ] + 1 ] = str2a[ i ][ j ]
  end
end

-- Solve for each line of the input in turn
local fstr = sf( "%%-%ds -> %%s", maxs + 1 )
for i = 1, #strs do
  res = solve( i, strs, str2a )
  print( sf( fstr, strs[ i ], #res > 0 and res or "(no solution)" ) )
end

