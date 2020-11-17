//-----------------------------------------------------------------------------
// List.cpp
// Implementation file for List ADT. List is a double ended queue with a vertical cursor standing between elements. The cursor position is always defined
// to be an int in the range 0 (at front) to length of List (at back).
// An empty list consists of the vertical cursor only, with no elements.
//-----------------------------------------------------------------------------
// Rishab Aida
// raida
// PA7

#include<iostream>
#include<string>
#include "List.h"

using namespace std;

// Private Constructor -----------------------------------------------

// Node Constructor
List::Node::Node(int x)
{
	data = x;
	next = nullptr;
	prev = nullptr;
}

// Class Constructors & Destructors ----------------------------------------

// Creates new List in the empty state.
List::List()
{
	frontDummy = new Node(-1);
	backDummy = new Node(-2);
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	pos_cursor = 0;
	num_elements = 0;
}

// Copy constructor.
List::List(const List& L)
{
	frontDummy = new Node(-1);
	backDummy = new Node(-2);
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	pos_cursor = 0;
	num_elements = 0;

	if(L.num_elements == 0)
	{
		return;
	}

	Node* N = L.frontDummy->next;
	Node* M = new Node(N->data);
	frontDummy->next = M;
	M->prev = frontDummy;
	Node* target = frontDummy->next;

	while(N->next != L.backDummy)
	{
		N = N->next;
		M = new Node(N->data);
		target->next = M;
		M->prev = target;
		target = target->next;
	}

	target->next = backDummy;
	backDummy->prev = target;

	num_elements = L.num_elements;
	pos_cursor = L.pos_cursor;
}

// Destructor
List::~List()
{
	clear();
	delete backDummy;
	delete frontDummy;
}


// Access functions --------------------------------------------------------

// isEmpty()
// Returns true if this List is empty, false otherwise.
bool List::isEmpty()
{
	if(num_elements == 0)
	{
		return true;
	}

	else
	{
		return false;
	}
}

// size()
// Returns the size of this List.
int List::size()
{
	return(num_elements);
}

// position()
// Returns the position of the cursor in this List. The value returned
// will be in the range 0 to size().
int List::position()
{
	return(pos_cursor);
}


// Manipulation procedures -------------------------------------------------

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront()
{
	beforeCursor = frontDummy;
	afterCursor = frontDummy->next;
	pos_cursor = 0;
}

