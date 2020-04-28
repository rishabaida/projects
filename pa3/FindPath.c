// FindPath.c
// Top Level CLient for Graph ADT

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[])
{
	FILE* in;
	FILE* out;
	int inputSize;

	if( argc != 3 )
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

	// Scan in input size
	fscanf(in, "%d", &inputSize);
	Graph G = newGraph(inputSize);

	int vertex1;
	int vertex2;

	// Scan in edges
	while(1 == 1)
	{
		fscanf(in, "%d", &vertex1);
		fscanf(in, "%d", &vertex2);

		if( vertex1 == 0 && vertex2 == 0)
		{
			break;
		}

		addEdge(G, vertex1, vertex2);
	}

	// Print graph
	printGraph(out, G);
	fprintf(out, "\n");

	List paths = newList();
	
	// Loop to run BFS and print out inputted paths
	while(1 == 1)
        {
                fscanf(in, "%d", &vertex1);
                fscanf(in, "%d", &vertex2);

                if( vertex1 == 0 && vertex2 == 0)
                {
                        break;
                }
		
		clear(paths);
                BFS(G, vertex1);
		getPath(paths, G, vertex2);
		
		if(front(paths) == NIL)
		{
			fprintf(out, "The distance from %d to %d is infinity", vertex1, vertex2);
			fprintf(out, "\n");
			fprintf(out, "No %d-%d path exists", vertex1, vertex2);
			fprintf(out, "\n");
		}
		else
		{
			fprintf(out, "The distance from %d to %d is %d", vertex1, vertex2, getDist(G, vertex2));
			fprintf(out, "\n");
			fprintf(out, "A shortest %d-%d path is: ", vertex1, vertex2);
			printList(out, paths);
			fprintf(out, "\n");
		}
		fprintf(out, "\n");
	
        }
	freeList(&paths);
	freeGraph(&G);

	// Close files
	fclose(in);
  	fclose(out);
}
