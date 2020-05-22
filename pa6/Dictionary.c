//-----------------------------------------------------------------------------
// Dictionary.c
// Implementation file for Dictionary ADT storing (key, value) pairs of types KEY_TYPE
// and VAL_TYPE.
//-----------------------------------------------------------------------------
// Rishab Aida
// raida
// PA6

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define KEY_TYPE char*
#define VAL_TYPE int*
#define KEY_UNDEF NULL
#define VAL_UNDEF NULL
#define KEY_FORMAT "%s"
#define VAL_FORMAT "%d"
#define KEY_CMP(x,y) strcmp((x),(y))
#define RED 1
#define BLACK 0

// private NodeObj type
typedef struct NodeObj
{
	KEY_TYPE key;
	VAL_TYPE value;
	int color;
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
	Node NIL;
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
	N->color = 0;
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
	D->NIL = newNode(KEY_UNDEF, VAL_UNDEF);
}

// freeDictionary()
// Frees heap memory associated with *pD, sets *pD to NULL.
void freeDictionary(Dictionary* pD)
{
	if( pD!=NULL && *pD!=NULL)
	{
		makeEmpty(*pD);
		freeNode(&((*pD)->NIL));
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
Node search(Dictionary D, Node N, KEY_TYPE k)
{
	if(N == D->NIL || N == NULL)
	{
		return(N);
	}

	if(k == N->key)
	{
		return(N);
	}

	if(KEY_CMP(k, N->key) < 0)
	{
		return(search(D, N->left, k));
	}

	else
	{
		return(search(D, N->right, k));
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
	
	if(D->size == 0)
	{
		return(VAL_UNDEF);
	}

	Node target = search(D, D->root, k);

	if(target == D->NIL || target == NULL)
	{
		return(VAL_UNDEF);
	}

	else
	{
		return(target->value);
	}
}


// Manipulation procedures ----------------------------------------------------

void leftRotate(Dictionary D, Node X)
{
	Node Y = X->right;

	X->right = Y->left;

	if(Y->left != D->NIL)
	{
		Y->left->parent = X;
	}

	Y->parent = X->parent;

	if(X->parent == D->NIL)
	{
		D->root = Y;
	}

	else if(X == X->parent->left)
	{
		X->parent->left = Y;
	}

	else
	{
		X->parent->right = Y;
	}

	Y->left = X;
	X->parent = Y;
}

void rightRotate(Dictionary D, Node X)
{
	Node Y = X->left;

	X->left = Y->right;

	if(Y->right != D->NIL)
	{
		Y->right->parent = X;
	}

	Y->parent = X->parent;

	if(X->parent == D->NIL)
	{
		D->root = Y;
	}

	else if(X == X->parent->right)
	{
		X->parent->right = Y;
	}

	else
	{
		X->parent->left = Y;
	}

	Y->right = X;
	X->parent = Y;
}

void insertFix(Dictionary D, Node Z)
{
	Node Y;
	while(Z->parent->color == RED)
	{
		if(Z->parent == Z->parent->parent->left)
		{
			Y = Z->parent->parent->right;
			if(Y->color == RED)
			{
				Z->parent->color = BLACK;
				Y->color = BLACK;
				Z->parent->parent->color = RED;
				Z = Z->parent->parent;
			}

			else
			{
				if(Z == Z->parent->right)
				{
					Z = Z->parent;
					leftRotate(D, Z);
				}
				Z->parent->color = BLACK;
				Z->parent->parent->color = RED;
				rightRotate(D, Z->parent->parent);
			}
		}

		else
		{
			Y = Z->parent->parent->left;
			if(Y->color == RED)
			{
				Z->parent->color = BLACK;
				Y->color = BLACK;
				Z->parent->parent->color = RED;
				Z = Z->parent->parent;
			}

			else
			{
				if(Z == Z->parent->left)
				{
					Z = Z->parent;
					rightRotate(D, Z);
				}
				Z->parent->color = BLACK;
				Z->parent->parent->color = RED;
				leftRotate(D, Z->parent->parent);
			}
		}
	}
	D->root->color = BLACK;
}

void deleteFix(Dictionary D, Node X)
{
	while(X != D->root && X->color == BLACK)
	{
		Node W;
		if(X == X->parent->left)
		{
	         W = X->parent->right;
	         if(W->color == RED)
	         {
	            W->color = BLACK;
	            X->parent->color = RED;
	            leftRotate(D, X->parent);
	            W = X->parent->right;
	         }

	         if(W->left->color == BLACK && W->right->color == BLACK)
	         {
	            W->color = RED;
	            X = X->parent;
	         }

	         else
	         {
	        	 if(W->right->color == BLACK)
	        	 {
	        		 W->left->color = BLACK;
	        		 W->color = RED;
	        		 rightRotate(D, W);
	        		 W = X->parent->right;
	            }
	            W->color = X->parent->color;
	            X->parent->color = BLACK;
	            W->right->color = BLACK;
	            leftRotate(D, X->parent);
	            X = D->root;
	         }
		}

		else
		{
			W = X->parent->left;
			if(W->color == RED)
			{
				W->color = BLACK;
	            X->parent->color = RED;
	            rightRotate(D, X->parent);
	            W = X->parent->left;
	         }

	         if(W->right->color == BLACK && W->left->color == BLACK)
	         {
	            W->color = RED;
	            X = X->parent;
	         }

	         else
	         {
	        	 if(W->left->color == BLACK)
	        	 {
	        		 W->right->color = BLACK;
	        		 W->color = RED;
	        		 leftRotate(D, W);
	        		 W = X->parent->left;
	        	 }
	        	 W->color = X->parent->color;
	        	 X->parent->color = BLACK;
	        	 W->left->color = BLACK;
	        	 rightRotate(D, X->parent);
	        	 X = D->root;
	         }
		}
	}
	X->color = BLACK;
}

// findMin()
Node findMin(Dictionary D, Node N)
{
        Node M = N;
        while(M->left != D->NIL)
        {
                M = M->left;
        }

        return(M);
}

// findMax()
Node findMax(Dictionary D, Node N)
{
        Node M = N;
        while(M->right != D->NIL)
        {
                M = M->right;
        }

        return(M);
}

// getSuccesor
Node getSuccesor(Dictionary D, Node N)
{
        if(N->right != D->NIL)
        {
                return(findMin(D, N->right));
        }

        Node temp = N->parent;

        while(temp != D->NIL && N == temp->right)
        {
                N = temp;
                temp = temp->parent;
        }

        return(temp);
}

//getPred()

Node getPred(Dictionary D, Node N)
{
        if(N->left != D->NIL)
        {
                return(findMax(D, N->left));
        }

        Node temp = N->parent;

        while(temp != D->NIL && N == temp->left)
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

	Node N = newNode(k, v);
	Node Y = D->NIL;
	Node X;

	if(D->size == 0)
	{
		D->root = N;
		N->color = BLACK;
		N->left = D->NIL;
		N->right = D->NIL;
		N->parent = D->NIL;
		D->size++;
		return;
	}

 	if(getUnique(D) == 1)
        {
                if(lookup(D, k) != VAL_UNDEF)
                {
                        printf("Dictionary Error: getUnique is true. Key already exists");
                        exit(1);
                }
        }


	X = D->root;

	while(X != D->NIL)
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

	N->color = RED;
	N->left = D->NIL;
	N->right = D->NIL;
	insertFix(D, N);
	D->size++;
}

// transplant()
void transplant(Dictionary D, Node U, Node V)
{
	if(U->parent == D->NIL)
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

	V->parent = U->parent;
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

	if(lookup(D, k) == VAL_UNDEF && search(D, D->root, k) == D->NIL)
	{
		printf("Dictionary Error: trying to delete non-existent key");
		exit(1);
	}

	Node X;
	Node target = search(D, D->root, k);
	Node Y;
	Y = target;
	int originalColor = Y->color;

	if(target->left == D->NIL)
	{
		X = target->right;
		transplant(D, target, target->right);
	}

	else if(target->right == D->NIL)
	{
		X = target->left;
		transplant(D, target, target->left);
	}

	else
	{
		Y = findMin(D, target->right);
		originalColor = Y->color;
		X = Y->right;
		if(Y->parent == target)
		{
			X->parent = Y;
		}

		else
		{
			transplant(D, Y, Y->right);
			Y->right = target->right;
			Y->right->parent = Y;
		}

		transplant(D, target, Y);
		Y->left = target->left;
		Y->left->parent = Y;
		Y->color = target->color;
	}

	if(originalColor == BLACK)
	{
		deleteFix(D, X);
	}

	if(target == D->cursor)
	{
		D->cursor = NULL;
		D->iteration = 0;
	}

	freeNode(&target);
	D->size--;
	return;
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

	Node target = findMin(D, D->root);
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

	Node target = findMax(D, D->root);
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

	if(D->cursor == findMax(D, D->root))
	{
		D->cursor = NULL;
		D->iteration = 0;
		return(VAL_UNDEF);
	}

	Node target = getSuccesor(D, D->cursor);
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

	if(D->cursor == findMin(D, D->root))
	{
		D->cursor = NULL;
		D->iteration = 0;
		return(VAL_UNDEF);
	}

	Node target = getPred(D, D->cursor);
	D->cursor = target;
	return(target->value);
}


// Other operations -----------------------------------------------------------

// inOrderPrint()
void inOrderPrint(Dictionary D, Node N, FILE* out)
{
	if(N != D->NIL)
	{
		inOrderPrint(D, N->left, out);
		fprintf(out, "%s", N->key);
		inOrderPrint(D, N->right, out);
	}
}

void preOrderPrint(Dictionary D, Node N, FILE* out)
{
	if(N != D->NIL)
	{
		fprintf(out, "%s", N->key);
		preOrderPrint(D, N->left, out);
		preOrderPrint(D, N->right, out);
	}
}

void postOrderPrint(Dictionary D, Node N, FILE* out)
{
	if(N != D->NIL)
	{
		postOrderPrint(D, N->left, out);
		postOrderPrint(D, N->right, out);
		fprintf(out, "%s", N->key);
	}
}

// printDictionary()
// Prints a text representation of D to the file pointed to by out. Each key-
// value pair is printed on a single line, with the two items separated by a
// single space.  The pairs are printed in the order defined by the operator
// KEY_CMP().
void printDictionary(FILE* out, Dictionary D, const char* ord)
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

	if(strcmp(ord, "in") == 0)
	{
		inOrderPrint(D, D->root, out);
	}

	if(strcmp(ord, "pre") == 0)
	{
		preOrderPrint(D, D->root, out);
	}

	if(strcmp(ord, "post") == 0)
	{
		postOrderPrint(D, D->root, out);
	}
}
