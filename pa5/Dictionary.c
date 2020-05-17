//-----------------------------------------------------------------------------
// Dictionary.c
// Implementation file for Dictionary ADT storing (key, value) pairs of types KEY_TYPE
// and VAL_TYPE.
//-----------------------------------------------------------------------------
// Rishab Aida
// raida
// PA5

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define KEY_TYPE char*
#define VAL_TYPE int
#define KEY_UNDEF NULL
#define VAL_UNDEF -1
#define KEY_FORMAT "%s"
#define VAL_FORMAT "%d"
#define KEY_CMP(x,y) strcmp((x),(y))

// private NodeObj type
typedef struct NodeObj
{
	KEY_TYPE key;
	VAL_TYPE value;
	struct NodeObj* parent;
   	struct NodeObj* left;
   	struct NodeObj* right;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// Exported type --------------------------------------------------------------
typedef struct DictionaryObj
{
	Node root;
	int unique;
	int size;
	Node cursor;
	int iteration;
}DictionaryObj;

typedef DictionaryObj* Dictionary;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes previous, next, and data fields.
// Private.
Node newNode(KEY_TYPE k, VAL_TYPE v)
{
	Node N = malloc(sizeof(NodeObj));
	N->key = k;
	N->value = v;
	N->parent = NULL;
	N->left = NULL;
	N->right = NULL;
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

// newDictionary()
// Creates a new empty Dictionary. If unique==false (0), then the Dictionary
// will accept duplicate keys, i.e. distinct pairs with identical keys. If
// unique==true (1 or any non-zero value), then duplicate keys will not be
// accepted. In this case, the operation insert(D, k) will enforce the
// precondition: lookup(D, k)==VAL_UNDEF
Dictionary newDictionary(int unique)
{
	Dictionary D = malloc(sizeof(DictionaryObj));
	D->unique = unique;
	D->cursor = NULL;
	D->root = NULL;
	D->size = 0;
	D->iteration = 0;
}

// freeDictionary()
// Frees heap memory associated with *pD, sets *pD to NULL.
void freeDictionary(Dictionary* pD)
{
	if( pD!=NULL && *pD!=NULL)
	{
		makeEmpty(*pD);
		free(*pD);
		*pD = NULL;
	}
}


// Access functions -----------------------------------------------------------

// size()
// Returns the number of (key, value) pairs in Dictionary D.
int size(Dictionary D)
{
	if( D==NULL )
		{
			printf("Dictionary Error: calling size() on NULL Dictionary reference\n");
			exit(1);
		}
	return(D->size);
}

// getUnique()
// Returns true (1) if D requires that all pairs have unique keys. Returns
// false (0) if D accepts distinct pairs with identical keys.
int getUnique(Dictionary D)
{
	if( D==NULL )
	{
		printf("Dictionary Error: calling getUnique() on NULL Dictionary reference\n");
		exit(1);
	}
	return(D->unique);
}


// search()
Node search(Node N, KEY_TYPE k)
{
	if(N == NULL || k == N->key)
	{
		return(N);
	}

	if(KEY_CMP(k, N->key) < 0)
	{
		return(search(N->left, k));
	}

	else
	{
		return(search(N->right, k));
	}
}

// lookup()
// If Dictionary D contains a (key, value) pair whose key matches k (i.e. if
// KEY_CMP(key, k)==0), then returns value. If D contains no such pair, then
// returns VAL_UNDEF.
VAL_TYPE lookup(Dictionary D, KEY_TYPE k)
{
	if( D==NULL )
	{
		printf("Dictionary Error: calling lookup() on NULL Dictionary reference\n");
		exit(1);
	}

	Node target = search(D->root, k);

	if(target == NULL)
	{
		return(VAL_UNDEF);
	}

	else
	{
		return(target->value);
	}
}


// Manipulation procedures ----------------------------------------------------

// findMin()
Node findMin(Node N)
{
        Node M = N;
        while(M->left != NULL)
        {
                M = M->left;
        }

        return(M);
}

// findMax()
Node findMax(Node N)
{
        Node M = N;
        while(M->right != NULL)
        {
                M = M->right;
        }

        return(M);
}

// getSuccesor
Node getSuccesor(Node N)
{
        if(N->right != NULL)
        {
                return(findMin(N->right));
        }

        Node temp = N->parent;

        while(temp != NULL && N == temp->right)
        {
                N = temp;
                temp = temp->parent;
        }

        return(temp);
}
 
//getPred()

Node getPred(Node N)
{
        if(N->left != NULL)
        {
                return(findMax(N->left));
        }

        Node temp = N->parent;

        while(temp != NULL && N == temp->left)
        {
                N = temp;
                temp = temp->parent;
        }

        return(temp);
}
           
                 
// insert()
// Insert the pair (k,v) into Dictionary D.
// If getUnique(D) is false (0), then there are no preconditions.
// If getUnique(D) is true (1), then the precondition lookup(D, k)==VAL_UNDEF
// is enforced.
void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v)
{
	if( D==NULL )
	{
			printf("Dictionary Error: calling insert() on NULL Dictionary reference\n");
			exit(1);
	}

	if(getUnique(D) == 1)
	{
		if(lookup(D, k) != VAL_UNDEF)
		{
			printf("Dictionary Error: getUnique is true. Key already exists");
			exit(1);
		}
	}

	Node N = newNode(k, v);
	Node Y = NULL;
	Node X;

	if(D->size == 0)
	{
		D->root = N;
		D->size++;
		return;
	}

	X = D->root;

	while(X != NULL)
	{
		Y = X;
		if(KEY_CMP(k, X->key) < 0)
		{
			X = X->left;
		}

		else
		{
			X = X->right;
		}
	}

	N->parent = Y;

	if(KEY_CMP(k, Y->key) < 0)
	{
		Y->left = N;
	}

	else
	{
		Y->right = N;
	}

	D->size++;
}

// transplant()
void transplant(Dictionary D, Node U, Node V)
{
	if(U->parent == NULL)
	{
		D->root = V;
	}

	else if(U == U->parent->left)
	{
		U->parent->left = V;
	}

	else
	{
		U->parent->right = V;
	}

	if(V != NULL)
	{
		V->parent = U->parent;
	}
}

// delete()
// Remove the pair whose key is k from Dictionary D.
// Pre: lookup(D,k)!=VAL_UNDEF (i.e. D contains a pair whose key is k.)
void delete(Dictionary D, KEY_TYPE k)
{
	if( D==NULL )
	{
			printf("Dictionary Error: calling delete() on NULL Dictionary reference\n");
			exit(1);
	}

	if(lookup(D, k) == VAL_UNDEF)
	{
		printf("Dictionary Error: trying to delete non-existent key");
		exit(1);
	}

	Node target = search(D->root, k);

	if(target == D->cursor)
	{
		D->iteration = 0;		
	}

	if(target->left == NULL)
	{
		transplant(D, target, target->right);
		freeNode(&target);
		D->size--;
		return;
	}

	if(target->right == NULL)
	{
		transplant(D, target, target->left);
		freeNode(&target);
		D->size--;
		return;
	}

	else
	{
		Node replace = findMin(target->right);

		if(replace->parent != target)
		{
			transplant(D, replace, replace->right);
			replace->right = target->right;
			replace->right->parent = replace;
		}

		transplant(D, target, replace);
		replace->left = target->left;
		replace->left->parent = replace;
		freeNode(&target);
		D->size--;
		return;
	}
}

// makeEmpty()
// Reset Dictionary D to the empty state, containing no pairs.
void makeEmpty(Dictionary D)
{
	while(D->size != 0)
	{
		delete(D, D->root->key);
	}

	D->cursor = NULL;
	D->root = NULL;
	D->size = 0;
	D->iteration = 0;
}

// beginForward()
// If D is non-empty, starts a forward iteration over D at the first key
// (as defined by the order operator KEY_CMP()), then returns the first
// value. If D is empty, returns VAL_UNDEF.
VAL_TYPE beginForward(Dictionary D)
{
	if( D==NULL )
	{
			printf("Dictionary Error: calling beginForward() on NULL Dictionary reference\n");
			exit(1);
	}

	if(D->size == 0)
	{
		return(VAL_UNDEF);
	}

	D->iteration = 1;

	Node target = findMin(D->root);
	D->cursor = target;
	return(target->value);
}

// beginReverse()
// If D is non-empty, starts a reverse iteration over D at the last key
// (as defined by the order operator KEY_CMP()), then returns the last
// value. If D is empty, returns VAL_UNDEF.
VAL_TYPE beginReverse(Dictionary D)
{
	if( D==NULL )
	{
			printf("Dictionary Error: calling beginReverse() on NULL Dictionary reference\n");
			exit(1);
	}

	if(D->size == 0)
	{
		return(VAL_UNDEF);
	}

	D->iteration = 1;
	
	Node target = findMax(D->root);
	D->cursor = target;
	return(target->value);
}

// currentKey()
// If an iteration (forward or reverse) over D has started, returns the
// the current key. If no iteration is underway, returns KEY_UNDEF.
KEY_TYPE currentKey(Dictionary D)
{
	if( D==NULL )
	{
		printf("Dictionary Error: calling currentKey() on NULL Dictionary reference\n");
		exit(1);
	}

	if(D->iteration == 0)
	{
		return(KEY_UNDEF);
	}

	return(D->cursor->key);
}

// currentVal()
// If an iteration (forward or reverse) over D has started, returns the
// value corresponding to the current key. If no iteration is underway,
// returns VAL_UNDEF.
VAL_TYPE currentVal(Dictionary D)
{
	if( D==NULL )
	{
		printf("Dictionary Error: calling currentVal() on NULL Dictionary reference\n");
		exit(1);
	}

	if(D->iteration == 0)
	{
		return(VAL_UNDEF);
	}

	return(D->cursor->value);
}


// next()
// If an iteration (forward or reverse) over D has started, and has not
// reached the last pair, moves to the next key in D (as defined by the
// order operator KEY_CMP()), and returns the value corresponding to the
// new key. If an iteration has started, and has reached the last pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway,
// returns VAL_UNDEF.
VAL_TYPE next(Dictionary D)
{
	if( D==NULL )
	{
		printf("Dictionary Error: calling next() on NULL Dictionary reference\n");
		exit(1);
	}

	if(D->iteration == 0)
	{
		return(VAL_UNDEF);
	}

	if(D->cursor == findMax(D->root))
	{
		D->cursor = NULL;
		D->iteration = 0;
		return(VAL_UNDEF);
	}

	Node target = getSuccesor(D->cursor);
	D->cursor = target;
	return(target->value);
}

// prev()
// If an iteration (forward or reverse) over D has started, and has not
// reached the first pair, moves to the previous key in D (as defined by the
// order operator KEY_CMP()), and returns the value corresponding to the
// new key. If an iteration has started, and has reached the first pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway,
// returns VAL_UNDEF.
VAL_TYPE prev(Dictionary D)
{
	if( D==NULL )
	{
		printf("Dictionary Error: calling prev() on NULL Dictionary reference\n");
		exit(1);
	}

	if(D->iteration == 0)
	{
		return(VAL_UNDEF);
	}

	if(D->cursor == findMin(D->root))
	{
		D->cursor = NULL;
		D->iteration = 0;
		return(VAL_UNDEF);
	}

	Node target = getPred(D->cursor);
	D->cursor = target;
	return(target->value);
}


// Other operations -----------------------------------------------------------

// inOrderPrint()
void inOrderPrint(Node N, FILE* out)
{
	if(N != NULL)
	{
		inOrderPrint(N->left, out);
		fprintf(out, "%s %d\n", N->key, N->value);
		inOrderPrint(N->right, out);
	}
}

// printDictionary()
// Prints a text representation of D to the file pointed to by out. Each key-
// value pair is printed on a single line, with the two items separated by a
// single space.  The pairs are printed in the order defined by the operator
// KEY_CMP().
void printDictionary(FILE* out, Dictionary D)
{
	if( D==NULL )
	{
		printf("Dictionary Error: calling printDictionary() on NULL Dictionary reference\n");
		exit(1);
	}

	if( D->size == 0 )
	{
		printf("Dictionary Error: calling printDictionary() on empty Dictionary reference\n");
		exit(1);
	}

	inOrderPrint(D->root, out);
}
