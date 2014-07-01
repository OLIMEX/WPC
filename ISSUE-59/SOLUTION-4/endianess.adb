with Ada.Text_IO;

procedure Endianess is
  a : Integer;
  p : Character;
  for p'Address use a'Address;
begin
  a := 1;
  if (Character'Pos(p) = 1) then
    Ada.Text_IO.Put_Line("Little endian");
  else
    Ada.Text_IO.Put_Line("Big endian");
  end if;
end Endianess;
