//-----------------------------------------------------------------------------
// BigIntegerTest.c
// Test Suite for the BigInteger ADT
//-----------------------------------------------------------------------------
// Rishab Aida
// raida
// PA2

#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"BigInteger.h"

int main(int argc, char* argv[])
{
	char* input = "2";

	char* input2 = "4";

	BigInteger N = stringToBigInteger(input);
	BigInteger A = stringToBigInteger(input2);

	printBigInteger(stdout, prod(N, A));
	printBigInteger(stdout, diff(N, A));
 	printBigInteger(stdout, sum(N, A));
	printf("\n");
	printf("%d", compare(N, A)); 	
}
