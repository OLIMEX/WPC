with Ada.Text_IO;
with Ada.Integer_Text_IO;

procedure TrianglePoints is
-- Objective: find out if A, B, C points are placed clockwise 
-- or counterclockwise or on same line
-- Solution: based on y = mx + b equation
-- by comparing calculated and provided Cy
-- by comparing Ax and Bx to find order


Precision : constant := 1.0 / 1000.0;

type FixedPoint is delta precision digits 16;

type Point is 
  record
    x : FixedPoint;
    y : FixedPoint;
  end record;

type ResultTypes is (NoResult, SameLine, SamePoints, CW, CCW);

type PLetters is (A, B, C);

type PointArray is array(PLetters) of Point;

AllPoints : PointArray;
Slope : FixedPoint;
Shift : FixedPoint;
YNew : FixedPoint;
Result : ResultTypes;
Calculation: Boolean;

  procedure GetPoints is
    temp: Integer;
  begin
    for rec in PLetters'Range loop
      loop
          begin
            Ada.Text_IO.Put_Line("Please enter x for point " & PLetters'Image(rec) & ":");
            Ada.Integer_Text_IO.Get(temp);
            AllPoints(rec).x := FixedPoint(temp);
            exit;
          exception
            when others =>
                Ada.Text_IO.Put_Line("Invalid input");
                Ada.Text_IO.Skip_Line;
          end; 
      end loop;
      loop
          begin
            Ada.Text_IO.Put_Line("Please enter y for point " & PLetters'Image(rec) & ":");
            Ada.Integer_Text_IO.Get(temp);
            AllPoints(rec).y := FixedPoint(temp);
            exit;
          exception
            when others =>
                Ada.Text_IO.Put_Line("Invalid input");
                Ada.Text_IO.Skip_Line;
          end; 
      end loop;
    end loop;
  end GetPoints;

  procedure CalculateSlope is
  begin
    Slope :=  (AllPoints(B).y - AllPoints(A).y) / (AllPoints(B).x - AllPoints(A).x); 
  end CalculateSlope;

  procedure CalculateShift is
  begin
    Shift := AllPoints(B).y - AllPoints(B).x * Slope;
  end CalculateShift;

  procedure CalculateNewY is
  begin
    YNew := Shift + AllPoints(C).x * Slope;
  end CalculateNewY;

  function AreIdenticalPoints return Boolean is
    function IsEqual (p1: Point; p2: Point) return Boolean is
    begin
      return p1.x = p2.x and then p1.y = p2.y; 
    end IsEqual;
  begin
    return IsEqual(AllPoints(A), AllPoints(B)) or else
           IsEqual(AllPoints(A), AllPoints(C))  or else
           IsEqual(AllPoints(B), AllPoints(C));
  end AreIdenticalPoints;

  procedure EvaluateVertical is
  begin
-- No equation calculation done
    if AllPoints(A).x = AllPoints(B).x then
      if AllPoints(C).x = AllPoints(B).x then
         Result := SameLine;
      elsif AllPoints(A).y < AllPoints(B).y then
        if AllPoints(C).x > AllPoints(B).x then
          Result := CW; 
        else
          Result := CCW;
        end if;
      elsif AllPoints(A).y > AllPoints(B).y then
        if AllPoints(C).x < AllPoints(B).x then
          Result := CW; 
        else
          Result := CCW;
        end if;
      end if;
    end if;    
  end EvaluateVertical;

  procedure EvaluateNotVertical is
  begin
    if AllPoints(C).y = YNew then
      Result := SameLine;
    elsif AllPoints(A).x < AllPoints(B).x then
      if AllPoints(C).y < YNew then
        Result := CW;
      else
        Result := CCW;
      end if;
    elsif AllPoints(A).x > AllPoints(B).x then
      if AllPoints(C).y > YNew then
        Result := CW;
      else
        Result := CCW;
      end if;
    end if;
  end EvaluateNotVertical;
  
  procedure CalculateResults is
  begin
    if AreIdenticalPoints then
      Result := SamePoints;
    else
      EvaluateVertical;
    end if;
    if Result = NoResult then
      CalculateSlope;
      CalculateShift;
      CalculateNewY;
      Calculation := True;
      EvaluateNotVertical;
    end if;
  end CalculateResults;
  
  procedure DemoData (ax,ay,bx,by,cx,cy : Integer) is
  begin
    AllPoints(A).x := FixedPoint(ax); 
    AllPoints(A).y := FixedPoint(ay); 
    AllPoints(B).x := FixedPoint(bx); 
    AllPoints(B).y := FixedPoint(by); 
    AllPoints(C).x := FixedPoint(cx); 
    AllPoints(C).y := FixedPoint(cy); 
  end DemoData;

  procedure WriteOutput is
  begin
    for p in PLetters loop
      Ada.Text_IO.Put_Line(PLetters'Image(p) & ":" 
                & FixedPoint'Image(AllPoints(p).x) & ", "
                & FixedPoint'Image(AllPoints(p).y)); 
    end loop;
    Ada.Text_IO.Put_Line("Result = " & ResultTypes'Image(Result));
    if Calculation = True then
      Ada.Text_IO.Put_Line("Slope = " & FixedPoint'Image(Slope));
      Ada.Text_IO.Put_Line("Shift = " & FixedPoint'Image(Shift));
      if Slope = 1.0 then
        Ada.Text_IO.Put_Line("Used equatation: y - x" 
                          & " =" & FixedPoint'Image(Shift));
      elsif Slope /= 0.0 then
        Ada.Text_IO.Put_Line("Used equatation: y - x *" & FixedPoint'Image(Slope) 
                            & " =" & FixedPoint'Image(Shift));
      else
        Ada.Text_IO.Put_Line("Used equatation: y = " & FixedPoint'Image(Shift));
      end if;
    end if;
  end WriteOutput;

  procedure Initialize is
  begin
    Result := NoResult;
    Slope := 0.0;
    YNew := 0.0;
    Shift := 0.0;
    Calculation := False;
  end Initialize;
 

begin
  --GetPoints;
  Initialize;
  DemoData (5,-2, 4,-4, 4,-2);
  CalculateResults;
  WriteOutput;
end TrianglePoints;



