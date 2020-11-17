//-----------------------------------------------------------------------------
// Graph.c
// Implementation file for Graph ADT
//-----------------------------------------------------------------------------
// Rishab Aida
// raida
// PA4

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
#include "List.h"
#define NIL 0
#define UNDEF -1

// Structs --------------------------------------

// private GraphObj type
typedef struct GraphObj
{
	List* vertexNeighbors;
	int* parents;
	int* discovers;
	int* finishes;
	int size;
	int order;
	int components;
}GraphObj;

// private Graph type
typedef GraphObj* Graph;

/*** Constructors-Destructors ***/

Graph newGraph(int n)
{
	int placeholder = n + 1;
	Graph G = malloc(sizeof(GraphObj));
	G->vertexNeighbors = malloc(sizeof(List) * placeholder);
	G->parents = malloc(sizeof(int) * placeholder);
	G->discovers = malloc(sizeof(int) * placeholder);
	G->finishes = malloc(sizeof(int) * placeholder);
	G->size = 0;
	G->order = n;
	G->components = 0;

	for(int i = 1; i <= n; i++)
	{
		G->vertexNeighbors[i] = newList();
		G->parents[i] = NIL;
		G->discovers[i] = UNDEF;
		G->finishes[i] = UNDEF;
	}

	return(G);
}

void freeGraph(Graph* pG)
{
	free((*pG)->parents);
	free((*pG)->discovers);
	free((*pG)->finishes);
	for(int i = 1; i <= (*pG)->order; i++)
	{
		freeList(&(*pG)->vertexNeighbors[i]);
	}
	free((*pG)->vertexNeighbors);
	free(*pG);
	*pG = NULL;
}

/*** Access functions ***/

int getOrder(Graph G)
{
	if(G == NULL)
	{
		printf("Graph Error: getOrder called with NULL Graph reference");
		exit(1);
	}
	return(G->order);
}

int getComponents(Graph G)
{
        if(G == NULL)
        {
                printf("Graph Error: getComponents called with NULL Graph reference");
                exit(1);
        }
        return(G->components);
}


int getSize(Graph G)
{
	if(G == NULL)
	{
		printf("Graph Error: getSize called with NULL Graph reference");
		exit(1);
	}
	return(G->size);
}

int getParent(Graph G, int u)
{
	if(G == NULL)
	{
		printf("Graph Error: getParent called with NULL Graph reference");
		exit(1);
	}

	if(u < 1 || u > G->order)
	{
		printf("Graph Error: getParent called with invalid u");
		exit(1);
	}

	return(G->parents[u]);
}

int getDiscover(Graph G, int u)
{
	if(G == NULL)
	{
		printf("Graph Error: getDiscover called with NULL Graph reference");
		exit(1);
	}

	if(u < 1 || u > G->order)
	{
		printf("Graph Error: getDiscover called with invalid u");
		exit(1);
	}

	return(G->discovers[u]);
}

int getFinish(Graph G, int u)
{
	if(G == NULL)
	{
		printf("Graph Error: getFinish called with NULL Graph reference");
		exit(1);
	}

	if(u < 1 || u > G->order)
	{
		printf("Graph Error: getFinish called with invalid u");
		exit(1);
	}

	return(G->finishes[u]);
}

/*** Manipulation procedures ***/

void makeNull(Graph G)
{
	if(G == NULL)
	{
		printf("Graph Error: makeNull called with NULL Graph reference");
		exit(1);
	}

	for(int i = 1; i <= G->order; i++)
	{
		clear(G->vertexNeighbors[i]);
	}
}

void addEdge(Graph G, int u, int v)
{
	if(G == NULL)
	{
		printf("Graph Error: addEdge called with NULL Graph reference");
		exit(1);
	}

	if(u < 1 || u > G->order)
	{
		printf("Graph Error: addEdge called with invalid u");
		exit(1);
	}

	if(v < 1 || v > G->order)
	{
		printf("Graph Error: addEdge called with invalid v");
		exit(1);
	}

	if(u == v)
	{
		addArc(G, u, v);
		return;
	}

	addArc(G, u, v);
	addArc(G, v, u);
	G->size = G->size - 1;;
}

