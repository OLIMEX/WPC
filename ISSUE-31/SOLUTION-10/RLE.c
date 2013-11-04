/* 	Simple single byte based RLE/D algorithm implemented in C
	"binary style" encoding is used to store the # of occurrences 
	Output is in the form of (number) (delimiter) (byte)
	Example (in hex): 	05 09 86 42 00 38 fe fe ff 00 cc
	Equates to (4 + 2032 + 8580628 + 1065159160) (delim) (hex char 38) (253 + 64262 + 16387064) (delim) (hex char cc)
	Which is 1Gb of number 8, followed by 15.6Mb of hex char cc
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DELIMITER 0

int help() {
	printf("\nBasic single byte RLE/D compression program \n");
	printf("*Note: Output can be larger than input where runs \n");
	printf("consisting of less than 3 bytes frequently occur \n\n");
	printf("Usage: \n");
	printf("rle [-d] inputfile outputfile \n");
	printf("Include -d for decompression, omit for compression \n");
	printf("*Note: Specified outputfile is automatically overwritten \n");
	return(0);
}

int uncompress(FILE *infp, FILE *outfp) {
	unsigned int length = 1, tmplength = 1, iteration = 0, i;
	unsigned char byte, delim = DELIMITER;
	
	while(!feof(infp)) {
		if (byte = fgetc(infp), byte != delim) {
			if(iteration == 0) {
				length = (byte - 1);
				++iteration;
			}
			else {
				//"binary style" decoder, does 254 ^ iteration * byte
				for(i = 0; i < iteration; i++) {
					tmplength *= 254;
				}
				tmplength *= (byte - 1);
				++iteration;
				length += tmplength;
				tmplength = 1;
			}
		}
		else {
			//get byte after delim, then output to file
			byte = fgetc(infp);
			for(i = 0; i < length; i++) {
				fputc(byte,outfp);
			}
			length = 1;
			iteration = 0;
			tmplength = 1;
		}
	}
	
	printf("File decompressed \n");
	return(0);
}
	
	
int compress(FILE *infp, FILE *outfp) {
	unsigned int length = 1, tmplength;
	unsigned char byte, tmpbyte, delim = DELIMITER;
	tmpbyte = fgetc(infp);
	
	while(1) {
		if (byte = fgetc(infp), feof(infp) || (byte != tmpbyte)) {
			//length byte is omitted if it is equal to one
			if(length != 1) {
				while(length > 254) {
					/* "binary style" encoder, modulus is used to encode each byte
					   (length is incremented to avoid colliding with delimiter 0) */
					tmplength = (length / 254);
					length %= 254;
					++length;
					fputc(length,outfp);
					length = tmplength;
				}
				++length;
				fputc(length,outfp);
			}
			fputc(delim,outfp);
			fputc(tmpbyte,outfp);
			tmpbyte = byte;
			length = 1;
			if(feof(infp))
				break;
		}
		else ++length;
	}
	
	printf("File compressed \n");
	return(0);
}
	

int main(int argc, char *argv[])
{
	int IN_FNAME_ARG = 0, OUT_FNAME_ARG = 0, decompress = 0, arglevel;
	
	if(argc == 1) 
		return help();
		
	//argument handler	
	for(arglevel = 1; arglevel < argc; arglevel++) {
		if (!(strcmp(argv[arglevel], "-h")) || !(strcmp(argv[arglevel], "/h")))
			return help();
		else if (!(strcmp(argv[arglevel], "-?")) || !(strcmp(argv[arglevel], "/?")))
			return help();
		else if (!(strcmp(argv[arglevel], "-d")) || !(strcmp(argv[arglevel], "/d")))
			decompress = 1;
		else if (!IN_FNAME_ARG)
			IN_FNAME_ARG = arglevel;
		else OUT_FNAME_ARG = arglevel;
	}
	
	FILE *infp, *outfp;
	infp = fopen(argv[IN_FNAME_ARG],"rb");
	outfp = fopen(argv[OUT_FNAME_ARG],"wb");
	
	if(infp == NULL) {
		printf("Error: Invalid input file name, file does not exist or does not have read permissions \n %s\n", argv[IN_FNAME_ARG]);
		return(1);
	}
	
	if(infp == NULL) {
		printf("Error: Invalid output file name, check if you have permission to write to the specified location \n %s\n", argv[OUT_FNAME_ARG]);
		return(1);
	}
	
	if(decompress) 
		return uncompress(infp,outfp);
	else return compress(infp,outfp);
}
