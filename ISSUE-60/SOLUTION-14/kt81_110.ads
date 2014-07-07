package Kt81_110 is

   subtype Temperature is Float range -55.0 .. +150.0;
   subtype Sensor_Resistance is Float range 490.0 .. 2211.0;

   function Convert (R : Sensor_Resistance) return Temperature;

end Kt81_110;