void addArc(Graph G, int u, int v)
{
	if(G == NULL)
	{
		printf("Graph Error: addArc called with NULL Graph reference");
		exit(1);
	}

	if(u < 1 || u > G->order)
	{
		printf("Graph Error: addArc called with invalid u");
		exit(1);
	}

	if(v < 1 || v > G->order)
	{
		printf("Graph Error: addArc called with invalid v");
		exit(1);
	}

	moveFront(G->vertexNeighbors[u]);
	while(index(G->vertexNeighbors[u]) != -1)
	{
		if(get(G->vertexNeighbors[u]) > v)
                {
                        insertBefore(G->vertexNeighbors[u], v);
                        G->size++;
                        return;
                }


		if(get(G->vertexNeighbors[u]) < v)
		{
			moveNext(G->vertexNeighbors[u]);
		}
	}

	append(G->vertexNeighbors[u], v);
	G->size++;
}

void DFS(Graph G, List s)
{
	if(G == NULL)
	{
		printf("Graph Error: DFS called with NULL Graph reference");
		exit(1);
	}

	if(G->order != length(s))
	{
		printf("Graph Error: DFS must utilize correctly sized List s");
		exit(1);
	}

	int* time = calloc(sizeof(int), 1);

	List temp = newList();
	moveFront(s);
	while(index(s) != -1)
	{
		append(temp, get(s));
		moveNext(s);
	}

	moveFront(temp);
	clear(s);

	for(int i = 1; i <= G->order; i++)
	{
		G->parents[i] = NIL;
		G->discovers[i] = UNDEF;
		G->finishes[i] = UNDEF;
	}

	for(int y = 0; y < length(temp); y++)
	{
		int scroller = get(temp);

		if(G->discovers[scroller] >= 0)
		{
			moveNext(temp);
		}

		else
		{
			G->components++;
			visit(G, s, time, scroller);
			moveNext(temp);
		}
	}
	freeList(&temp);
	free(time);
}

void visit(Graph G, List s, int* time, int scroller)
{
	G->discovers[scroller] = ++(*time);

	moveFront(G->vertexNeighbors[scroller]);
	for(int counter = 0; counter < length(G->vertexNeighbors[scroller]); counter++)
	{
		int currentVertex = get(G->vertexNeighbors[scroller]);

		if(G->discovers[currentVertex] >= 0)
		{
			moveNext(G->vertexNeighbors[scroller]);
		}

		else
		{
			G->parents[currentVertex] = scroller;
			visit(G, s, time, currentVertex);
			moveNext(G->vertexNeighbors[scroller]);
		}
	}
	prepend(s, scroller);
	G->finishes[scroller] = ++(*time);
}

/*** Other operations ***/

Graph transpose(Graph G)
{
	if(G == NULL)
	{
		printf("Graph Error: transpose called with NULL Graph reference");
		exit(1);
	}

	Graph transpose = newGraph(G->order);
	transpose->size = G->size;
	transpose->order = G->order;

	for(int i = 1; i <= transpose->order; i++)
	{
		moveFront(G->vertexNeighbors[i]);
		for(int x = 0; x < length(G->vertexNeighbors[i]); x++)
		{
			addArc(transpose, get(G->vertexNeighbors[i]),i);
			moveNext(G->vertexNeighbors[i]);
		}
	}
	return(transpose);
}

Graph copyGraph(Graph G)
{
	if(G == NULL)
	{
		printf("Graph Error: copyGraph called with NULL Graph reference");
		exit(1);
	}

	Graph copy = newGraph(G->order);
	copy->order = G->order;
	copy->size = G->size;

	for(int i = 1; i <= G->order; i++)
	{
		copy->parents[i] = G->parents[i];
		copy->discovers[i] = G->discovers[i];
		copy->finishes[i] = G->finishes[i];
	}

	for(int x = 1; x <= G->order; x++)
	{
		moveFront(G->vertexNeighbors[x]);

		while(index(G->vertexNeighbors[x]) != -1)
		{
			append(copy->vertexNeighbors[x], get(G->vertexNeighbors[x]));
			moveNext(G->vertexNeighbors[x]);
		}
	}

	return(copy);
}

void printGraph(FILE* out, Graph G)
{
	if(G == NULL)
	{
		printf("Graph Error: printGraph called with NULL Graph reference");
		exit(1);
	}

	for(int i = 1; i <= G->order; i++)
	{
		moveFront(G->vertexNeighbors[i]);
		fprintf(out, "%d: ", i);
		printList(out, G->vertexNeighbors[i]);
		fprintf(out, "\n");
	}
}
