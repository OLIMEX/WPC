program plus_min;

uses SysUtils;

const powers: array[0..9] of cardinal = (1, 10, 100, 1000, 10000,
                                        100000, 1000000, 10000000,
                                        100000000, 1000000000);

var history: array[1..9] of char;
	idx: integer;

// Convert the performed operations into a readable string
function HistoryToString: string;
var
  r, s: string;
  i, j: integer;
begin
  s := '';
  r := '';
  // Mix operations and digits
  for i := 1 to 9 do
    begin
      s := s + history[i] + IntToStr(i);
    end;
  // Replace a vertical bar with the + or - sign that follows it
  for i := 1 to length(s) do
     begin
       if s[i] = '|' then
         begin
           for j := i + 1 to length(s) do
              begin
                if (s[j] = '+') or (s[j] = '-') then
                  begin
                    s[i] := s[j];
                    s[j] := ' ';
                    break;
                  end
                else
                  begin
                    if s[j] = '|'
                      then s[j] := ' ';
                  end;
              end;
         end;
     end;
   // Adjust spacing
   for i := 1 to length(s) do
      begin
       if s[i] = '+' then
          begin
           if i <> 1 then r := r + ' + ';
          end
       else if s[i] = '-' then
          begin
            if i <> 1 then
              r := r + ' - '
            else
              r := r + '- ';
          end
       else if s[i] <> ' ' then
            r := r + s[i];
      end;
  HistoryToString := r;
end;

// Recursivly test possible combinations
procedure Recurse(parent, power, pow_sum, subsum: integer);
var me, me_pow : integer;
begin
  // If the previous digit was a 9 then check the sum
  // and print the result if it equals 100
  if parent = 9 then
    begin
      if (subsum = 100) then
        Writeln(HistoryToString, ' = ', subsum);
      exit;
    end;

  // Try the next digit
  me := parent + 1;

  // If this digit is not part of a longer number
  if (power = 0) then
    begin
      // then try adding it to what we have so far
      history[me] := '+';
      Recurse(me, 0, 0, subsum + me);
      // and try subtracting it
      history[me] := '-';
      Recurse(me, 0, 0, subsum - me);
      // as well as combining it with the next digits 
      // into a longer number
      for me_pow := 1 to 9 - me do
        begin
          history[me] := '|';
          Recurse(me, me_pow, me * powers[me_pow], subsum);
        end;
    end
  // otherwise, tack this digit onto the back of the longer number
  else
    begin
      me_pow := power - 1;
	  // If this is the last digit in the longer number
      if (me_pow = 0) then
        begin
		  // then try adding the longer number to what we have so far
          history[me] := '+';
          Recurse(me, me_pow, 0, subsum + pow_sum + me);
          // and try subtracting it
          history[me] := '-';
          Recurse(me, me_pow, 0, subsum - pow_sum - me);
        end
      // otherwise, tack it onto the back of the longer number and continue
      else
       begin
         history[me] := '|';
         Recurse(me, me_pow, pow_sum + (me * powers[me_pow]), subsum);
       end;
    end;
end;

begin
  for idx := 1 to 9 do history[idx] := char(32);
  Recurse(0,0,0,0);
end.
