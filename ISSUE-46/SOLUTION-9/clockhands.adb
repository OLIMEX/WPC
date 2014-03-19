with Ada.Text_IO;
with Ada.Float_Text_IO;
with Ada.Integer_Text_IO;
use Ada.Text_IO;
use Ada.Float_Text_IO;
use Ada.Integer_Text_IO;

procedure ClockHands is
  minute : float;
  multiplier : constant float := 60.0000 / 11.0000;
  -- from 30h+(1/2)m = 6m
begin
  Put_Line("   0:0.00");
  for hour in 1..10 loop
    minute := multiplier * float(hour); 
    Put(Item => hour, Width => 4);
    Put(":");
    Put(Item => minute, Fore =>0, Aft =>2, Exp => 0);
    New_Line;
  end loop;
  Put_Line("  12:00.00");
end ClockHands;
