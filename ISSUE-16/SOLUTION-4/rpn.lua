--[[
Usage: lua rpn.lua "expression"
For example:

> lua rpn.lua '(((3+6)*(2-4))+7)'
'(((3+6)*(2-4))+7)' => 3 6 + 2 4 - * 7 +

Will raise an error if the expression is invalid
--]]

local sf = string.format
local args = { ... }

local prilist, crtpri, rpn = {}, 0, {}
local lexer_data, lexer_pos, lexer_last

-- Lexer
function lexer_init( s )
  lexer_data, lexer_pos, lexer_last = s, 1, #s
end

function _isdigit( s )
  return #s == 1 and s:byte( 1 ) >= string.byte( "0", 1 ) and s:byte( 1 ) <= string.byte( "9", 1 )
end

function lexer_get_token()
  local token = ''
  if lexer_next then 
    t, lexer_next = lexer_next, nil
    return t
  end
  if lexer_pos > lexer_last then return "" end
  crt = lexer_data:sub( lexer_pos, lexer_pos )
  if crt == '+' or crt == '-' or crt == '*' or crt == '/' or crt == '(' or crt == ')' then
    lexer_pos = lexer_pos + 1
    return crt
  elseif _isdigit( crt ) then
    token = ''
    repeat
      token = token .. crt
      lexer_pos = lexer_pos + 1
      crt = lexer_data:sub( lexer_pos, lexer_pos )
    until lexer_pos > lexer_last or not _isdigit( crt )
    return tonumber( token )
  end
end

function lexer_push_back( t )
  lexer_next = t
end

-- Parser
function parse_expr( s )
  s = s:gsub( '%s+', ''):gsub( '"', "" ):gsub( "'", "" )
  if #s == 0 then error( "empty expression" ) end
  lexer_init( s )
  parse_e()
end

function _match_eps( t )
  lexer_push_back( t )
  if lexer_get_token() ~= "" then error( "invalid expression" ) end
end

function parse_e()
  parse_t()
  parse_e1()
end

function parse_e1()
  local t = lexer_get_token()
  if t == '+' or t == '-' then
    prilist[ #prilist + 1 ] = { t, crtpri + 1 }
    parse_t()
    parse_e1()
  else
    lexer_push_back( t )
  end
end

function parse_t()
  parse_f()
  parse_t1()
end

function parse_t1()
  local t = lexer_get_token()
  if t == '*' or t == '/' then
    prilist[ #prilist + 1 ] = { t, crtpri + 3 }
    parse_f()
    parse_t1()
  else
    lexer_push_back( t )
  end
end

function parse_f()
  local t = lexer_get_token()
  if t == '-' then
    t = lexer_get_token()
    if type( t ) ~= "number" then error( "invalid expression" ) end
    prilist[ #prilist + 1 ] = { '-' .. t }
  elseif type( t ) ~= "number" then
    if t ~= '(' then error( "invalid expression" ) end
    crtpri = crtpri + 20
    parse_e()
    if lexer_get_token() ~= ')' then error( "invalid expression" ) end
    crtpri = crtpri - 20
  else
    prilist[ #prilist + 1 ] = { t }
  end
end

function generate( a, l, r )
  local l, r, lvl = l or 1, r or #a, lvl or 1
  if l > r or l < 1 or r > #a then return end
  if l == r then rpn[ #rpn + 1 ] = a[ l ][ 1 ] end
  local min, minpos = 0xFFFFFFFF, l
  for i = l + 1, r do
    if a[ i ][ 2 ] and a[ i ][ 2 ] < min then min, minpos = a[ i ][ 2 ], i end
  end
  if min == 0xFFFFFFFF then return end
  rpn[ #rpn + 1 ] = a[ minpos ][ 1 ]
  generate( a, minpos + 1, r )
  generate( a, l, minpos - 1 )
end

if not args[ 1 ] then
  print ( 'Usage: lua rpn.lua "expression"' )
  return 1
end
parse_expr( args[ 1 ] )
if #prilist == 1 then
  print( sf( '%s => %s', args[ 1 ], args[ 1 ] ) )
else
  generate( prilist )
  io.write( sf( '%s => ', args[ 1 ] ) )
  for i = #rpn, 1, -1 do io.write( sf( '%s ', tostring( rpn[ i ] ) ) ) end
  print ""
end

