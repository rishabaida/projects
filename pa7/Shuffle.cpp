//-----------------------------------------------------------------------------
// Shuffle.cpp
// Top Level Client for the List ADT
//----------------------------------------------------------------------------
// Rishab Aida
// raida
// PA7

#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<fstream>
#include<string>
#include<iostream>
#include"List.h"

using namespace std;

int main(int argc, char * argv[])
{

	if(argc != 2)
	{
		cerr << "Usage: " << argv[0] << " <inputted integer>" << endl;
		return(EXIT_FAILURE);
	}

	int input = atoi(argv[1]);


	List L;
	List compare;
	List firstHalf;
	List secondHalf;
	int looper = 0;
	bool odd;

	cout << "deck size       shuffle count" << endl;
	cout << "------------------------------" << endl;

	for(int i = 0; i < input; i++)
	{
		L.insertBefore(i);
		compare.insertBefore(i);
	}

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

	int counter = 0;
	int counter2 = 0;

	bool first = true;             

	while(!L.equals(compare) || first)
	{
		first = false;
		counter++;
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

		for(counter2 = 0; counter2 < half; counter2++)
		{
			L.insertBefore(secondHalf.peekNext());
			L.insertBefore(firstHalf.peekNext());
			firstHalf.moveNext();
			secondHalf.moveNext();
		}

		if(odd)
		{
			L.insertBefore(secondHalf.peekNext());
		}

		firstHalf.clear();
		secondHalf.clear();
	}

	cout << " " << input << "\t\t " << counter << endl;

	return(0);
}