// moveBack()
// Moves cursor to position size() in this List.
void List::moveBack()
{
	afterCursor = backDummy;
	beforeCursor = backDummy->prev;
	pos_cursor = num_elements;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<size()
int List::peekNext()
{
	if( pos_cursor == num_elements )
	{
	      cerr << "List Error: calling peekNext() on invalid cursor position" << endl;
	      exit(EXIT_FAILURE);
	}

	return(afterCursor->data);
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
int List::peekPrev()
{
	if( pos_cursor == 0 )
	{
	      cerr << "List Error: calling peekPrev() on invalid cursor position" << endl;
	      exit(EXIT_FAILURE);
	}

	return(beforeCursor->data);
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over.
// pre: position()<size()
int List::moveNext()
{
	if( pos_cursor == num_elements )
	{
		cerr << "List Error: calling moveNext() on invalid cursor position" << endl;
		exit(EXIT_FAILURE);
	}

	pos_cursor++;
	beforeCursor = beforeCursor->next;
	afterCursor = afterCursor->next;

	return(beforeCursor->data);

}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over.
// pre: position()>0
int List::movePrev()
{
	if( pos_cursor == 0 )
	{
		cerr << "List Error: calling movePrev() on invalid cursor position" << endl;
		exit(EXIT_FAILURE);
	}

	pos_cursor--;
	beforeCursor = beforeCursor->prev;
	afterCursor = afterCursor->prev;

	return(afterCursor->data);
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(int x)
{
	Node* N = new Node(x);
	N->prev = beforeCursor;
	N->next = afterCursor;
	beforeCursor->next = N;
	afterCursor->prev = N;
	afterCursor = N;
	num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(int x)
{
	Node* N = new Node(x);
	N->prev = beforeCursor;
	N->next = afterCursor;
	beforeCursor->next = N;
	afterCursor->prev = N;
	beforeCursor = N;
	num_elements++;
	pos_cursor++;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<size()
void List::eraseAfter()
{
	if( pos_cursor == num_elements )
	{
		cerr << "List Error: calling eraseAfter() on invalid cursor position" << endl;
		exit(EXIT_FAILURE);
	}

	if(num_elements == 0)
	{
		cerr << "List Error: calling eraseAfter() on an empty List" << endl;
		exit(EXIT_FAILURE);
	}

	Node* target = afterCursor;
	Node* targetBefore = beforeCursor;
	Node* targetNext = afterCursor->next;

	targetBefore->next = targetNext;
	targetNext->prev = targetBefore;
	afterCursor = targetNext;
	delete target;
	num_elements--;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore()
{
	if( pos_cursor == 0 )
	{
		cerr << "List Error: calling eraseBefore() on invalid cursor position" << endl;
		exit(EXIT_FAILURE);
	}

	if(num_elements == 0)
	{
		cerr << "List Error: calling eraseBefore() on an empty List" << endl;
		exit(EXIT_FAILURE);
	}

	Node* target = beforeCursor;
	Node* targetBefore = target->prev;
	Node* targetNext = afterCursor;

	targetBefore->next = targetNext;
	targetNext->prev = targetBefore;
	beforeCursor = targetBefore;
	delete target;
	num_elements--;
	pos_cursor--;
}

// findNext()
// Starting from the current cursor position, performs a linear search (in
// the direction front-to-back) for the first occurrence of the element x.
// If x is found, places the cursor immediately after the found element (so
// eraseBefore() would remove the found element), and returns the final
// cursor position. If x is not found, places the cursor at position size(),
// and returns -1.
int List::findNext(int x)
{
	Node* reader = beforeCursor;
	moveNext();
	while(pos_cursor != num_elements)
	{
		reader = beforeCursor;
		if(reader->data == x)
		{
			return pos_cursor;
		}
		moveNext();
	}

	if(beforeCursor->data == x)
	{
		return pos_cursor;
	}

	else
	{
		return -1;
	}
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in
// the direction back-to-front) for the first occurrence of the element x.
// If x is found, places the cursor immediately before the found element (so
// eraseAfter() would remove the found element), and returns the final
// cursor position. If x is not found, places the cursor at position 0, and
// returns -1.
int List::findPrev(int x)
{
	Node* reader = afterCursor;
	movePrev();
	while(pos_cursor != 0)
	{
		reader = afterCursor;
		if(reader->data == x)
		{
			return pos_cursor;
		}
		movePrev();
	}

	if(afterCursor->data == x)
	{
		return pos_cursor;
	}

	else
	{
		return -1;
	}
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique data
// values. The order of the remaining elements is obtained by retaining
// the frontmost occurrance of each element, and removing all other
// occurances. The cursor is not moved with respect to the retained
// elements, i.e. it lies between the same two retained elements that it
// did before cleanup() was called.
void List::cleanup()
{		
	Node* holder = nullptr;
	int counter = 0;
	Node* target = nullptr;
	Node* counter2 = nullptr;	
	Node* scroller = frontDummy->next;
	

	while(scroller != backDummy)
	{
		target = scroller->next;
		holder = scroller;

		while(target != backDummy)
		{
			if(target->data != scroller->data)
			{ 
				holder = target;
				target = holder->next;
       			}			

			else
			{
				num_elements--;
                                target->next->prev = holder;
                                holder->next = target->next;

				if(target == afterCursor)
                                {
                                        afterCursor = target->next;
                                }

				if(target == beforeCursor)
				{
					pos_cursor--;
					beforeCursor = holder;
				}
				delete target;
				target = holder->next;
			}
		}
		
		if(pos_cursor != 0)
        	{
                	counter = 1;

                	counter2 = frontDummy->next;

                	while(counter2 != beforeCursor)
                	{
                        	counter2 = counter2->next;
                        	counter++;
                	}
                	pos_cursor = counter;
        	}
		scroller = scroller->next;
	}                     			
}

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear()
{
	Node* N = frontDummy->next;
	Node* M = nullptr;

	while(N != backDummy)
	{
		M = N;
		N = N->next;
		delete M;
	}

	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	num_elements = 0;
	pos_cursor = 0;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
}

// concat()
// Returns a new List consisting of the elements of this List, followed
// the elements of L. The returned List's cursor will be at its front
// (position 0).
List List::concat(const List& L)
{
	List J;
	Node* N = this->frontDummy->next;
	Node* M = L.frontDummy->next;

	while(N != this->backDummy)
	{
		J.insertBefore(N->data);
		N = N->next;
	}

	while(M != L.backDummy)
	{
		J.insertBefore(M->data);
		M = M->next;
	}

	J.moveFront();
	J.num_elements = this->num_elements + L.num_elements;
	return J;
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this List consisting of a comma
// separated sequence of elements, surrounded by parentheses.
string List::to_string()
{
	Node* N = frontDummy->next;
	string s = "(";

	while(N != backDummy)
	{
		s += std::to_string(N->data);
		
 		if(N->next != backDummy)
		{
			s += ", ";
		}

		N = N->next;
	}

	s += ")";

	return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R)
{
	bool eq = false;
	Node* N = nullptr;
	Node* r = nullptr;

	eq = ( num_elements == R.num_elements);
	N = frontDummy->next;
	r = R.frontDummy->next;
	while( eq && N!=nullptr && r!=nullptr)
	{
		eq = (N->data == r->data);
		N = N->next;
		r = r->next;
	}

	return eq;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
ostream& operator<<( ostream& stream, List& L )
{
	return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The
// cursors in both Lists are unchanged are unchanged.
bool operator==( List& A, const List& B )
{
	return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L )
{
	if( this != &L)
	{
		List temp = L;
		
		std::swap(num_elements, temp.num_elements);
		std::swap(pos_cursor, temp.pos_cursor);
		std::swap(backDummy, temp.backDummy);
		std::swap(frontDummy, temp.frontDummy);
		std::swap(beforeCursor, temp.beforeCursor);
		std::swap(afterCursor, temp.afterCursor);
	}
	
	return *this;
}

