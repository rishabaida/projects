// DictionaryTest.c
// A Test file for the Dictionary ADT
// Rishab Aida
// raida
// PA5

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Dictionary.h"

int main(int argc, char* argv[])
{
	Dictionary D = newDictionary(1);
	printf("%d", size(D));
	insert(D, "a", 1);
	printf("%d", size(D));
        insert(D, "b", 2);
	printf("%d", size(D));
        insert(D, "c", 3);
	printf("%d", size(D));
        insert(D, "e", 5);
	printf("%d", size(D));
	printf("\n");
        printDictionary(stdout, D);

	printf("%d", lookup(D, "a"));

	delete(D, "a");
       printf("%d", size(D));
        printf("\n");
        printDictionary(stdout, D);
 
}

