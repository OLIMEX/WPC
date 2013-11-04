/*
    Olimex WPC #31 -  Run-length encoding and decoding (C version)

    This program reads a file and writes a run-length encoded or decoded version.

	There are two versions of the encoding / decoding routines.

	The first one always writes two bytes n and b. Byte n indicates the repeat count
	and b represents the value to be repeated.

	The second version writes just the value b if b is not repeated or writes b b n
	with n indicating the repeat count (with n >= 2).

	Environment:
		Linux Mint 15
		clang 3.2-1

    Compilation: clang -Wall rle_c.c -o rle_c

 	Usage:
		To run-length encode "infile" into "outfile" : rle_c encode infile outfile
		To decode "infile" into "outfile"            : rle_c decode infile outfile

		alternative version:

		To run-length encode "infile" into "outfile" : rle_c encode2 infile outfile
		To decode "infile" into "outfile"            : rle_c decode2 infile outfile
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


FILE *infile = NULL;
FILE *outfile = NULL;
char* in_fn;
char* out_fn;
int current;
int next;
size_t count;

void usage()
{
    printf("\nThis program run-length encodes or decodes a file\n");
    printf( "Usage:");
    printf( "  To encode file \"infile\": rle_c encode infile outfile");
    printf( "  To decode file \"infile\": rle_c decode infile outfile");
    printf( "Alternative version:");
    printf( "  To encode file \"infile\": rle_c encode2 infile outfile");
    printf( "  To decode file \"infile\": rle_c decode2 infile outfile\n");
}

int open_files()
{
    infile = fopen(in_fn, "rb");
    if (!infile)
    {
        printf("Unable to open %s", in_fn);
        return 0;
    }

    outfile = fopen(out_fn, "wb");
    if (!outfile)
    {
        printf("Unable to open %s", out_fn);
        fclose(infile);
        return 0;
    }

    return 1;
}

void close_files()
{
    fclose(infile);
    fclose(outfile);
}

// Strategy 1

void write_encoded()
{
    while (count > 0)
    {
        if (count > 255)
        {
            fputc(255, outfile);
            count -= 255;
        }
        else
        {
            fputc(count, outfile);
            count = 0;
        }
        fputc(current, outfile);
    }
}

// Encode a file
void encode()
{
    if (!open_files())
        return;

    current = fgetc(infile);
    count = 1;

    while ((next = fgetc(infile)) != EOF)
    {
        if (next != current)
        {
            write_encoded();
            current = next;
            count = 1;
        }
        else
        {
            count++;
        }
    }

    write_encoded();
    close_files();
}

// Decode a file
void decode()
{
    if (!open_files())
        return;

    count = getc(infile);
    current = getc(infile);

    do
    {
        for (int i = 0; i < count; i++)
            fputc(current, outfile);
    }
    while(((count = getc(infile))!=EOF) &&
            ((current = getc(infile))!=EOF));

    close_files();
}

// Strategy 2

void write_encoded_2()
{
    if (count == 1)
        fputc(current, outfile);
    else
        while (count > 0)
        {
            if (count > 1)
            {
                fputc(current, outfile);
                fputc(current, outfile);
                if (count > 255)
                {
                    fputc(255, outfile);
                    count -= 255;
                }
                else
                {
                    fputc(count, outfile);
                    count = 0;
                }
            }
            else
            {
                fputc(current, outfile);
                count = 0;
            }
        }
}

// Encode a file
void encode_2()
{
    if (!open_files())
        return;

    current = fgetc(infile);
    count = 1;

    while ((next = fgetc(infile)) != EOF)
    {
        if (next != current)
        {
            write_encoded_2();
            current = next;
            count = 1;
        }
        else
        {
            count++;
        }
    }

    write_encoded_2();
    close_files();
}

// Decode a file
void decode_2()
{
    if (!open_files())
        return;

    int c1, c2, c3;
    int done = 0;

    c1 = getc(infile);
    c2 = getc(infile);

    if (c1 == EOF)
        done = 1;
    else
    {
        if (c2 == EOF)
        {
            fputc(c1, outfile);
            done = 1;
        }
    }

    while (!done)
    {
        if (c1 == c2)
        {
            c3 = getc(infile);
            if (c3 == EOF)
            {
                fputc(c1, outfile);
                fputc(c2, outfile);
                done = 1;
            }
            else
            {
                for (int i = 0; i < c3; i++)
                    fputc(c1, outfile);
                c1 = getc(infile);
                if (c1 == EOF)
                {
                    done = 1;
                }
                else
                {
                    c2 = getc(infile);
                    if (c2 == EOF)
                    {
                        fputc(c1, outfile);
                        done = 1;
                    }
                }
            }
        }
        else
        {
            fputc(c1, outfile);
            c1 = c2;
            c2 = getc(infile);
            if (c2 == EOF)
            {
                fputc(c1, outfile);
                done = 1;
            }
        }
    }
    close_files();
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        usage();
        return 1;
    }
    else
    {
        in_fn = argv[2];
        out_fn = argv[3];

        if (strcmp(argv[1], "encode") == 0)
            encode();
        else if (strcmp(argv[1], "decode") == 0)
            decode();
        else if (strcmp(argv[1], "encode2") == 0)
            encode_2();
        else if (strcmp(argv[1], "decode2") == 0)
            decode_2();
        else
        {
            printf("Invalid argument \"%s\"\n", argv[1]);
            return 1;
        }

    }
    return 0;
}
