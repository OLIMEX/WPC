with Ada.Text_IO;                  use Ada.Text_IO;
with Ada.Float_Text_Io;
with Ada.Command_Line;
with KT81_110;

procedure PTC_Linearization is
   use Ada.Command_Line;
   use Ada.Float_Text_Io;
   use Kt81_110;

   Range_Str : constant String := ("(real number in the range 490.0 .. 2211.0)");
   T : Temperature;
   R : Sensor_Resistance;
   L : Positive;

   Short_Output : Boolean := False;

begin
   if Argument_Count /= 1 then
      raise Constraint_Error;
   end if;

   -- convert string argument into a float value
   Ada.Float_Text_Io.Get (Argument(1), R, L); -- might raise out of range

   T := Convert (R);

   Put ("resulting temperature for input resistance");
   Put (R, Fore => 5, Aft => 1, Exp => 0);
   Put ("Ohm is ");

   Put (T, Fore => 5, Aft => 1, Exp => 0);

   Put ("C");
   New_Line;

exception
   when others =>
      Put_Line ("ptc_linearization resistance " & Range_Str);
      Set_Exit_Status (Failure);

end PTC_Linearization;
