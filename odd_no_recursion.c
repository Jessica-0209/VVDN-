#include<stdio.h>

void odd_num(int n)
{
	if(n == 0)
	{
		return;
	}

	odd_num(n-1);

	if(n % 2 != 0)
	{
		printf("%d ", n);
	}
}

int main()
{
	int n;
	printf("Enter n = ");
	scanf("%d", &n);

	printf("Odd numbers = ");
	odd_num(n);
	printf("\n");

	return 0;
}
