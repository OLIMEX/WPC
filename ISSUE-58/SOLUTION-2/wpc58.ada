
-- Problem:

-- Make code which enters Gregorian calendar date in format:
-- Day/Month/Year and calculates how many seconds passed since the
-- beginning.

with Ada.Text_IO;                  use Ada.Text_IO;
with Ada.Integer_Text_IO;          use Ada.Integer_Text_IO;
with Ada.Calendar;                 use Ada.Calendar;
with Ada.Command_Line;             use Ada.Command_Line;

procedure Secs_Since_Beginning is

   Beginning : constant Time := Time_Of (Year    => 1970,
                                         Month   => 1,
                                         Day     => 1,
                                         Seconds => 0.0);

   Now         : Time;
   Secs_Passed : Duration;

   Invalid_Date : exception;

   -- parse the input string and return a time value
   function Value (Date : String) return Time
   is
      Mon : Month_Number;
      Year: Year_Number;
      Day : Day_Number;
      -- string indices
      S   : Positive := Date'First;
      E   : Positive := Date'Last;
   begin
      Get (From => Date(S..E), Item => Day, Last => S);
      S := S+2;
      Get (From => Date(S..E), Item => Mon, Last => S);
      S := S+2;
      Get (From => Date(S..E), Item => Year, Last => S);
      return Time_Of (Year => Year,
                      Month => Mon,
                      Day  => Day,
                      Seconds => 0.0);
   exception
      when Error: others =>
         raise Invalid_Date;
   end Value;

begin
   if Argument_Count /= 1 then
      raise Invalid_Date;
   end if;

   Now := Value (Argument (1));
   Secs_Passed := Now - Beginning;

   Put ("Seconds since the beginning (1970-01-01 00:00):");
   Put (Duration'Image (Secs_Passed));
   New_Line;
end Secs_Since_Beginning;



