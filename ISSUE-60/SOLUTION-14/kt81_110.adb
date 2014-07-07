package body Kt81_110 is

   type Rt_Pair is record
      T : Temperature;
      R : Sensor_Resistance;
   end record;

   type Value_Table is array (Positive range <>) of Rt_Pair;

   Conv_Data : constant Value_Table :=
     ((-55.0,  490.0),
      (-50.0,  515.0),
      (-40.0,  567.0),
      (-30.0,  624.0),
      (-20.0,  684.0),
      (-10.0,  747.0),
      (  0.0,  815.0),
      ( 10.0,  886.0),
      ( 20.0,  961.0),
      ( 25.0, 1000.0),
      ( 30.0, 1040.0),
      ( 40.0, 1122.0),
      ( 50.0, 1209.0),
      ( 60.0, 1299.0),
      ( 70.0, 1392.0),
      ( 80.0, 1490.0),
      ( 90.0, 1591.0),
      (100.0, 1696.0),
      (110.0, 1805.0),
      (120.0, 1915.0),
      (125.0, 1970.0),
      (130.0, 2023.0),
      (140.0, 2124.0),
      (150.0, 2211.0));

   --  Gradient is an array containing the gradient between two known
   --  values.  On a micro processor this would be calculated before
   --  compile time, not at run time.  Conceptually this is a
   --  constant.
   Gradient : array (Conv_Data'Range) of Float;


   function Convert (R : Sensor_Resistance) return Temperature
   is
      Pos : Positive; -- index into the table of values
   begin
      -- find next higher index
      Pos := 1;
      while Conv_Data(Pos).R <= R loop
         Pos := Pos + 1;
      end loop;

      -- linear interpolation between next and previous value
      return Conv_Data(Pos-1).T + (R - Conv_Data(Pos-1).R) * Gradient(Pos);
   end Convert;


   procedure Set_Up_Gradients is
   begin
      for I in 2 .. Gradient'Last loop
         Gradient(I) := (Conv_Data(I).T - Conv_Data(I-1).T) /
           (Conv_Data(I).R - Conv_Data(I-1).R);
      end loop;
      -- special case for the first entry.  We don't have a previous
      -- value, so we assume the same gradient as in the next
      -- interval.
      Gradient(1) := Gradient(2);
   end Set_Up_Gradients;

begin
   Set_Up_Gradients;
end Kt81_110;
