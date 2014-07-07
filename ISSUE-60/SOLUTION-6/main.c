#include <stdio.h>
#include <math.h>

/*
 * Olimex WPC # 60 - PTC linearization
 *
 */

// Simulate a resistance value being returned by MCU
double get_resistance()
{
	static double value = 440;
	return value += 25;
}

// Use a polynomal (see Sage worksheet) to determine temperature
double polynomal(double R)
{
	double l = log(R);
	return     7.589469715260443 * l*l*l + 
	        -131.583894632367670 * l*l + 
	         858.112369335528800 * l + 
	       -2125.510302051728600;
}

// Use a lookup table to determine temperature
double r_lut[] = { 490, 515, 567, 624, 684, 747, 815, 886, 961, 1000, 1040, 1122, 1209, 
			      1299, 1392, 1490, 1591, 1696, 1805, 1915, 1970, 2023, 2124, 2211};
					 
double t_lut[] = {-55, -50, -40, -30, -20, -10, 0, 10, 20, 25, 30, 40,
				   50, 60, 70, 80, 90, 100, 110, 120, 125, 130, 140, 150};

double lookup(double R)
{	
	// Lookup with linear interpolation
	int i = 0;
	while (i < sizeof(r_lut)/sizeof(int) - 1)
	{
		if ((R >= r_lut[i]) && (R <= r_lut[i+1])) 
		{
			double delta_temp = t_lut[i+1] - t_lut[i];
			double fraction = (R - r_lut[i]) / (r_lut[i+1] - r_lut[i]); 
			return t_lut[i] + (delta_temp * fraction); 
		}
		i++;
	}  
	
	// (Inaccurate) fallback for resistances out of LUT range
	return 0.118 * R - 99.64;
}

int main (int argc, char *argv[])
{
	double resistance;
	double temp_poly;
	double temp_lut;
		
	while(resistance < 2300)
	{
		resistance = get_resistance();
		temp_poly = polynomal(resistance);
		temp_lut = lookup(resistance);
		printf ("%.0f ohm = %.2f C, %.2f C\n", resistance, temp_poly, temp_lut);	
	}
	return 0;
}

