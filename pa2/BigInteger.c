//-----------------------------------------------------------------------------
// BigInteger.c
// Implementation file for BigInteger ADT
//-----------------------------------------------------------------------------
// Rishab Aida
// raida
// PA2

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
#include "BigInteger.h"

#define POWER 9
#define BASE 1000000000

// Exported type -------------------------------------------------------------

// BigInteger reference type
typedef struct BigIntegerObj
{
	int sign;
	List magnitude;
} BigIntegerObj;

typedef BigIntegerObj* BigInteger;

// Constructors-Destructors ---------------------------------------------------

// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state.
BigInteger newBigInteger()
{
	BigInteger BI = malloc(sizeof(BigIntegerObj));
	BI->sign = 0;
	BI->magnitude = newList();
	return(BI);
}

// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger* pN)
{
	if( pN!=NULL && *pN!=NULL)
	{
		freeList(&(*pN)->magnitude);
		free(*pN);
		*pN = NULL;
	}
}

// Access functions -----------------------------------------------------------

// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero
// state.
int sign(BigInteger N)
{
	if( N==NULL )
	{
		printf("BigInteger Error: calling sign() on NULL BigInteger reference\n");
		exit(1);
	}

	return N->sign;
}

// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B)
{
	if( A==NULL || B==NULL)
	{
		printf("BigInteger Error: calling compare() on NULL BigInteger reference\n");
		exit(1);
	}

	if(A->sign > B->sign)
	{
		return(1);
	}

	if(B->sign > A->sign)
	{
		return(-1);
	}

	if(B->sign == 0 && A->sign == 0)
	{
		return(0);
	}

	if(B->sign == -1 && A->sign == -1)
	{
		if(length(B->magnitude) > length(A->magnitude))
		{
			return(1);
		}

		if(length(A->magnitude) > length(B->magnitude))
		{
			return(-1);
		}

		if(length(B->magnitude) == length(A->magnitude))
		{
			moveFront(A->magnitude);
			moveFront(B->magnitude);

			while(index(A->magnitude) != -1 && index(B->magnitude) != -1)
			{

				if(get(A->magnitude) > get(B->magnitude))
				{
					return(-1);
				}

				if(get(A->magnitude) < get(B->magnitude))
				{
					return(1);
				}

				if(get(A->magnitude) == get(B->magnitude))
				{
					moveNext(A->magnitude);
					moveNext(B->magnitude);
				}
			}

			if(index(A->magnitude) == -1 && index(B->magnitude) == -1)
			{
				return(0);
			}
		}
	}

	if(B->sign == 1 && A->sign == 1)
	{
		if(length(B->magnitude) > length(A->magnitude))
		{
			return(-1);
		}

		if(length(A->magnitude) > length(B->magnitude))
		{
			return(1);
		}

		if(length(B->magnitude) == length(A->magnitude))
		{
			moveFront(A->magnitude);
			moveFront(B->magnitude);

			while(index(A->magnitude) != -1 && index(B->magnitude) != -1)
			{
				if(get(A->magnitude) > get(B->magnitude))
				{
					return(1);
				}

				if(get(A->magnitude) < get(B->magnitude))
				{
					return(-1);
				}

				if(get(A->magnitude) == get(B->magnitude))
				{
					moveNext(A->magnitude);
					moveNext(B->magnitude);
				}
			}

			if(index(A->magnitude) == -1 && index(B->magnitude) == -1)
			{
				return(0);
			}
		}
	}
}

// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B)
{
	if( A==NULL || B==NULL)
	{
		printf("BigInteger Error: calling equals() on NULL BigInteger reference\n");
		exit(1);
	}

	if(A->sign == B->sign)
	{
		if(listEquals(A->magnitude, B->magnitude))
		{
			return(1);
		}
	}

	return(0);
}

// Manipulation procedures ----------------------------------------------------

// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N)
{
	if( N==NULL )
	{
		printf("BigInteger Error: calling sign() on NULL BigInteger reference\n");
		exit(1);
	}

	clear(N->magnitude);
	N->sign = 0;
}

// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N)
{
	if( N==NULL )
	{
		printf("BigInteger Error: calling sign() on NULL BigInteger reference\n");
		exit(1);
	}

	if(N->sign == 0)
	{
		return;
	}

	if(N->sign == 1)
	{
		N->sign = -1;
		return;
	}

	if(N->sign == -1)
	{
		N->sign = 1;
		return;
	}
}

// BigInteger Arithmetic operations -----------------------------------------------

// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
// and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char* s)
{
	if(s == NULL)
	{
		printf("BigInteger Error: calling stringToBigInteger() on NULL String reference\n");
		exit(1);
	}

	if(s[0] == '/0')
	{
		printf("BigInteger Error: calling stringToBigInteger() on empty string\n");
		exit(1);
	}

	long store = 0;
	long mult = 1;
	int checker = 0;
	int stringIndex = 0;
	int setter;
	int length = strlen(s);
	BigInteger N = newBigInteger();
	N->sign = 1;

	if(s[0] == '-')
	{
		N->sign = -1;
		checker++;
		stringIndex++;
		length--;
	}

	if(s[0] == '+')
	{
		checker++;
		stringIndex++;
		length--;
	}

	while(s[checker] != '\0')
	{
		if(48 > s[checker] || s[checker] > 57)
		{
			printf("BigInteger Error: Only digits must be present in String\n");
			exit(1);
		}
		checker++;
	}

	int stopper = stringIndex + (length%POWER);
	setter = stopper - 1;

	while(stringIndex < stopper)
	{
		long stringVal = s[stringIndex + setter]-48;
		store = store + (stringVal*mult);
		stringIndex++;
		mult = mult*10;
		setter = setter - 2;
	}

	mult = 1;

	if(stopper != 0)
	{
		append(N->magnitude, store);
	}
	store = 0;
	
	setter = POWER - 1;
	while(stringIndex < length)
	{
		for(int check2 = 0; check2 < POWER; check2++)
		{
			long stringVal = s[stringIndex + setter]-48;
	                store = store + (stringVal*mult);
        	        stringIndex++;
               		mult = mult*10;
			setter = setter - 2;
		}
		append(N->magnitude, store);
		mult = 1;
		store = 0;
		setter = POWER - 1;
	}
	return(N);
}

// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N)
{
	if( N==NULL )
	{
		printf("BigInteger Error: calling sign() on NULL BigInteger reference\n");
		exit(1);
	}

	BigInteger copy = newBigInteger();
	copy->sign = N->sign;
	freeList(&(copy)->magnitude);
	copy->magnitude = copyList(N->magnitude);
	return(copy);
}

// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B)
{
	if(S == NULL || A == NULL || B == NULL)
	{
		printf("BigInteger Error: calling add() on NULL BigInteger reference\n");
		exit(1);
	}

	clear(S->magnitude);
	BigInteger newSum = sum(A, B);
	S->sign = newSum->sign;
	S->magnitude = copyList(newSum->magnitude);
	freeBigInteger(&newSum);
	return;
}

// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B)
{	

	if(A == NULL || B == NULL)
	{
		printf("BigInteger Error: calling sum() on NULL BigInteger reference\n");
		exit(1);
	}
	
	if(B->sign == 0)
	{
		BigInteger sum = copy(A);
		return(sum);
	}
	
	if(A->sign == 0)
	{
		BigInteger sum = copy(B);
		return(sum);
	}

	if(A->sign != B->sign)
	{
		if(B->sign == -1 && A->sign == 1)
                {
                        B->sign = 1;
                        BigInteger sum = diff(A, B);
                        B->sign = -1;
                        return(sum);
                }


		if(B->sign == 1 && A->sign == -1)
		{
			A->sign = 1;
			BigInteger sum = diff(B, A);
			A->sign = -1;
			return(sum);
		}
	}	

	BigInteger sum = newBigInteger();

	if(A->sign == B->sign)
	{
		sum->sign = B->sign;	
		long temp;
		long carry = 0;
		moveBack(A->magnitude);
		moveBack(B->magnitude);

		while(index(B->magnitude) >= 0 && index(A->magnitude) >= 0)
		{
			temp = carry + get(B->magnitude) + get(A->magnitude);
			
			if(temp >= BASE)
			{
				carry = 1;
			}

			if(temp < BASE)
			{
				carry = 0;
			}

			temp = temp % BASE;
			prepend(sum->magnitude, temp);
			movePrev(B->magnitude);
			movePrev(A->magnitude);			
		}

		if(index(A->magnitude) == -1)
		{
			while(index(B->magnitude) >= 0)
			{
				temp = carry + get(B->magnitude);

                        	if(temp >= BASE)
                        	{
                                	carry = 1;
                        	}

                        	if(temp < BASE)
                        	{
                                	carry = 0;
                        	}

                        	temp = temp % BASE;
                        	prepend(sum->magnitude, temp);
                        	movePrev(B->magnitude);
			}				
		}

		if(index(B->magnitude) == -1)
                {
                        while(index(A->magnitude) >= 0)
                        {
                                temp = carry + get(A->magnitude);

                                if(temp >= BASE)
                                {
                                        carry = 1;
                                }

                                if(temp < BASE)
                                {
                                        carry = 0;
                                }

                                temp = temp % BASE;
                                prepend(sum->magnitude, temp);
                                movePrev(A->magnitude);
                        }
                }
		
		if(carry > 0)
		{
			prepend(sum->magnitude, carry);
		}
	}
	return(sum);			
}

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B)
{
	if(D == NULL || A == NULL || B == NULL)
	{
		printf("BigInteger Error: calling subtract() on NULL BigInteger reference\n");
		exit(1);
	}

	clear(D->magnitude);
	BigInteger newDifference = diff(A, B);
	D->sign = newDifference->sign;
	D->magnitude = copyList(newDifference->magnitude);
	freeBigInteger(&newDifference);
}

// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B)
{
	if(A == NULL || B == NULL)
	{
		printf("BigInteger Error: calling diff() on NULL BigInteger reference\n");
		exit(1);
	}

	if(B->sign == 0)
	{
		BigInteger difference = copy(A);
		return(difference);
	}

	if(A->sign == 0)
        {
                BigInteger difference = copy(B);
		difference->sign = difference->sign * -1;
                return(difference);
        }
	
	if(A->sign != B->sign)
        {
                if(B->sign == -1 && A->sign == 1)
                {
                        B->sign = 1;
                        BigInteger difference = sum(B, A);
                        B->sign = -1;
                        return(difference);
                }

                if(B->sign == 1 && A->sign == -1)
                {
                        B->sign = -1;
                        BigInteger difference = sum(B, A);
                        B->sign = 1;
                        return(difference);
                }
        }
	
	BigInteger difference = newBigInteger();
	
	if(equals(B, A))
        {
                return(difference);
        }

	if(B->sign == A->sign && compare(A, B) == A->sign)
	{
		long temp;
		long carry = 0;

		moveBack(A->magnitude);
		moveBack(B->magnitude);
	
		while(index(A->magnitude) >= 0 && index(B->magnitude) >= 0)
		{
			temp = get(A->magnitude) - get(B->magnitude) - carry;
			if(temp > 0)
			{
				carry = 0;
			}			

			if(temp < 0)
			{
				temp = temp + BASE;
				carry = 1;
			}

			movePrev(A->magnitude);
			movePrev(B->magnitude);
			prepend(difference->magnitude, temp);
		}

		while(index(A->magnitude) >= 0)
		{
			temp = get(A->magnitude) - carry;
                	if(temp > 0)
                	{
                        	carry = 0;
                	}

                	if(temp < 0)
                	{
                        	temp = temp + BASE;
                        	carry = 1;
                	}

                	movePrev(A->magnitude);
                	prepend(difference->magnitude, temp);
		}
		difference->sign = A->sign;
		return(difference);
	}

	if(B->sign == A->sign && compare(A, B) != A->sign)
        {
                long temp;
                long carry = 0;

                moveBack(A->magnitude);
                moveBack(B->magnitude);

                while(index(A->magnitude) >= 0 && index(B->magnitude) >= 0)
                {
                        temp = get(B->magnitude) - get(A->magnitude) - carry;
                        if(temp > 0)
                        {
                                carry = 0;
                        }

                        if(temp < 0)
                        {
                                temp = temp + BASE;
                                carry = 1;
                        }

                        movePrev(A->magnitude);
                        movePrev(B->magnitude);
                        prepend(difference->magnitude, temp);
                }

                while(index(B->magnitude) >= 0)
                {
                        temp = get(B->magnitude) - carry;
                        if(temp > 0)
                        {
                                carry = 0;
                        }

                        if(temp < 0)
                        {
                                temp = temp + BASE;
                                carry = 1;
                        }

                        movePrev(B->magnitude);
                        prepend(difference->magnitude, temp);
                }
                difference->sign = B->sign * -1;
                return(difference);
        }
}

// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B)
{
	if(P == NULL || A == NULL || B == NULL)
		{
			printf("BigInteger Error: calling multiply() on NULL BigInteger reference\n");
			exit(1);
		}

		BigInteger newProduct = prod(A, B);
		P->sign = newProduct->sign;
		clear(P->magnitude);
		P->magnitude = copyList(newProduct->magnitude);
		freeBigInteger(&newProduct);
}

// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B)
{
	if(A == NULL || B == NULL)
	{
		printf("BigInteger Error: calling prod() on NULL BigInteger reference\n");
		exit(1);
	}

	BigInteger product = newBigInteger();

	if(A->sign * B->sign == 0)
	{	
		return(product);
	}

	product->sign = A->sign * B->sign;

	int size = length(A->magnitude) + length(B->magnitude);
	long carry = 0;
	long temp;
	long* values = calloc(sizeof(long), size);
	int placeholder = 0;
	moveBack(B->magnitude);

	while(index(B->magnitude) >= 0)
	{
		moveBack(A->magnitude);
		for(int i = 0; i<length(A->magnitude); i++)
		{
			values[i + placeholder] = values[i + placeholder] + (get(B->magnitude) * get(A->magnitude));
			movePrev(A->magnitude);
		}
		movePrev(B->magnitude);	
		placeholder++;	
	}
	
	int counter = 0;

	while(counter < size-1)
	{
		temp = values[counter] + carry;
		
		if(temp >= BASE)
                {
            		carry = 0;
			long setter = temp;
			while(setter >= BASE)
			{
				carry++;
				setter = setter - BASE;
			}
                }

                if(temp < BASE)
                {
                        carry = 0;
                }

                temp = temp % BASE;
                prepend(product->magnitude, temp);
  		counter++;
	}
	
	free(values);

	if(carry > 0)
        {
   		prepend(product->magnitude, carry);
        }
	printList(stdout, product->magnitude);
	return(product);	
}

// Other operations -----------------------------------------------------------

// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N)
{
	if( N==NULL )
	{
		printf("BigInteger Error: calling printList() on NULL BigInteger reference\n");
		exit(1);
	}

	if(out == NULL)
	{
		printf("Unable to open file for writing/n");
	}

	if(N->sign == 0)
	{
		fprintf(out, "0\n");
		return;
	}

	if(N->sign == -1)
	{
		fprintf(out, "-");
	}

	moveFront(N->magnitude);

	fprintf(out, "%ld", get(N->magnitude));

	moveNext(N->magnitude);

	while(index(N->magnitude) != -1)
	{
		fprintf(out, "%0*ld", POWER, get(N->magnitude));
		moveNext(N->magnitude);
	}
}
