/* 	Brute-forcing maze solver. Can be extremely slow on some sets of test data,
	as there are no rule based optimisations in the algorithm (only recommended for
	small or simple data sizes!). Input should be a csv file with spaces indicating
	white space, and any character other than a space, comma or newline to indicate
	black spaces. Output is a csv file showing numbered steps taken.
*/
#include <stdio.h>
#include <stdlib.h>

#define DELIMITER ','

int help() {
	printf("\nMaze solving program \n");
	printf("Usage: \n");
	printf("mazefind inputfile outputfile \n");
	return(0);
}

//Get file dimensions before creating pointer arrays
void getdim(FILE *infp, FILE *outfp, int *x_dim, int *y_dim) {
	char byte, delim = DELIMITER;

	while(!feof(infp)) {
		if (byte = fgetc(infp), (*x_dim == 0) && (byte == delim)) {
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

int maze(FILE *outfp, int x_dim, int y_dim, int blackcount, char **inputData, char **upMask, char **downMask, char **leftMask, char **rightMask, int **outputData) {
	int x = 0, y = 0, count = 1;
	outputData[x][y] = count;
	
	//Brute-forcing algorithm - only capable of horizontal or vertical movement, not diagonal.
	while(1) {
		if (((y < y_dim-1) && (inputData[x][y+1] == 0)) && ((outputData[x][y+1] == 0) && (downMask[x][y] == 0))) {
			outputData[x][++y] = ++count;
		}
		else if (((x < x_dim-1) && (inputData[x+1][y] == 0)) && ((outputData[x+1][y] == 0) && (rightMask[x][y] == 0))) {
			outputData[++x][y] = ++count;
		}
		else if (((y > 0) && (inputData[x][y-1] == 0)) && ((outputData[x][y-1] == 0) && (upMask[x][y] == 0))) {
			outputData[x][--y] = ++count;
		}
		else if (((x > 0) && (inputData[x-1][y] == 0)) && ((outputData[x-1][y] == 0) && (leftMask[x][y] == 0))) {
			outputData[--x][y] = ++count;
		}
		else if ((count == ((y_dim * x_dim) - (blackcount))) && ((x == 1) && (y == 0))) {
			printf("\nSolved");
			break;
		}
		else if (((x == 0) && (y == 0)) && ((rightMask[x][y] == 1) && (downMask[x][y] == 1))) {
			printf("\nUnsolvable");
			return(1);
		}
		else if ((y > 0) && (outputData[x][y-1] == (count-1))) {
			outputData[x][y] = 0;
			downMask[x][y] = 0;
			upMask[x][y] = 0;
			leftMask[x][y] = 0;
			rightMask[x][y] = 0;
			downMask[x][--y] = 1;
			--count;
		}
		else if ((x > 0) && (outputData[x-1][y] == (count-1))) {
			outputData[x][y] = 0;
			downMask[x][y] = 0;
			upMask[x][y] = 0;
			leftMask[x][y] = 0;
			rightMask[x][y] = 0;
			rightMask[--x][y] = 1;
			--count;
		}
		else if ((y < y_dim-1) && (outputData[x][y+1] == (count-1))) {
			outputData[x][y] = 0;
			downMask[x][y] = 0;
			upMask[x][y] = 0;
			leftMask[x][y] = 0;
			rightMask[x][y] = 0;
			upMask[x][++y] = 1;
			--count;
		}
		else if ((x < x_dim-1) && (outputData[x+1][y] == (count-1))) {
			outputData[x][y] = 0;
			downMask[x][y] = 0;
			upMask[x][y] = 0;
			leftMask[x][y] = 0;
			rightMask[x][y] = 0;
			leftMask[++x][y] = 1;
			--count;
		}
	}
	
	//File Output
	for (x = 0; x < x_dim; x++) {
		for (y = 0; y < y_dim; y++) {
			fprintf(outfp, "%i,", outputData[x][y]);
		}
		fprintf(outfp, "\n");
	}
	
	return(0);
}

int arraygen(FILE *infp, FILE *outfp, int x_dim, int y_dim) {
	int x, y, blackcount = 0;
	char byte, delim = DELIMITER;
	//Dynamically generated pointer arrays, using dimensions gathered from file
	char **inputData;
	char **upMask;
	char **downMask;
	char **leftMask;
	char **rightMask;
	int **outputData;
	
	inputData = ( char **)calloc(x_dim,sizeof( char *));
	upMask = ( char **)calloc(x_dim,sizeof( char *));
	downMask = ( char **)calloc(x_dim,sizeof( char *));
	leftMask = ( char **)calloc(x_dim,sizeof( char *));
	rightMask = ( char **)calloc(x_dim,sizeof( char *));
	outputData = ( int **)calloc(x_dim,sizeof( int *));
	
	for (x = 0; x < x_dim; x++) {
		inputData[x] = ( char *)calloc(y_dim,sizeof( char));
		upMask[x] = ( char *)calloc(y_dim,sizeof( char));
		downMask[x] = ( char *)calloc(y_dim,sizeof( char));
		leftMask[x] = ( char *)calloc(y_dim,sizeof( char));
		rightMask[x] = ( char *)calloc(y_dim,sizeof( char));
		outputData[x] = ( int *)calloc(y_dim,sizeof( int));
	}
	
	//importing data into array
	for (x = 0; x < x_dim; x++) {
		for (y = 0; y < y_dim; y++) {
			while(byte = fgetc(infp), ((byte != delim) && (byte != '\n'))) {
				if(byte != ' ') {
					inputData[x][y] = 1;
				}
			}
			if (inputData[x][y] == 1) {
				++blackcount;
			}
		}
	}
	
	return maze(outfp,x_dim,y_dim,blackcount,inputData,upMask,downMask,leftMask,rightMask,outputData);
}
		
int main(int argc, char *argv[])
{
	int IN_FNAME_ARG = 0, OUT_FNAME_ARG = 0, arglevel, x_dim = 0, y_dim = 0;
	
	if(argc == 1) 
		return help();
		
	//argument handler	
	for(arglevel = 1; arglevel < argc; arglevel++) {
		if (!IN_FNAME_ARG)
			IN_FNAME_ARG = arglevel;
		else OUT_FNAME_ARG = arglevel;
	}
	
	FILE *infp, *outfp;
	infp = fopen(argv[IN_FNAME_ARG],"r");
	outfp = fopen(argv[OUT_FNAME_ARG],"w");
	
	if(infp == NULL) {
		printf("Error: Invalid input file name, file does not exist or does not have read permissions \n %s\n", argv[IN_FNAME_ARG]);
		return(1);
	}
	
	if(infp == NULL) {
		printf("Error: Invalid output file name, check if you have permission to write to the specified location \n %s\n", argv[OUT_FNAME_ARG]);
		return(1);
	}
	
	getdim(infp,outfp,&x_dim,&y_dim);
	
	return arraygen(infp,outfp,x_dim,y_dim);
}
