//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------
// Rishab Aida
// raida
// PA1

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"

// Structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj
{
	int data;
	struct NodeObj* previous;
   	struct NodeObj* next;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj
{
	Node front;
	Node back;
	Node cursor;
	int length;
	int index;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes previous, next, and data fields.
// Private.
Node newNode(int data)
{
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->previous = NULL;
	N->next = NULL;
	return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN)
{
	if( pN!=NULL && *pN!=NULL )
	{
		free(*pN);
		*pN = NULL;
	}
}

// newList()
// Returns reference to new empty List object.
List newList(void)
{
	List L;
	L = malloc(sizeof(ListObj));
	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	L->length = 0;
	L->index = -1;
	return(L);
}


// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL)
{
	if( pL!=NULL && *pL!=NULL)
	{
		while(!isEmpty(*pL))
		{
			deleteFront(*pL);
		}
		free(*pL);
		*pL = NULL;
	}
}


// Access functions -----------------------------------------------------------

// length()
// Returns the length of L
int length(List L)
{
	if( L==NULL )
	{
		printf("List Error: calling length() on NULL List reference\n");
		exit(1);
	}
	return(L->length);
}

// index()
// Returns index of cursor element if defined, -1 otherwise
int index(List L)
{
	if( L==NULL )
	{
		printf("List Error: calling index() on NULL List reference\n");
		exit(1);
	}
	return(L->index);
}

// front()
// Returns the value at the front of L
// Pre: length()>0
int front(List L)
{
	if( L==NULL )
	{
		printf("List Error: calling front() on NULL List reference\n");
	    exit(1);
	}

	if( isEmpty(L) )
	{
		printf("List Error: calling front() on an empty List\n");
		exit(1);
	}
	return(L->front->data);
}

// back()
// Returns back element of L
// Pre: length()>0
int back(List L)
{
	if( L==NULL )
	{
		printf("List Error: calling back() on NULL List reference\n");
	    exit(1);
	}

	if( isEmpty(L) )
	{
		printf("List Error: calling back() on an empty List\n");
		exit(1);
	}
	return(L->back->data);
}

// get()
// Returns cursor element of L
// Pre: length()>0, index()>=0
int get(List L)
{
	if( L==NULL )
	{
		printf("List Error: calling get() on NULL List reference\n");
	    exit(1);
	}

	if( isEmpty(L) )
	{
		printf("List Error: calling get() on an empty List\n");
		exit(1);
	}

	if( L->index==-1 )
	{
		printf("List Error: index out of range\n");
		exit(1);
	}
	return(L->cursor->data);
}

// equals()
// Returns true (1) if Lists A and B are in same
// state, and returns false (0) otherwise.
int equals(List A, List B)
{
	int eq = 0;
	Node NA = NULL;
	Node NB = NULL;

	if( A == NULL || B == NULL)
	{
		 printf("List Error: calling equals() on NULL List reference\n");
		 exit(1);
	}

	eq = ( A->length == B->length);
	NA = A->front;
	NB = B->front;
	while( eq && NA!=NULL && NB!=NULL)
	{
		eq = (NA->data == NB->data);
		NA = NA->next;
		NB = NB->next;
	}
	return eq;
}

// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state.
void clear(List L)
{
	if( L==NULL )
	{
		printf("List Error: calling clear() on NULL List reference\n");
		exit(1);
	}

	while(!isEmpty(L))
	{
		deleteFront(L);
	}

	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	L->length = 0;
	L->index = -1;
}

// moveFront()
// If L is non-empty, sets cursor under the front element,
// otherwise does nothing
void moveFront(List L)
{
	if( L==NULL )
	{
		printf("List Error: calling moveFront() on NULL List reference\n");
		exit(1);
	}

	if( isEmpty(L) )
	{
		return;
	}

	L->cursor = L->front;
	L->index = 0;
}

// moveBack()
// If L is non-empty, sets cursor under the back element,
// otherwise does nothing
void moveBack(List L)
{
	if( L==NULL )
	{
		printf("List Error: calling moveBack() on NULL List reference\n");
		exit(1);
	}

	if( isEmpty(L) )
	{
		return;
	}

	L->cursor = L->back;
	L->index = L->length - 1;
}

// movePrev()
// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L)
{
	if( L==NULL )
	{
		printf("List Error: calling movePrev() on NULL List reference\n");
		exit(1);
	}

	if( L->cursor == NULL )
	{
		return;
	}

	if( L->cursor == L->front)
	{
		L->cursor = NULL;
		L->index = -1;
		return;
	}

	L->cursor = L->cursor->previous;
	L->index--;
}

// moveNext()
// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L)
{
	if( L==NULL )
	{
		printf("List Error: calling moveNext() on NULL List reference\n");
		exit(1);
	}

	if( L->cursor == NULL )
	{
		return;
	}

	if( L->cursor == L->back)
	{
		L->cursor = NULL;
		L->index = -1;
		return;
	}
	L->cursor = L->cursor->next;
	L->index++;
}

// prepend()
// Insert new element into L. If L is non-empty,
// insertion takes place before front element
void prepend(List L, int data)
{
	if( L==NULL )
	{
		printf("List Error: calling prepend() on NULL List reference\n");
		exit(1);
	}

	Node N = newNode(data);

	if( isEmpty(L) )
	{
		L->front = N;
		L->back = N;
		L->length++;
		return;
	}

	L->front->previous = N;
	N->next = L->front;
	L->front = N;
	L->length++;

	if(L->index >= 0)
	{
		L->index++;
	}
}

// append()
// Insert new element into L. If L is non-empty,
// insertion takes place after back element
void append(List L, int data)
{
	if( L==NULL )
	{
		printf("List Error: calling append() on NULL List reference\n");
		exit(1);
	}

	Node N = newNode(data);

	if( isEmpty(L) )
	{
		L->front = N;
		L->back = N;
		L->length++;
		return;
	}

	L->back->next = N;
	N->previous = L->back;
	L->back = N;
	L->length++;
}

// insertBefore
// Insert new element before cursor
// Pre: length()>0, index()>=0
void insertBefore(List L, int data)
{
	if( L==NULL )
	{
		printf("List Error: calling get() on NULL List reference\n");
	    exit(1);
	}

	if( isEmpty(L) )
	{
		printf("List Error: calling insertAfter() on an empty List\n");
		exit(1);
	}

	if( L->index==-1 )
	{
		printf("List Error: index out of range\n");
		exit(1);
	}

	Node N = newNode(data);
	if( L->cursor == L->front)
	{
		N->next = L->cursor;
		L->cursor->previous = N;
		L->front = N;
		L->length++;
		L->index++;
		return;
	}

	N->next = L->cursor;
	N->previous = L->cursor->previous;
	L->cursor->previous = N;
	N->previous->next = N;
	L->index++;
	L->length++;
}

// insertAfter
// Insert new element after cursor
// Pre: length()>0, index()>=0
void insertAfter(List L, int data)
{
	if( L==NULL )
		{
			printf("List Error: calling get() on NULL List reference\n");
		    exit(1);
		}

		if( isEmpty(L) )
		{
			printf("List Error: calling insertAfter() on an empty List\n");
			exit(1);
		}

		if( L->index==-1 )
		{
			printf("List Error: index out of range\n");
			exit(1);
		}

		if( L->cursor == L->back)
		{
			Node N = newNode(data);
			N->previous = L->cursor;
			L->cursor->next = N;
			L->back = N;
			L->length++;
			return;
		}

		Node N = newNode(data);
		N->previous = L->cursor;
		N->next = L->cursor->next;
		L->cursor->next = N;
		N->next->previous = N;
		L->length++;
}

// deleteFront()
// Delete the front element. Pre: length()>0
void deleteFront(List L)
{
	if( L==NULL )
	{
		printf("List Error: calling deleteFront() on NULL List reference\n");
	    exit(1);
	}

	if( isEmpty(L) )
	{
		printf("List Error: calling deleteFront() on an empty List\n");
		exit(1);
	}

	if( L->length == 1)
	{
		Node N = L->front;
	    freeNode(&N);
	    L->length--;
	    L->index = -1;
	    L->cursor = NULL;
	    return;
	}

	if( L->cursor == L->front)
	{
		Node N = L->front;
		L->front = L->front->next;
		L->front->previous = NULL;
		freeNode(&N);
		L->length--;
		L->cursor = NULL;
		L->index = -1;
		return;
	}

	if( L->cursor == L->back)
	{
		Node N = L->front;
		L->front = L->front->next;
		L->front->previous = NULL;
		freeNode(&N);
		L->length--;
		L->index = L->length-1;
		return;
	}


	Node N = L->front;
	L->front = L->front->next;
	L->front->previous = NULL;
	freeNode(&N);
	L->length--;
	L->index--;
}

// deleteBack()
// Delete the back element. Pre: length()>0
void deleteBack(List L)
{
    if( L==NULL )
    {
            printf("List Error: calling deleteBack() on NULL List reference\n");
        exit(1);
    }

    if( isEmpty(L) )
    {
            printf("List Error: calling deleteBack() on an empty List\n");
            exit(1);
    }

    if( L->length == 1)
    {
            Node N = L->front;
            freeNode(&N);
            L->length--;
            L->index = -1;
            L->cursor = NULL;
            return;
    }

    if( L->cursor == L->back)
    {
            Node N = L->back;
            L->back = L->back->previous;
            L->back->next = NULL;
            freeNode(&N);
            L->length--;
            L->cursor = NULL;
            L->index = -1;
            return;
    }

    if( L->cursor == L->front )
    {
    	Node N = L->back;
    	L->back = L->back->previous;
    	L->back->next = NULL;
    	freeNode(&N);
    	L->length--;
    	L->index = 0;
    	return;
    }

    Node N = L->back;
    L->back = L->back->previous;
    L->back->next = NULL;
    freeNode(&N);
    L->length--;
    L->index--;

}

// delete()
// Delete cursor element, making cursor undefined
// Pre: length()>0, index()>=0
void delete(List L)
{
	if( L==NULL )
	{
		printf("List Error: calling get() on NULL List reference\n");
		exit(1);
	}

	if( isEmpty(L) )
	{
		printf("List Error: calling insertAfter() on an empty List\n");
		exit(1);
	}

	if( L->index==-1 )
	{
		printf("List Error: index out of range\n");
		exit(1);
	}

	if( L->length == 1)
	{
		Node N = L->front;
		freeNode(&N);
		L->length--;
		L->index = -1;
		L->cursor = NULL;
		return;
	}

	if( L->cursor == L->front)
	{
		Node N = L->front;
		L->front = L->front->next;
		L->front->previous = NULL;
		freeNode(&N);
		L->length--;
		L->cursor = NULL;
		L->index = -1;
		return;
	}

	 if( L->cursor == L->back)
	 {
		 Node N = L->back;
		 L->back = L->back->previous;
		 L->back->next = NULL;
		 freeNode(&N);
		 L->length--;
		 L->cursor = NULL;
		 L->index = -1;
		 return;
	 }

	 L->cursor->previous->next = L->cursor->next;
	 L->cursor->next->previous = L->cursor->previous;
	 freeNode(&(L->cursor));
	 L->cursor = NULL;
	 L->index = -1;
	 L->length--;
}

// isEmpty()
// Returns true (1) if Q is empty, otherwise returns false (0)
int isEmpty(List L)
{
	if( L==NULL )
	{
		printf("List Error: calling isEmpty() on NULL List reference\n");
		exit(1);
	}
	return(L->length==0);
}

// Other Operations ------------------------------------------------------------

// printList()
// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left
void printList(FILE* out, List L)
{
	if( L==NULL )
	{
		printf("List Error: calling printList() on NULL List reference\n");
		exit(1);
	}

	if(out == NULL)
	{
		printf("Unable to open file for writing/n");
	}

	Node N = NULL;

	for(N = L->front; N != NULL; N = N->next)
	{
		fprintf(out, "%d ", N->data);
	}
}

// copyList()
// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged
List copyList(List L)
{
	if( L==NULL )
	{
		printf("List Error: calling copyList() on NULL List reference\n");
		exit(1);
	}

	List copy = newList();

	Node N = NULL;

	for(N = L->front; N != NULL; N = N->next)
	{
		append(copy, N->data);
	}
	return copy;
}