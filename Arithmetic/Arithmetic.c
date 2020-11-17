//-----------------------------------------------------------------------------
// Arithmetic.c
// File that sorts input file alphabetically
//-----------------------------------------------------------------------------
// Rishab Aida
// raida
// PA2

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
#include "BigInteger.h"

int main(int argc, char * argv[])
{
	FILE *in;
	FILE *out;
	int size1;
	int size2;

	// Check command line for correct number of arguments
	if( argc != 3)
	{
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	// Open files for reading and writing
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");

    if( in==NULL )
    {
    	printf("Unable to open file %s for reading\n", argv[1]);
    	exit(1);
    }

    if( out==NULL )
    {
    	printf("Unable to open file %s for writing\n", argv[2]);
    	exit(1);
    }

 	fscanf(in, "%d\n", &size1);

	int sign = 0;
	char signCheck = fgetc(in);
	if(signCheck == '+' || signCheck == '-')
	{
		sign = 1;
	}

	char input1[size1 + sign + 1];
	fseek(in, -1, SEEK_CUR);
	fgets(input1, size1 + sign + 1, in);

	fscanf(in, "%d\n", &size2);

        sign = 0;
        signCheck = fgetc(in);
        if(signCheck == '+' || signCheck == '-')
        {
                sign = 1;
        }

        char input2[size2 + sign + 1];
        fseek(in, -1, SEEK_CUR);
        fgets(input2, size2 + sign + 1, in);
  

    	BigInteger A = stringToBigInteger(input1);
    	BigInteger B = stringToBigInteger(input2);

    	// Print A
    	printBigInteger(out, A);
    	fprintf(out, "\n");
	fprintf(out, "\n");

    	// Print B
    	printBigInteger(out, B);
    	fprintf(out, "\n");
	fprintf(out, "\n");	

    	// Print A+B
    	BigInteger sum1 = sum(A, B);
    	printBigInteger(out, sum1);
	fprintf(out, "\n");
	fprintf(out, "\n");
    	freeBigInteger(&sum1);

    	// Print A-B
    	BigInteger difference1 = diff(A, B);
    	printBigInteger(out, difference1);
    	fprintf(out, "\n");
	fprintf(out, "\n");
    	freeBigInteger(&difference1);

    	// Print A-A
    	BigInteger difference2 = diff(A, A);
    	printBigInteger(out, difference2);
	fprintf(out, "\n");
	fprintf(out, "\n");
    	freeBigInteger(&difference2);

    	// Print 3A-2B
    	char* threeString = "3";
    	BigInteger three = stringToBigInteger(threeString);
    	char* twoString = "2";
    	BigInteger two = stringToBigInteger(twoString);
    	// 3A
    	BigInteger product1 = prod(three, A);
    	// 2A
	BigInteger product2 = prod(two, B);
	BigInteger difference3 = diff(product1, product2);
    	printBigInteger(out, difference3);
    	fprintf(out, "\n");
	fprintf(out, "\n");
    	freeBigInteger(&two);
    	freeBigInteger(&three);
    	freeBigInteger(&product1);
    	freeBigInteger(&product2);
    	freeBigInteger(&difference3);

    	// Print AB
    	BigInteger product3 = prod(A, B);
    	printBigInteger(out, product3);
    	fprintf(out, "\n");
	fprintf(out, "\n");
    	freeBigInteger(&product3);

    	// Print AA
    	BigInteger product4 = prod(A, A);
    	printBigInteger(out, product4);
    	fprintf(out, "\n");
	fprintf(out, "\n");
    	freeBigInteger(&product4);

    	// Print BB
    	BigInteger product5 = prod(B, B);
    	printBigInteger(out, product5);
    	fprintf(out, "\n");
	fprintf(out, "\n");
    	freeBigInteger(&product5);

    	// Print 9AAAA + 16BBBBB
    	char* nineString = "9";
    	BigInteger nine = stringToBigInteger(nineString);
    	char* sixteenString = "16";
    	BigInteger sixteen = stringToBigInteger(sixteenString);
    	// AA
    	BigInteger product6 = prod(A, A);
    	// AAA
    	BigInteger product7 = prod(product6, A);
    	// AAAA
    	BigInteger product8 = prod(product7, A);
    	// BB
    	BigInteger product9 = prod(B, B);
    	// BBB
    	BigInteger product10 = prod(product9, B);
    	// BBBB
    	BigInteger product11 = prod(product10, B);
    	// BBBBB
    	BigInteger product12 = prod(product11, B);
    	// 9AAAA
    	BigInteger product13 = prod(product8, nine);
    	// 16BBBBB
    	BigInteger product14 = prod(product12, sixteen);
    	// Add them
    	BigInteger sum2 = sum(product13, product14);

    	printBigInteger(out, sum2);
	fprintf(out, "\n");
        fprintf(out, "\n");

    	freeBigInteger(&nine);
    	freeBigInteger(&sixteen);
    	freeBigInteger(&product6);
    	freeBigInteger(&product7);
    	freeBigInteger(&product8);
    	freeBigInteger(&product9);
    	freeBigInteger(&product10);
    	freeBigInteger(&product11);
    	freeBigInteger(&product12);
    	freeBigInteger(&product13);
    	freeBigInteger(&product14);
    	freeBigInteger(&sum2);

    	freeBigInteger(&A);
    	freeBigInteger(&B);

    	// close files
    	fclose(in);
    	fclose(out);

    	return(0);

}
