#include<stdio.h>

typedef unsigned long ulong;
typedef unsigned long int ulint;

ulong fact(ulint n)
{
	if( n == 0 )
	{
		return 1;
	}
	else
	{
		return ( n * fact(n - 1) );
	}
}

int main()
{
	ulong n = 0;
	ulong result = 0;

	printf("Find factorial of the number : ");
	scanf("%lu", &n);
	
	result = fact(n);
	printf("Factorial of %lu is: %lu\n", n, result);

	return 0;
}
