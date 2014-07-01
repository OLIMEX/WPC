
--  WPC #59, 2014-06-29
--  Make code which detects on what machine is ran – with
--  Big or Little Endian.

with System;                       use System;
with Ada.Text_IO;                  use Ada.Text_IO;

procedure Endianness is
begin
   if Default_Bit_Order = Low_Order_First then
      Put_Line ("little endian");
   else
      Put_Line ("big endian");
   end if;
end Endianness;


