#!/usr/bin/perl

# calculate the temperature of a KTY81/110 PTC from its resistance

$MULT=1.0/0.001882748;
$EXP=1.0/2.3144273215;

$res = $ARGV[0];

$temp= ($res * $MULT) ** $EXP;

printf "PTC: %4.f Ohms, Temp: %4.1f Kelvin (%3.1f Celcius)\n", $res, $temp, $temp-273;
