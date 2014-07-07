Hi,
Here's my submission for the PTC linearisation problem.
I took an analytical approach - finding the "best fit" equation for the 
temperature using the characteristics in the data sheet.
To do this I typed the Temperature and R-typ values into LibreOffice Calc (file 
enclosed: PTC-characteristics.ods). I then converted the temperatures into 
degrees Kelvin and plotted them. LibreOffice has a trendline feature that fits 
the best line for different sorts of data. It will also tell you the equation it 
discovers for this fit.
I used a power law and got the equation Resistance = 0.001882748 * (Temperature 
(Kelvin) ** 2.3144273215)
When rearranged to calculate the temperature I was able to write the following 
Perl script (enclosed: ptc.pl):
*#!/usr/bin/perl*
*# calculate the temperature of a KTY81/110 PTC from its resistance*
*$MULT=1.0/0.001882748;
$EXP=1.0/2.3144273215;*
*$res = $ARGV[0];*
*$temp= ($res * $MULT) ** $EXP;*
*printf "PTC: %4.f Ohms, Temp: %4.1f Kelvin (%3.1f Celcius)\n", $res, $temp, 
$temp-273;*
To run on a Linux box, copy the code   or save the attachment to a file and run 
it as follows:
perl ptc.pl RESISTANCE
and it will print out the calculated temperature.
Example:
$ perl ./ptc.pl 1209
Resistance: 1209 Ohms, Temperature: 323.1 Kelvin (50.1 Celcius)
The accuracy of the calculation is within 1% over the temperature range given 
and within 0.5% up to 140 Celcius.
This accuracy is better than the Min-Max resistance variation of the device.
with regards
Peter Lynch
p.s. all information herein is offered freely and with no guarantees whatsoever.
