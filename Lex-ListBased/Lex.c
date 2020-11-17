//-----------------------------------------------------------------------------
// Lex.c
// File that sorts input file alphabetically
//-----------------------------------------------------------------------------
// Rishab Aida
// raida
// PA1

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"

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

    // Creates List
    List L = newList();

    int test = 1;

    // Add first element to List
    append(L, 0);

    // Double loop to input sorted string indices into List
    while(test<counter)
    {
    	moveFront(L);
    	while(index(L) >= 0)
    	{
    		int x = get(L);
    		if(strcmp(inputArray[test], inputArray[x]) < 0)
    		{
    			insertBefore(L, test);
    			break;
    		}
    		moveNext(L);
    	}
    	int y = back(L);
    	if(strcmp(inputArray[test], inputArray[y]) > 0)
    	{
    		append(L, test);
    	}
    	test++;
    }

    // Prints to output file
    moveFront(L);
    while(index(L) >= 0)
    {
    	fprintf(out, "%s", inputArray[get(L)]);
    	moveNext(L);
    }

    int counter4 = 0;

    // Free String Array
    while(counter4<counter)
    {
    	free(inputArray[counter4]);
    	counter4++;
    }

    free(inputArray);

    // Free List
    freeList(&L);

    // close files
    fclose(in);
    fclose(out);

    return(0);
}
