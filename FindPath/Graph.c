//-----------------------------------------------------------------------------
// Graph.c
// Implementation file for Graph ADT
//-----------------------------------------------------------------------------
// Rishab Aida
// raida
// PA3

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
#include "List.h"
#define NIL 0
#define INF -1

// Structs --------------------------------------

// private GraphObj type
typedef struct GraphObj
{
	List* vertexNeighbors;
	int* parents;
	int* distances;
	int size;
	int order;
	int source;
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
	G->distances = malloc(sizeof(int) * placeholder);
	G->size = 0;
	G->order = n;
	G->source = NIL;

	for(int i = 1; i <= n; i++)
	{
		G->vertexNeighbors[i] = newList();
		G->parents[i] = NIL;
		G->distances[i] = INF;
	}

	return(G);
}

void freeGraph(Graph* pG)
{
	free((*pG)->parents);
	free((*pG)->distances);
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

int getSize(Graph G)
{
	if(G == NULL)
	{
		printf("Graph Error: getSize called with NULL Graph reference");
		exit(1);
	}
	return(G->size);
}

int getSource(Graph G)
{
	if(G == NULL)
	{
		printf("Graph Error: getSource called with NULL Graph reference");
		exit(1);
	}
	return(G->source);
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

int getDist(Graph G, int u)
{
	if(G == NULL)
	{
		printf("Graph Error: getDist called with NULL Graph reference");
		exit(1);
	}

	if(u < 1 || u > G->order)
	{
		printf("Graph Error: getDist called with invalid u");
		exit(1);
	}

	return(G->distances[u]);
}

void getPath(List L, Graph G, int u)
{
	if(G == NULL)
	{
		printf("Graph Error: getPath called with NULL Graph reference");
		exit(1);
	}

	if(L == NULL)
	{
		printf("Graph Error: getPath called with NULL List reference");
		exit(1);
	}
	
	if(u < 1 || u > G->order)
	{
		printf("Graph Error: getPath called with invalid u");
		exit(1);
	}

	if(getSource(G) == NIL)
	{
		printf("Graph Error: Must call BFS before calling getSource");
		exit(1);
	}

	if(getSource(G) < 1 || getSource(G) > G->order)
	{
		append(L, NIL);
		return;
	}

	if(u == G->source)
	{
		append(L, u);
		return;
	}

	while(u != G->source && u != NIL)
	{
		prepend(L, u);
		u = G->parents[u];
	}

	if(u == NIL)
	{
		clear(L);
	}

	prepend(L, u);
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
		printf("Graph Error: addEdge called on same vertex");
		exit(1);
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

	if(u == v)
	{
		printf("Graph Error: addArc called on same vertex");
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

void BFS(Graph G, int s)
{
	if(G == NULL)
	{
		printf("Graph Error: BFS called with NULL Graph reference");
		exit(1);
	}

	if(s < 1 || G->order < s)
	{
		printf("Graph Error: BFS called with invalid s");
		exit(1);
	}

	for(int i = 1; i <= G->order; i++)
        {
                G->parents[i] = NIL;
                G->distances[i] = INF;
        }


	List Queue = newList();
	G->source = s;
	G->distances[s] = 0;
	append(Queue, s);
	int currentVertex;
	int listScroller;

	while(!isEmpty(Queue))
	{
		currentVertex = front(Queue);
		deleteFront(Queue);
		moveFront(G->vertexNeighbors[currentVertex]);

		while(index(G->vertexNeighbors[currentVertex]) != -1)
		{
			listScroller = get(G->vertexNeighbors[currentVertex]);

			if(G->distances[listScroller] == INF)
			{
				G->distances[listScroller] = G->distances[currentVertex] + 1;
				G->parents[listScroller] = currentVertex;
				append(Queue, listScroller);
			}
			moveNext(G->vertexNeighbors[currentVertex]);
		}
	}
	freeList(&Queue);
	return;
}

/*** Other operations ***/

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
