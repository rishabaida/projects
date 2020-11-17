// FindComponents.c
// Top Level CLient for Graph ADT
// Rishab Aida
// raida
// pa4

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
	int components = 0;
	List Stack = newList();

	// check for files
	if( argc != 3 )
	{
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	fprintf(out, "Adjacency list representation of G:\n");

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

	// Initialize graph object
	fscanf(in, "%d", &inputSize);
	Graph G = newGraph(inputSize);

	// Initialize stack for first run of DFS with all vertex values
	for(int i = 1; i <= getOrder(G); i++)
	{
		append(Stack, i);
	}

	int vertex1;
	int vertex2;

	// add Arcs to graph
	while(1 == 1)
	{
		fscanf(in, "%d", &vertex1);
		fscanf(in, "%d", &vertex2);

		if( vertex1 == 0 && vertex2 == 0)
		{
			break;
		}

		addArc(G, vertex1, vertex2);
	}

	Graph trans = transpose(G);

	// Print Graph
	fprintf(out, "Adjacency list representation of G:");
	fprintf(out, "\n");
	printGraph(out, G);
	fprintf(out, "\n");

	// Run DFS on Graph and then Transpose
	DFS(G, Stack);
	DFS(trans, Stack);

	// Print out strongly connected components
	fprintf(out, "G contains %d strongly connected components:", getComponents(trans));
	fprintf(out, "\n");

	 moveBack(Stack);

	 int temp;

	 for(int counter = 1; counter <= getComponents(trans); counter++)
	 {
		 fprintf(out, "Component %d: ", counter);

		 while(getParent(trans, get(Stack)) != 0)
		 {
			 movePrev(Stack);
		 }

		 temp = index(Stack);

		 fprintf(out, "%d ", get(Stack));
		 moveNext(Stack);

		 while(index(Stack) != -1 && getParent(trans, get(Stack)) != 0)
		 {
			 fprintf(out, "%d ", get(Stack));
			 moveNext(Stack);
		 }

		 moveBack(Stack);

		 while(index(Stack) != temp)
		 {
			 movePrev(Stack);
		 }
		 movePrev(Stack);

		 fprintf(out, "\n");
	 }

	// Free memory
	freeList(&Stack);
	freeGraph(&trans);
	freeGraph(&G);

	// close files
	fclose(in);
	fclose(out);
}
