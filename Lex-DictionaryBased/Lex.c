//-----------------------------------------------------------------------------
// Lex.c
// File that sorts input file alphabetically
//-----------------------------------------------------------------------------
// Rishab Aida
// raida
// PA5

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Dictionary.h"

#define MAX_LENGTH 160

int main(int argc, char * argv[])
{
	FILE *in;
	FILE *out;
	int counter = 0;
	int counter2 = 0;

	// Check command line for correct number of arguments
	if( argc != 3)
	{
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	// Open files for reading and writing
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");

    if( in==NULL )
    {
    	printf("Unable to open file %s for reading\n", argv[1]);
    	exit(1);
    }

    if( out==NULL )
    {
    	printf("Unable to open file %s for writing\n", argv[2]);
    	exit(1);
    }

    char checker;

    // Count lines in input file
    while(( checker = fgetc(in)) != EOF )
    {
    	if(checker == '\n')
    	{
    		counter++;
    	}
    }

    // Rewind cursor
    rewind(in);

    // Allocates memory for String Array
    char** inputArray;
    int size = counter * sizeof(char*);
    inputArray = malloc(size);

    while(counter2<counter)
    {
    	inputArray[counter2] = malloc(MAX_LENGTH * sizeof(char));
    	counter2++;
    }

    int counter3 = 0;

    // Reads strings to array
    while(counter3<counter)
    {
    	fgets(inputArray[counter3], MAX_LENGTH, in);
    	counter3++;
    }

    // Creates Dictionary, inputs keys
    Dictionary D = newDictionary(0);

    int walker = 0;

    while(walker<counter)
    {
    	insert(D, inputArray[walker], 0);
	walker++;
    }

	// prints keys out in order
    beginForward(D);

	while(currentKey(D) != KEY_UNDEF)
	{
		fprintf(out, "%s", currentKey(D));
		next(D);
	}

    int counter4 = 0;

    // Free String Array
    while(counter4<counter)
    {
    	free(inputArray[counter4]);
    	counter4++;
    }

    free(inputArray);

    // Free Dictionary
    freeDictionary(&D);

    // close files
    fclose(in);
    fclose(out);

    return(0);
}
