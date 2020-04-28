// GraphTest.c
// Test File for Graph ADT
// Rishab Aida
// raida
// pa3

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"

int main(int argc, char* argv[])
{
	List L = newList();
	List C = newList();
	Graph A = newGraph(64);
	
	addArc(A, 64, 4);
        addArc(A, 64, 3);
        addArc(A, 42, 2);
        addArc(A, 2, 64);
        addArc(A, 4, 2);
        addArc(A, 3, 42);
        BFS(A, 3);
        getPath(L, A, 64);
        append(C, 3);
        append(C, 42);
        append(C, 2);
        append(C, 64);
	
	moveFront(L);
        BFS(A, 2);
        getPath(L, A, 2);
        append(C, 2);

	//getPath(L, A, 99);
        clear(L);
        clear(C);
        append(C, NIL);
        BFS(A, 99);
        getPath(L, A, 2);
	

	printList(stdout, L);
	printf("\n");

	printList(stdout, C);
        printf("\n");

	
	freeList(&C);
	freeList(&L);
	freeGraph(&A);
}
