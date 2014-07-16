
file for WPC #61

best regards
    Rolf


-----result.log-------------
F:\Devel\Ada\olimex_wpc61>permute_figures.exe
1 + 2 + 3 - 4 + 5 + 6 + 78 + 9 = 100
1 + 2 + 34 - 5 + 67 - 8 + 9 = 100
1 + 23 - 4 + 5 + 6 + 78 - 9 = 100
1 + 23 - 4 + 56 + 7 + 8 + 9 = 100
12 + 3 + 4 + 5 - 6 - 7 + 89 = 100
12 + 3 - 4 + 5 + 67 + 8 + 9 = 100
12 - 3 - 4 + 5 - 6 + 7 + 89 = 100
123 + 4 - 5 + 67 - 89 = 100
123 + 45 - 67 + 8 - 9 = 100
123 - 4 - 5 - 6 - 7 + 8 - 9 = 100
123 - 45 - 67 + 89 = 100
found 11 solutions.
-----permute_figures.adb-------------
with Ada.Text_IO;
with Ada.Integer_Text_IO;

procedure Permute_Figures is

   type Operator is ('+', '-', '*');
   function Image (O : Operator) return String;

   subtype Op_Position is Integer range 1 .. 8;
   subtype Val_Position is Integer range 1 .. 9;

   type Val_Array is array (Val_Position range <>) of Integer;
   Values : Val_Array (Val_Position) := (others => 0);
   Init_Values : constant Val_Array := (1, 2, 3, 4, 5, 6, 7, 8, 9);

   type Op_Array is array (Op_Position range <>) of Operator;

   function Image (Left : String; Right : Op_Array) return String;
   function Image (Ops : Op_Array) return String;

   function Image (V : Integer) return String;


   --------------------
   --
   -- subroutine bodies
   --
   --------------------

   function Eval (Text : String) return Integer
   is
      use Ada.Integer_Text_Io;

      Val : Integer;
      Read_Int : Integer;
      Read_Op  : Character;
      Idx : Natural := Text'First; -- Last read character position in the input string
   begin
      Get (Text(Idx .. Text'Last), Val, Idx);
      Idx := Idx + 2; -- skip the blank char
      while Idx < Text'Last loop
         Read_Op := Text(Idx);                           Idx := Idx + 2;
         Get (Text(Idx .. Text'Last), Read_Int, Idx);    Idx := Idx + 2;
         case Read_Op is
            when '+' => Val := Val + Read_Int;
            when '-' => Val := Val - Read_Int;
            when others => raise Constraint_Error;
            -- this should not happen after evaluating all mults in
            -- the string processing loop
         end case;
      end loop;
      return Val;
   end Eval;


   function Image (O : Operator) return String is
   begin
      case O is
         when '+' => return " + ";
         when '-' => return " - ";
         when '*' => return "";
      end case;
   end Image;


   function Image (Left : String; Right : Op_Array) return String is
   begin
      if Right'Length = 0 then
         return Left;
      else
      Recurse:
         declare
            Pos  : constant Op_Position := Right'First;
            Last : constant Op_Position := Right'Last;
            Op   : constant Operator := Right(Pos);
            Result : constant String := Left & Image (Op) & Image (Init_Values(Pos+1));
         begin
            return Image (Result, Op_Array'(Right(Pos+1 .. Last)));
         end Recurse;
      end if;
   end Image;


   function Image (Ops : Op_Array) return String
   is
   begin
      return Image ("1", Ops);
   end Image;


   function Image (V : Integer) return String
   is
      V_Str : constant String := Integer'Image(V);
   begin
      if V < 0 then
         return V_Str;
      else
         return V_Str(2..V_Str'Last);
      end if;
   end Image;


----

   T : Op_Array (Op_Position'Range);
   V : Integer;
   Solutions : Natural := 0;
   use Ada.Text_IO;

begin -- Main
Pos1: for O in Operator'Range loop
      T(1) := O;
   Pos2: for O in Operator'Range loop
         T(2) := O;
      Pos3: for O in Operator'Range loop
            T(3) := O;
         Pos4: for O in Operator'Range loop
               T(4) := O;
            Pos5: for O in Operator'Range loop
                  T(5) := O;
               Pos6: for O in Operator'Range loop
                     T(6) := O;
                  Pos7: for O in Operator'Range loop
                        T(7) := O;
                     Pos8: for O in Operator'Range loop
                           T(8) := O;
                           V := Eval (Image(T));
                           if V = 100 then
                              Solutions := Solutions + 1;
                              Put_Line (Image(T) & " = " & Image(V));
                           end if;
                        end loop Pos8;
                     end loop Pos7;
                  end loop Pos6;
               end loop Pos5;
            end loop Pos4;
         end loop Pos3;
      end loop Pos2;
   end loop Pos1;
   Put_Line ("found " & Image(Solutions) & " solutions.");
end Permute_Figures;


