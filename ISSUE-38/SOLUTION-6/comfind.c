/* 	Centre of mass calculator. Input file is a csv instead of an image
	(this also has the advantage of allowing the magnitude of mass at
	each point to be specified). Output is relative to the top left 
	corner of the file (technically the y value should be negative
	as this represents the second quadrant of a graph (since (0,0) is
	at top left point, not bottom left).
	
	The csv was generated from the png using:
	http://www.cemetech.net/projects/basicelite/sourcecoder2.php
	Data is taken from the 8-Bit (256-Shade) Color array, imported into
	excel, and then saved as csv.
*/
#include <stdio.h>
#include <stdlib.h>

#define DELIMITER ','

int help() {
	printf("\nProgram to calculate centre of mass. \n");
	printf("Input should be a csv file with mass data at particular points. \n");
	printf("Make sure the csv has a newline at the end of the file \n");
	printf("and no commas at the end of each line. \n");
	printf("\nUsage: \n");
	printf("comfind inputfile \n");
	return(0);
}

//Get file dimensions before creating pointer arrays
void getDim(FILE *infp, int *x_dim, int *y_dim) {
	char byte;

	//Dimensions are returned through function pointers
	while(!feof(infp)) {
		if (byte = fgetc(infp), (*x_dim == 0) && (byte == DELIMITER)) {
			++*y_dim;
			continue;
		}
		if (byte == '\n') {
			if (*x_dim == 0) {
				++*y_dim;
			}
			++*x_dim;
		}
	}
	rewind(infp);
}

void arrayGen2d(FILE *infp, int x_dim, int y_dim, float ***inputData) {
	int x;
	
	//Dynamically generated pointer arrays, using dimensions gathered from file
	*inputData = (float **)calloc(x_dim,sizeof(float *));
	
	for (x = 0; x < x_dim; x++) {
		(*inputData)[x] = (float *)calloc(y_dim,sizeof(float));
	}
}

void arrayGen1d(int a_max, float **a_total) {
	*a_total = (float *)malloc(sizeof(float)*a_max);
}

void importData(FILE *infp, int x_dim, int y_dim, float **inputData) {
	int x, y;
	char tmpchar;
	float tmpdata;
	
	//Data is returned by a function pointer
	for (x = 0; x < x_dim; x++) {
		for (y = 0; y < y_dim; y++) {
			if(fscanf(infp,"%f%c", &tmpdata, &tmpchar) != EOF) {
				inputData[x][y] = tmpdata;
			}
		}
	}
}

float getCOM(float **inputData, float *a_total, int a_max, int b_max, int invert, float *totalMass) {
	int a, b;
	//floats to store mass*displacement and just mass
	float mx = 0.0F, m = 0.0F, tempfloat;
	
	for (a = 0; a < a_max; a++) {
		tempfloat = 0.0F;
		for (b = 0; b < b_max; b++) {
			//use invert to switch rows and cols when calculating x coords 
			if(invert) {
				tempfloat += inputData[b][a];
			}
			else tempfloat += inputData[a][b];
		}
		a_total[a] = tempfloat;
	}
	
	//implementation of the formula (m1*x1 + m2*x2 ...) / (m1 + m2 ...)
	for (a = 0; a < a_max; a++) {
		mx += (a_total[a]*a);
		m += (a_total[a]);
	}
	
	*totalMass = m;
	return(mx/m);
}
		
int main(int argc, char *argv[])
{
	int IN_FNAME_ARG = 0, arglevel, x_dim = 0, y_dim = 0;
	float **inputData, *x_totals, *y_totals, totalMass;
	
	if(argc == 1) 
		return help();
		
	//argument handler	
	for(arglevel = 1; arglevel < argc; arglevel++) {
		if (!IN_FNAME_ARG)
			IN_FNAME_ARG = arglevel;
	}
	
	FILE *infp;
	infp = fopen(argv[IN_FNAME_ARG],"r");
	
	if(infp == NULL) {
		printf("Error: Invalid input file name, file does not exist or does not have read permissions \n %s\n", argv[IN_FNAME_ARG]);
		return(1);
	}
	
	getDim(infp,&x_dim,&y_dim);
	arrayGen2d(infp,x_dim,y_dim,&inputData);
	arrayGen1d(x_dim,&x_totals);
	arrayGen1d(y_dim,&y_totals);
	importData(infp,x_dim,y_dim,inputData);
	
	printf("Centre of mass X coords: %f \n", (getCOM(inputData,y_totals,y_dim,x_dim,1,&totalMass)+1));
	printf("Centre of mass Y coords: %f \n", (getCOM(inputData,x_totals,x_dim,y_dim,0,&totalMass)+1));
	printf("Total Mass: %f \n", totalMass);
	
	return(0);
}
