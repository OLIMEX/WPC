/*
 2014-07-06 by kantal59 
 License: LGPL
 OLIMEX WPC#60: PTC linearization
			KTY81/110 is non linear resistor which increases it’s value with temperature. 
			You can read the datasheet here: http://www.nxp.com/documents/data_sheet/KTY81_SER.pdf
 			Make code which input KTY81/110 real number of resistance in ohms and output the temperature of the sensor.

 			Resources: see my Python solution kty.py!
 			
 			Compile: gcc -o kty kty.c
*/


#include <stdio.h>
#include <stdlib.h>
#include "kty.h"


float get_temperature( float fohm,	const rtdata_t  *pdata)
{

	unsigned int ohm,i,index,r1,r2;
	int t1,t2;
	size_t size= pdata->len;
	const restemp_t* ptbl= pdata->ptbl;
	
	ohm= fohm*100;
	if( ohm < ptbl[0].res ||  ohm > ptbl[ size-1].res )		return( INVTEMPR);		// invalid input resistance value yields invalid temperature
	
	for( i=0;	i< size;	i++){
	
		if( ptbl[i].res > ohm ) break;
		index= i;
	}

	if( ohm == ptbl[index].res  )	return( (float)ptbl[index].temp / 100 );
	
	r1= ptbl[index].res;	t1= ptbl[index].temp;
	r2= ptbl[index+1].res;	t2= ptbl[index+1].temp;
	
	return( ( (float)t1 + (float)((t2-t1)*(ohm-r1))/(r2-r1)  ) / 100 );

}


int main( int argc, char *argv[]){

	
	if( argc<2 ){ 
					puts(" Usage: $ ./kty.py  resistance1 resistance2 ...\n  where the values are in Ohms");
					return(1);
	}	
	
	int i;			
	for( i=1; i< argc; i++){
		
		float res= strtof( argv[i],NULL);	puts( argv[i]);
		float temp= get_temperature( res, &data_kty81_110);
		if( temp == INVTEMPR )		printf( " %.2f Ohms\tNA\n", res );
		else						printf( " %.2f Ohms\t%.2f\n", res,temp );
			
	}
		
	return(0);
}

