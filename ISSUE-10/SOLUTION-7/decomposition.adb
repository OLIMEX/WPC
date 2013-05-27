with Generic_Rational;
with Ada.Text_IO;

procedure Decomposition is
   package RationalInteger is new Generic_Rational(Integer);
   use RationalInteger;
   subtype LoopRange is Integer range 1 .. 100;
   NotFoundException : exception;

-- *************************
-- You can change input A and B here
   InputA : Integer := 6;
   InputB : Integer := 7;
-- *************************

   RationalNumber : Rational := InputA / InputB;
   ResultArray : array (1 .. 100) of Integer := (others => 0);
   LoopIndex: LoopRange := LoopRange'First;
   ArrayCounter : Integer := 0;
begin

  while Numerator(RationalNumber) /= 1 and then 
    LoopIndex < LoopRange'Last and then
    ArrayCounter < ResultArray'Last loop
      declare
        Actual_Denom : Rational := Rational'(1 / LoopIndex);
      begin 
        if Actual_Denom < RationalNumber then
          ArrayCounter := ArrayCounter + 1;
          ResultArray(ArrayCounter) := LoopIndex;
          RationalNumber := RationalNumber - Actual_Denom;
        end if;
        LoopIndex := LoopIndex + 1;  
      end;
  end loop;
        
  if Numerator(RationalNumber) = 1 then -- we got the last one
    ArrayCounter := ArrayCounter + 1;
    ResultArray(ArrayCounter) := Denominator(RationalNumber);
  else
    raise NotFoundException;
  end if;            

-- just print out results
  for Index in 1 .. ArrayCounter loop
    Ada.Text_IO.Put(Integer'Image(ResultArray(Index)));
    if Index <= ArrayCounter - 1 then
      Ada.Text_IO.Put(",");
    else
      Ada.Text_IO.New_Line;
    end if;
  end loop;

  Exception 
    when NotFoundException => Ada.Text_IO.Put_Line("More then 100 elements, increase range in source.");
    when others => Ada.Text_IO.Put_Line("Some exception raised"); 

end Decomposition;
