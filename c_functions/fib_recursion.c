#include<stdio.h>

unsigned long long fibonacci(int n)
{
	if( n == 0 )
	{
		return 0;
	}
	else if( n == 1)
	{
		return 1;
	}
	else
	{
		return fibonacci(n - 1) + fibonacci(n - 2);
	}
}

int main()
{
	int n = 0;
	
	printf("Find the fibonacci series upto the number : ");
	scanf("%d", &n);

	if( n < 0 )
	{
		printf("\nInvalid!\n");
		return 1;
	}
	
	printf("Fibonacci series upto position %d is: \n", n);
	for(int i = 0; i < n; i++)
	{
		printf("%llu", fibonacci(i));
		printf(" ");
	}
	printf("\n");

	return 0;
}
