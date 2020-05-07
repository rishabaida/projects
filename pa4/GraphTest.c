#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[])
{
	Graph G = newGraph(8);
	addArc(G, 1, 2);
	addArc(G, 2, 3);
	addArc(G, 2, 5);
	addArc(G, 2, 6);
	addArc(G, 3, 4);
	addArc(G, 3, 7);
	addArc(G, 4, 3);
	addArc(G, 4, 8);	
	addArc(G, 5, 1);
	addArc(G, 5, 6);
	addArc(G, 6, 7);
	addArc(G, 7, 6);
	addArc(G, 7, 8);
	addArc(G, 8, 8);

	printGraph(stdout, G);

	List Stack = newList();

	for(int i = 1; i <= getOrder(G); i++)
	{
		append(Stack, i);
	}

	DFS(G, Stack);
	printList(stdout, Stack);
	printf("\n");
	printf("\n");

	Graph trans = transpose(G);

	printGraph(stdout, trans);

	DFS(trans, Stack);
	printList(stdout, Stack);
	printf("\n");

	printf("%d", getComponents(trans));
	printf("\n");
	printf("\n");

	for(int u = 1; u <= getOrder(trans); u++)
	{
		printf("%d", getParent(trans, u));
		printf("\n");
	}

	moveBack(Stack);
	
	int temp;
	
	for(int counter = 1; counter <= getComponents(trans); counter++)
	{
		printf("%d: ", counter);
		
		while(getParent(trans, get(Stack)) != 0)
		{
			movePrev(Stack);
		}

		temp = index(Stack);

		printf("%d ", get(Stack));
		moveNext(Stack);

		while(index(Stack) != -1 && getParent(trans, get(Stack)) != 0)
		{
			printf("%d ", get(Stack));
			moveNext(Stack);
		}
		
		moveBack(Stack);

		while(index(Stack) != temp)
		{
			movePrev(Stack);
		}
			movePrev(Stack);

		printf("\n");		
	}
}
