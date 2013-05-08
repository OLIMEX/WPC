#include <stdio.h>

unsigned long 
calc_posb(unsigned long stairs) {
	if(stairs > 2) {
		return (calc_posb(stairs-2) + calc_posb(stairs-1));
	}
	else {
		return stairs;
	}
}

int 
main ( int argc, char *argv[] ) {

	char input[6];
	unsigned long input_stairs;
	
	printf("How many stairs? ");
	fgets(input, 5, stdin);
	sscanf( input, "%lu", &input_stairs);

	printf("The cat has %lu opportunities facing %lu stairs", calc_posb(input_stairs), input_stairs);

	return 1;
}
