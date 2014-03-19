/*
 *
 * Olimex WPC # 46 - Clock hands
 *
 */

#include <stdio.h>
#include <math.h>

int main (int argc, char *argv[])
{
	
	double overlap_time;
	
	int loop = 0;
	int hours;
	int minutes;
	int seconds;

	printf("\n");	

	while (hours < 12)
	{
		overlap_time = (720.0/11.0) * loop;
		hours = floor(overlap_time / 60);
		minutes = floor(overlap_time - (hours * 60));
		seconds = floor((overlap_time - trunc(overlap_time)) * 60);
		printf("%02d:%02d:%02d\n", hours, minutes, seconds);		
		loop++;
	}

	printf("\nClock hands crossed %d (or %d if you don't count the last one) times in a 12 hour period.\n\n", loop, loop-1); 
		
	return 0;
}

