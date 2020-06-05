//-----------------------------------------------------------------------------
// Shuffle.cpp
// Top Level Client for the List ADT
//----------------------------------------------------------------------------
// Rishab Aida
// raida
// PA7

#include<iostream>
#include<fstream>
#include<string>
#include<iostream>
#include"List.h"

using namespace std;

void shuffle(List& L)
{
	// All variables used in loops
	List firstHalf;
	List secondHalf;
	int looper = 0;
	bool odd;
	int input = L.size();

	// Determines if List size is odd
	int checker = input%2;

	if(checker == 1)
	{
		odd = true;
	}

	else
	{
		odd = false;
	}

	int half = input/2;
	int counter2 = 0;

	// Seperates List into halves
	L.moveFront();
	for(looper = 0; looper < half; looper++)
	{
		firstHalf.insertBefore(L.peekNext());
		L.moveNext();
	}

	while(L.position() != L.size())
	{
		secondHalf.insertBefore(L.peekNext());
		L.moveNext();
	}

	firstHalf.moveFront();
	secondHalf.moveFront();

	L.clear();

	// Shuffles the halves together
	for(counter2 = 0; counter2 < half; counter2++)
	{
		L.insertBefore(secondHalf.peekNext());
		L.insertBefore(firstHalf.peekNext());
		firstHalf.moveNext();
		secondHalf.moveNext();
	}

	// Case if List has an odd amount
	if(odd)
	{
		L.insertBefore(secondHalf.peekNext());
	}

	firstHalf.clear();
	secondHalf.clear();
}

int main(int argc, char * argv[])
{
	// Checks for correct amount of arguments
	if(argc != 2)
	{
		cerr << "Usage: " << argv[0] << " <inputted integer>" << endl;
		return(EXIT_FAILURE);
	}
	
	// Takes in user input
	int userInput = atoi(argv[1]);

	// Lists and variables used
	List L;
	List compare;
	int i;
	bool first;
	int counter;

	// Prints header
	cout << "deck size       shuffle count" << endl;
	cout << "------------------------------" << endl;

	// For loop building up to user input
	for(int j = 1; j<=userInput; j++)
	{
		counter = 0;
		L.clear();
		compare.clear();
		// Fills in Lists
		for(i = 0; i < j; i++)
		{
			L.insertBefore(i);
			compare.insertBefore(i);
		}

		first = true;

		// Determines order of List
		while(!L.equals(compare) || first)
		{
			first = false;
			counter++;
			shuffle(L);
		}
		cout << " " << j << "\t\t " << counter << endl;
	}
	return(0);
}




