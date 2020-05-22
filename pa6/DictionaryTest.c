// DictionaryTest.c
// A Test file for the Dictionary ADT
// Rishab Aida
// raida
// PA5

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Dictionary.h"

#define IN "in"
#define PRE "pre"
#define POST "post"


int main(int argc, char* argv[])
{
	Dictionary D = newDictionary(1);
	printf("%d", size(D));
	insert(D, "a", NULL);
	printf("%d", size(D));
        insert(D, "b", NULL);
	printf("%d", size(D));
//        insert(D, "c", NULL);
//	printf("%d", size(D));
//        insert(D, "e", NULL);
//	printf("%d", size(D));
//	printf("\n");
//	freeDictionary(&D);

//	delete(D, "b");
//	delete(D, "a");
freeDictionary(&D);
//	printf("%d", lookup(D, "a"));

//	delete(D, "a");
   //    printf("%d", size(D));
  //      printf("\n");
//        printDictionary(stdout, D);
 
}

